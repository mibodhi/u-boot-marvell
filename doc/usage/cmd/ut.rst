.. SPDX-License-Identifier: GPL-2.0+:

.. index::
   single: ut (command)

ut command
==========

Synopsis
--------

::

    ut [-r<runs>] [-fs] [-I<n>:<one_test>] [<suite> [<test>]]

       <runs>      Number of times to run each test
       -f          Force 'manual' tests to run as well
       <n>         Run <one test> after <n> other tests have run
       <one_test>  Name of the 'one' test to run
       <suite>     Test suite to run, or `all`
       <test>      Name of single test to run

Description
-----------

The ut command runs unit tests written in C.

Typically the command is run on :ref:`arch/sandbox/sandbox:sandbox` since it
includes a near-complete set of emulators, no code-size limits, many CONFIG
options enabled and runs easily in CI without needing QEMU. It is also possible
to run some tests on real boards.

For a list of available test suites, type `ut info -s`.

Each test is normally run once, although those marked with `UTF_DM` are
run with livetree and flattree where possible. To run a test more than once,
use the `-r` flag.

Manual tests are normally skipped by this command. Use `-f` to run them. See
See :ref:`develop/tests_writing:mixing python and c` for more information on
manual test.

When running unit tests, some may have side effects which cause a subsequent
test to break. This can sometimes be seen when using 'ut dm' or similar. To
fix this, select the 'one' test which breaks. Then tell the 'ut' command to
run this one test after a certain number of other tests have run. Using a
binary search method with `-I` you can quickly figure one which test is causing
the problem.

Generally all tests in the suite are run. To run just a single test from the
suite, provide the <test> argument.

See :ref:`develop/tests_writing:writing c tests` for more information on how to
write unit tests.

Example
-------

Show information about tests::

    => ut info
    Test suites: 23
    Total tests: 833

List available unit-test suites::

    => ut info -s
    Test suites: 23
    Total tests: 833

    Tests  Suite         Purpose
    -----  ------------  -------------------------
        1  addrmap       very basic test of addrmap command
        4  bdinfo        bdinfo (board info) command
       14  bloblist      bloblist implementation
        7  bootm         bootm command
       66  bootstd       standard boot implementation
        2  cmd           various commands
       14  common        tests for common/ directory
       502 dm            driver model
        6  env           environment
        1  exit          shell exit and variables
       19  fdt           fdt command
       10  fdt_overlay   device tree overlays
        1  font          font command
       20  hush          hush behaviour
      115  lib           library functions
        2  loadm         loadm command parameters and loading memory blob
       18  log           logging functions
        1  mbr           mbr command
        1  measurement   TPM-based measured boot
       13  mem           memory-related commands
        1  pci_mps       PCI Express Maximum Payload Size
       11  setexpr       setexpr command
        4  upl           Universal payload support


Run one of the suites::

    => ut bloblist
    Running 14 bloblist tests
    Test: bloblist_test_align: bloblist.c
    Test: bloblist_test_bad_blob: bloblist.c
    Test: bloblist_test_blob: bloblist.c
    Test: bloblist_test_blob_ensure: bloblist.c
    Test: bloblist_test_blob_maxsize: bloblist.c
    Test: bloblist_test_checksum: bloblist.c
    Test: bloblist_test_cmd_info: bloblist.c
    Test: bloblist_test_cmd_list: bloblist.c
    Test: bloblist_test_grow: bloblist.c
    Test: bloblist_test_init: bloblist.c
    Test: bloblist_test_reloc: bloblist.c
    Test: bloblist_test_resize_fail: bloblist.c
    Test: bloblist_test_resize_last: bloblist.c
    Test: bloblist_test_shrink: bloblist.c
    Failures: 0

Run just a single test in a suite::

    => ut bloblist bloblist_test_grow
    Test: bloblist_test_grow: bloblist.c
    Failures: 0
