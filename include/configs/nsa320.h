/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * (C) Copyright 2016-2023 bodhi <mibodhi@gmail.com>
 *
 * Based on
 * Copyright (C) 2012  Peter Schildmann <linux@schildmann.info>
 *
 * Based on guruplug.h originally written by
 * Siddarth Gore <gores@marvell.com>
 * (C) Copyright 2009
 * Marvell Semiconductor <www.marvell.com>
 */

#ifndef _CONFIG_NSA320_H
#define _CONFIG_NSA320_H

#include "mv-common.h"

/*
 * Default environment variables
 */
#define CFG_EXTRA_ENV_SETTINGS \
	"bootcmd_exec=if run load_uimage; then; if run load_initrd; then if run load_dtb; then bootm $load_uimage_addr $load_initrd_addr $load_dtb_addr; " \
		"else bootm $load_uimage_addr $load_initrd_addr; fi; else if run load_dtb; then bootm $load_uimage_addr - $load_dtb_addr; else bootm $load_uimage_addr; fi; fi; fi\0" \
	"bootcmd_uenv=run uenv_load; if test $uenv_loaded -eq 1; then run uenv_import; fi\0" \
	"bootdelay=10\0" \
	"bootdev=usb\0" \
	"console=ttyS0,115200\0"\
	"device=0:1\0" \
	"devices=usb sata\0" \
	"disks=0 1 2 3\0" \
	"if_netconsole=ping $serverip\0" \
	"dtb_file=/boot/dts/"CONFIG_DEFAULT_DEVICE_TREE".dtb\0" \
	"load_dtb_addr=0x1c00000\0" \
	"load_initrd_addr=0x1100000\0" \
	"load_uimage_addr=0x800000\0" \
	"load_dtb=echo loading DTB $dtb_file ...; load $bootdev $device $load_dtb_addr $dtb_file\0" \
	"load_initrd=echo loading uInitrd ...; load $bootdev $device $load_initrd_addr /boot/uInitrd\0" \
	"load_uimage=echo loading uImage ...; load $bootdev $device $load_uimage_addr /boot/uImage\0" \
        "mtdparts="CONFIG_MTDPARTS_DEFAULT"\0"\
	"preboot_nc=run if_netconsole start_netconsole\0" \
	"scan_disk=echo running scan_disk ...; scan_done=0; setenv scan_usb \"usb start\";  setenv scan_sata \"sata init\";  setenv scan_mmc \"mmc rescan\"; " \
		"for dev in $devices; do if test $scan_done -eq 0; then echo Scan device $dev; run scan_$dev; " \
			"for disknum in $disks; do if test $scan_done -eq 0; then echo device $dev $disknum:1; if load $dev $disknum:1 $load_uimage_addr /boot/uImage 1; then scan_done=1; " \
				"echo Found bootable drive on $dev $disknum; setenv device $disknum:1; setenv bootdev $dev; fi; fi; done; fi; done\0" \
	"set_bootargs=setenv bootargs console=ttyS0,115200 root=LABEL=rootfs rootdelay=10 $mtdparts $custom_params\0" \
	"start_netconsole=setenv ncip $serverip; setenv bootdelay 10; setenv stdin nc; setenv stdout nc; setenv stderr nc; version;\0" \
	"stderr=serial\0" \
	"stdin=serial\0" \
	"stdout=serial\0" \
	"uenv_addr=0x810000\0" \
	"uenv_import=echo importing envs ...; env import -t $uenv_addr $filesize\0" \
	"uenv_init_devices=echo Initializing devices...; setenv init_usb usb start;  setenv init_sata sata init;  setenv init_mmc mmc rescan; for devtype in $devices; do run init_$devtype; done;\0" \
	"uenv_load=run uenv_init_devices; setenv uenv_loaded 0; for devtype in $devices; do for disknum in $disks; " \
		"do if test $uenv_loaded -eq 0; then setenv device_type $devtype; setenv disk_number $disknum; run uenv_read; fi; done; done;\0" \
	"uenv_read=echo Loading envs from $device_type $disk_number...; if load $device_type  $disk_number:1 $uenv_addr /boot/uEnv.txt; then setenv uenv_loaded 1; echo ... envs loaded; fi\0" \
	"usb_ready_retry=15\0"

#endif /* _CONFIG_NSA320_H */
