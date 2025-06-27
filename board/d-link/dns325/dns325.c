// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2011
 * Stefan Herbrechtsmeier <stefan@herbrechtsmeier.net>
 *
 * Based on Kirkwood support:
 * (C) Copyright 2009
 * Marvell Semiconductor <www.marvell.com>
 * Written-by: Prafulla Wadaskar <prafulla@marvell.com>
 */

#include <init.h>
#include <netdev.h>
#include <asm/global_data.h>
#include <asm/arch/cpu.h>
#include <asm/arch/soc.h>
#include <asm/arch/mpp.h>
#include <asm/arch/gpio.h>
#include <linux/bitops.h>
#include "dns325.h"

DECLARE_GLOBAL_DATA_PTR;

int board_early_init_f(void)
{
	/* Gpio configuration */
	mvebu_config_gpio(DNS325_OE_VAL_LOW, DNS325_OE_VAL_HIGH,
			  DNS325_OE_LOW, DNS325_OE_HIGH);

	/* Multi-Purpose Pins Functionality configuration */
	static const u32 kwmpp_config[] = {
		MPP0_NF_IO2,
		MPP1_NF_IO3,
		MPP2_NF_IO4,
		MPP3_NF_IO5,
		MPP4_NF_IO6,
		MPP5_NF_IO7,
		MPP6_SYSRST_OUTn,
		MPP7_GPO,
		MPP8_TW_SDA,
		MPP9_TW_SCK,
		MPP10_UART0_TXD,
		MPP11_UART0_RXD,
		MPP12_SD_CLK,
		MPP13_SD_CMD,
		MPP14_SD_D0,
		MPP15_SD_D1,
		MPP16_SD_D2,
		MPP17_SD_D3,
		MPP18_NF_IO0,
		MPP19_NF_IO1,
		MPP20_SATA1_ACTn,	/* sata1(left) status led */
		MPP21_SATA0_ACTn,	/* sata0(right) status led */
		MPP22_GPIO,
		MPP23_GPIO,
		MPP24_GPIO,		/* power off out */
		MPP25_GPIO,
		MPP26_GPIO,		/* power led */
		MPP27_GPIO,		/* sata0(right) error led */
		MPP28_GPIO,		/* sata1(left) error led */
		MPP29_GPIO,		/* usb error led */
		MPP30_GPIO,
		MPP31_GPIO,
		MPP32_GPIO,
		MPP33_GPIO,
		MPP34_GPIO,		/* power key */
		MPP35_GPIO,
		MPP36_GPIO,
		MPP37_GPIO,
		MPP38_GPIO,
		MPP39_GPIO,		/* enable sata 0 */
		MPP40_GPIO,		/* enable sata 1 */
		MPP41_GPIO,		/* hdd0 present */
		MPP42_GPIO,		/* hdd1 present */
		MPP43_GPIO,		/* usb status led */
		MPP44_GPIO,		/* fan status */
		MPP45_GPIO,		/* fan high speed */
		MPP46_GPIO,		/* fan low speed */
		MPP47_GPIO,		/* usb umount */
		MPP48_GPIO,		/* factory reset */
		MPP49_GPIO,		/* thermal sensor */
		0
	};
	kirkwood_mpp_conf(kwmpp_config, NULL);

	kw_gpio_set_blink(DNS325_GPIO_LED_POWER , 1);

	kw_gpio_set_value(DNS325_GPIO_SATA0_EN , 1);
	kw_gpio_set_value(DNS325_GPIO_SATA1_EN , 1);
	return 0;
}

int board_eth_init(struct bd_info *bis)
{
	return cpu_eth_init(bis);
}

int board_init(void)
{
	/* Boot parameters address */
	gd->bd->bi_boot_params = mvebu_sdram_bar(0) + 0x100;

	return 0;
}
