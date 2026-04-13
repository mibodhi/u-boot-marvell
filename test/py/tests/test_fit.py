# SPDX-License-Identifier:	GPL-2.0+
# Copyright (c) 2013, Google Inc.

"""Sanity check of the FIT handling in U-Boot"""

import os
import struct

import pytest
import fit_util
import utils

# Define a base ITS which we can adjust using % and a dictionary
BASE_ITS = '''
/dts-v1/;

/ {
        description = "Chrome OS kernel image with one or more FDT blobs";
        #address-cells = <1>;

        images {
                kernel-1 {
                        data = /incbin/("%(kernel)s");
                        type = "kernel";
                        arch = "sandbox";
                        os = "linux";
                        compression = "%(compression)s";
                        load = <0x40000>;
                        entry = <0x8>;
                };
                kernel-2 {
                        data = /incbin/("%(loadables1)s");
                        type = "kernel";
                        arch = "sandbox";
                        os = "linux";
                        compression = "none";
                        %(loadables1_load)s
                        entry = <0x0>;
                };
                fdt-1 {
                        description = "snow";
                        data = /incbin/("%(fdt)s");
                        type = "flat_dt";
                        arch = "sandbox";
                        %(fdt_load)s
                        compression = "%(compression)s";
                        signature-1 {
                                algo = "sha1,rsa2048";
                                key-name-hint = "dev";
                        };
                };
                ramdisk-1 {
                        description = "snow";
                        data = /incbin/("%(ramdisk)s");
                        type = "ramdisk";
                        arch = "sandbox";
                        os = "linux";
                        %(ramdisk_load)s
                        compression = "%(compression)s";
                };
                ramdisk-2 {
                        description = "snow";
                        data = /incbin/("%(loadables2)s");
                        type = "ramdisk";
                        arch = "sandbox";
                        os = "linux";
                        %(loadables2_load)s
                        compression = "none";
                };
        };
        configurations {
                default = "conf-1";
                conf-1 {
                        %(kernel_config)s
                        fdt = "fdt-1";
                        %(ramdisk_config)s
                        %(loadables_config)s
                };
        };
};
'''

# Define a base FDT - currently we don't use anything in this
BASE_FDT = '''
/dts-v1/;

/ {
	#address-cells = <1>;
	#size-cells = <0>;

	model = "Sandbox Verified Boot Test";
	compatible = "sandbox";

	binman {
	};

	reset@0 {
		compatible = "sandbox,reset";
		reg = <0>;
	};
};
'''

# This is the U-Boot script that is run for each test. First load the FIT,
# then run the 'bootm' command, then save out memory from the places where
# we expect 'bootm' to write things. Then quit.
BASE_SCRIPT = '''
mw.b 0 0 160000
host load hostfs 0 %(fit_addr)x %(fit)s
fdt addr %(fit_addr)x
bootm start %(fit_addr)x
bootm loados
host save hostfs 0 %(kernel_addr)x %(kernel_out)s %(kernel_size)x
host save hostfs 0 %(fdt_addr)x %(fdt_out)s %(fdt_size)x
host save hostfs 0 %(ramdisk_addr)x %(ramdisk_out)s %(ramdisk_size)x
host save hostfs 0 %(loadables1_addr)x %(loadables1_out)s %(loadables1_size)x
host save hostfs 0 %(loadables2_addr)x %(loadables2_out)s %(loadables2_size)x
'''

@pytest.mark.boardspec('sandbox')
@pytest.mark.buildconfigspec('fit')
@pytest.mark.requiredtool('dtc')
class TestFitImage:
    """Test class for FIT image handling in U-Boot

    TODO: Almost everything:
      - hash algorithms - invalid hash/contents should be detected
      - signature algorithms - invalid sig/contents should be detected
      - compression
      - checking that errors are detected like:
            - image overwriting
            - missing images
            - invalid configurations
            - incorrect os/arch/type fields
            - empty data
            - images too large/small
            - invalid FDT (e.g. putting a random binary in instead)
      - default configuration selection
      - bootm command line parameters should have desired effect
      - run code coverage to make sure we are testing all the code
    """

    def make_fname(self, ubman, leaf):
        """Make a temporary filename

        Args:
            ubman (ConsoleBase): U-Boot fixture
            leaf (str): Leaf name of file to create (within temporary directory)

        Return:
            str: Temporary filename
        """
        return os.path.join(ubman.config.build_dir, leaf)

    def filesize(self, fname):
        """Get the size of a file

        Args:
            fname (str): Filename to check

        Return:
            int: Size of file in bytes
        """
        return os.stat(fname).st_size

    def read_file(self, fname):
        """Read the contents of a file

        Args:
            fname (str): Filename to read

        Return:
            str: Contents of file
        """
        with open(fname, 'rb') as fd:
            return fd.read()

    def make_ramdisk(self, ubman, filename, text):
        """Make a sample ramdisk with test data

        Returns:
            str: Filename of ramdisk created
        """
        fname = self.make_fname(ubman, filename)
        data = ''
        for i in range(100):
            data += f'{text} {i} was seldom used in the middle ages\n'
        with open(fname, 'w', encoding='ascii') as fd:
            print(data, file=fd)
        return fname

    def make_compressed(self, ubman, filename):
        """Compress a file using gzip"""
        utils.run_and_log(ubman, ['gzip', '-f', '-k', filename])
        return filename + '.gz'

    def find_matching(self, text, match):
        """Find a match in a line of text, and return the unmatched line portion

        This is used to extract a part of a line from some text. The match string
        is used to locate the line - we use the first line that contains that
        match text.

        Once we find a match, we discard the match string itself from the line,
        and return what remains.

        TODO: If this function becomes more generally useful, we could change it
        to use regex and return groups.

        Args:
            text (list of str): Text to check, one for each command issued
            match (str): String to search for

        Return:
            str: unmatched portion of line

        Raises:
            ValueError: If match is not found

        .. code-block:: python

            >>> find_matching(['first line:10', 'second_line:20'], 'first line:')
            '10'
            >>> find_matching(['first line:10', 'second_line:20'], 'second line')
            Traceback (most recent call last):
              ...
            ValueError: Test aborted
            >>> find_matching(['first line:10', 'second_line:20'], 'second_line:')
            '20'
            >>> find_matching(['first line:10', 'second_line:20\\nthird_line:30'],
            ...               'third_line:')
            '30'
        """
        # pylint: disable=W0612
        __tracebackhide__ = True
        for line in '\n'.join(text).splitlines():
            pos = line.find(match)
            if pos != -1:
                return line[:pos] + line[pos + len(match):]

        pytest.fail("Expected '%s' but not found in output")
        return '<no-match>'

    def check_equal(self, expected_fname, actual_fname, failure_msg):
        """Check that a file matches its expected contents

        This is always used on out-buffers whose size is decided by the test
        script anyway, which in some cases may be larger than what we're
        actually looking for. So it's safe to truncate it to the size of the
        expected data.

        Args:
            expected_fname (str): Filename containing expected contents
            actual_fname (str): Filename containing actual contents
            failure_msg (str): Message to print on failure
        """
        expected_data = self.read_file(expected_fname)
        actual_data = self.read_file(actual_fname)
        if len(expected_data) < len(actual_data):
            actual_data = actual_data[:len(expected_data)]
        assert expected_data == actual_data, failure_msg

    def check_not_equal(self, expected_fname, actual_fname, failure_msg):
        """Check that a file does not match its expected contents

        Args:
            expected_fname (str): Filename containing expected contents
            actual_fname (str): Filename containing actual contents
            failure_msg (str): Message to print on failure
        """
        expected_data = self.read_file(expected_fname)
        actual_data = self.read_file(actual_fname)
        assert expected_data != actual_data, failure_msg

    def test_fit_operations(self, ubman):
        """Basic sanity check of FIT loading in U-Boot

        This test covers various FIT configurations and verifies correct behavior.

        Args:
            ubman (ConsoleBase): U-Boot fixture
        """
        mkimage = os.path.join(ubman.config.build_dir, 'tools/mkimage')

        # Set up invariant files
        fdt_data = fit_util.make_dtb(ubman, BASE_FDT, 'u-boot')
        kernel = fit_util.make_kernel(ubman, 'test-kernel.bin', 'kernel')
        ramdisk = self.make_ramdisk(ubman, 'test-ramdisk.bin', 'ramdisk')
        loadables1 = fit_util.make_kernel(ubman, 'test-loadables1.bin', 'lenrek')
        loadables2 = self.make_ramdisk(ubman, 'test-loadables2.bin', 'ksidmar')
        kernel_out = self.make_fname(ubman, 'kernel-out.bin')
        fdt = self.make_fname(ubman, 'u-boot.dtb')
        fdt_out = self.make_fname(ubman, 'fdt-out.dtb')
        ramdisk_out = self.make_fname(ubman, 'ramdisk-out.bin')
        loadables1_out = self.make_fname(ubman, 'loadables1-out.bin')
        loadables2_out = self.make_fname(ubman, 'loadables2-out.bin')

        # Set up basic parameters with default values
        params = {
            'fit_addr' : 0x1000,

            'kernel' : kernel,
            'kernel_out' : kernel_out,
            'kernel_addr' : 0x40000,
            'kernel_size' : self.filesize(kernel),
            'kernel_config' : 'kernel = "kernel-1";',

            'fdt' : fdt,
            'fdt_out' : fdt_out,
            'fdt_addr' : 0x80000,
            'fdt_size' : self.filesize(fdt_data),
            'fdt_load' : '',

            'ramdisk' : ramdisk,
            'ramdisk_out' : ramdisk_out,
            'ramdisk_addr' : 0xc0000,
            'ramdisk_size' : self.filesize(ramdisk),
            'ramdisk_load' : '',
            'ramdisk_config' : '',

            'loadables1' : loadables1,
            'loadables1_out' : loadables1_out,
            'loadables1_addr' : 0x100000,
            'loadables1_size' : self.filesize(loadables1),
            'loadables1_load' : '',

            'loadables2' : loadables2,
            'loadables2_out' : loadables2_out,
            'loadables2_addr' : 0x140000,
            'loadables2_size' : self.filesize(loadables2),
            'loadables2_load' : '',

            'loadables_config' : '',
            'compression' : 'none',
        }

        # Make a basic FIT and a script to load it
        fit = fit_util.make_fit(ubman, mkimage, BASE_ITS, params)
        params['fit'] = fit
        cmd = BASE_SCRIPT % params

        # First check that we can load a kernel
        # We could perhaps reduce duplication with some loss of readability
        with ubman.log.section('Kernel load'):
            output = ubman.run_command_list(cmd.splitlines())
            self.check_equal(kernel, kernel_out, 'Kernel not loaded')
            self.check_not_equal(fdt_data, fdt_out,
                                 'FDT loaded but should be ignored')
            self.check_not_equal(ramdisk, ramdisk_out,
                                 'Ramdisk loaded but should not be')

            # Find out the offset in the FIT where U-Boot has found the FDT
            line = self.find_matching(output, 'Booting using the fdt blob at ')
            fit_offset = int(line, 16) - params['fit_addr']
            fdt_magic = struct.pack('>L', 0xd00dfeed)
            data = self.read_file(fit)

            # Now find where it actually is in the FIT (skip the first word)
            real_fit_offset = data.find(fdt_magic, 4)
            assert fit_offset == real_fit_offset, (
                    'U-Boot loaded FDT from offset %#x, FDT is actually at %#x' %
                    (fit_offset, real_fit_offset))

        # Check bootargs string substitution
            output = ubman.run_command_list([
                'env set bootargs \\"\'my_boot_var=${foo}\'\\"',
                'env set foo bar',
                'bootm prep',
                'env print bootargs'])
            assert 'bootargs="my_boot_var=bar"' in output, "Bootargs strings not substituted"

        # Now a kernel and an FDT
        with ubman.log.section('Kernel + FDT load'):
            params['fdt_load'] = 'load = <%#x>;' % params['fdt_addr']
            fit = fit_util.make_fit(ubman, mkimage, BASE_ITS, params)
            params['fit'] = fit
            cmd = BASE_SCRIPT % params
            output = ubman.run_command_list(cmd.splitlines())
            self.check_equal(kernel, kernel_out, 'Kernel not loaded')
            self.check_equal(fdt_data, fdt_out, 'FDT not loaded')
            self.check_not_equal(ramdisk, ramdisk_out,
                                 'Ramdisk loaded but should not be')

        # Try a ramdisk
        with ubman.log.section('Kernel + FDT + Ramdisk load'):
            params['ramdisk_config'] = 'ramdisk = "ramdisk-1";'
            params['ramdisk_load'] = 'load = <%#x>;' % params['ramdisk_addr']
            fit = fit_util.make_fit(ubman, mkimage, BASE_ITS, params)
            params['fit'] = fit
            cmd = BASE_SCRIPT % params
            output = ubman.run_command_list(cmd.splitlines())
            self.check_equal(ramdisk, ramdisk_out, 'Ramdisk not loaded')

        # Configuration with some Loadables
        with ubman.log.section('Kernel + FDT + Ramdisk load + Loadables'):
            params['loadables_config'] = 'loadables = "kernel-2", "ramdisk-2";'
            params['loadables1_load'] = ('load = <%#x>;' %
                                          params['loadables1_addr'])
            params['loadables2_load'] = ('load = <%#x>;' %
                                          params['loadables2_addr'])
            fit = fit_util.make_fit(ubman, mkimage, BASE_ITS, params)
            params['fit'] = fit
            cmd = BASE_SCRIPT % params
            output = ubman.run_command_list(cmd.splitlines())
            self.check_equal(loadables1, loadables1_out,
                             'Loadables1 (kernel) not loaded')
            self.check_equal(loadables2, loadables2_out,
                             'Loadables2 (ramdisk) not loaded')

        # Kernel, FDT and Ramdisk all compressed
        with ubman.log.section('(Kernel + FDT + Ramdisk) compressed'):
            params['compression'] = 'gzip'
            params['kernel'] = self.make_compressed(ubman, kernel)
            params['fdt'] = self.make_compressed(ubman, fdt)
            params['ramdisk'] = self.make_compressed(ubman, ramdisk)
            fit = fit_util.make_fit(ubman, mkimage, BASE_ITS, params)
            params['fit'] = fit
            cmd = BASE_SCRIPT % params
            output = ubman.run_command_list(cmd.splitlines())
            self.check_equal(kernel, kernel_out, 'Kernel not loaded')
            self.check_equal(fdt_data, fdt_out, 'FDT not loaded')
            self.check_not_equal(ramdisk, ramdisk_out, 'Ramdisk got decompressed?')
            self.check_equal(ramdisk + '.gz', ramdisk_out, 'Ramdisk not loaded')

        # Try without a kernel
        with ubman.log.section('No kernel + FDT'):
            params['kernel_config'] = ''
            params['ramdisk_config'] = ''
            params['ramdisk_load'] = ''
            fit = fit_util.make_fit(ubman, mkimage, BASE_ITS, params)
            params['fit'] = fit
            cmd = BASE_SCRIPT % params
            output = ubman.run_command_list(cmd.splitlines())
            assert "can't get kernel image!" in '\n'.join(output)
