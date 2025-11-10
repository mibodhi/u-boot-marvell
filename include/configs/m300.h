/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * (C) Copyright 2023-2025 Tony Dinh <mibodhi@gmail.com>
 */

#ifndef _CONFIG_M300_H
#define _CONFIG_M300_H

#include "mv-common.h"

#define KERNEL_ADDR_R	__stringify(0x800000)
#define FDT_ADDR_R	__stringify(0x2c00000)
#define RAMDISK_ADDR_R	__stringify(0x01100000)
#define SCRIPT_ADDR_R	__stringify(0x200000)

#define LOAD_ADDRESS_ENV_SETTINGS \
	"kernel_addr_r=" KERNEL_ADDR_R "\0" \
	"fdt_addr_r=" FDT_ADDR_R "\0" \
	"ramdisk_addr_r=" RAMDISK_ADDR_R "\0" \
	"scriptaddr=" SCRIPT_ADDR_R "\0"

#define CFG_EXTRA_ENV_SETTINGS \
	LOAD_ADDRESS_ENV_SETTINGS \
	"fdtfile=" CONFIG_DEFAULT_DEVICE_TREE ".dtb\0" \
	"mtdparts=" CONFIG_MTDPARTS_DEFAULT "\0" \
	"console=ttyS0,115200\0"

#endif /* _CONFIG_M300_H */
