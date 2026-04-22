// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2025 Tony Dinh <mibodhi@gmail.com>
 * Copyright (C) 2011 Simon Guinot <sguinot@lacie.com>
 *
 * Based on Kirkwood support:
 * (C) Copyright 2009
 * Marvell Semiconductor <www.marvell.com>
 * Written-by: Prafulla Wadaskar <prafulla@marvell.com>
 */

#include <netdev.h>
#include <asm/arch/cpu.h>
#include <asm/arch/soc.h>
#include <asm/arch/mpp.h>
#include <asm/io.h>
#include <asm/arch/gpio.h>
#include <asm/mach-types.h>
#include <bootstage.h>
#include <command.h>
#include <init.h>
#include <linux/bitops.h>

/* GPIO configuration */
#define NETSPACE_V2_OE_LOW		0x06004000
#define NETSPACE_V2_OE_HIGH		0x00000031
#define NETSPACE_V2_OE_VAL_LOW		0x10030000
#define NETSPACE_V2_OE_VAL_HIGH		0x00000000

#define NETSPACE_V2_GPIO_BUTTON         32

DECLARE_GLOBAL_DATA_PTR;

int board_early_init_f(void)
{
	/* Gpio configuration */
	mvebu_config_gpio(NETSPACE_V2_OE_VAL_LOW, NETSPACE_V2_OE_VAL_HIGH,
			  NETSPACE_V2_OE_LOW, NETSPACE_V2_OE_HIGH);

	/* Multi-Purpose Pins Functionality configuration */
	static const u32 kwmpp_config[] = {
		MPP0_SPI_SCn,
		MPP1_SPI_MOSI,
		MPP2_SPI_SCK,
		MPP3_SPI_MISO,
		MPP4_NF_IO6,
		MPP5_NF_IO7,
		MPP6_SYSRST_OUTn,
		MPP7_GPO,		/* Fan speed (bit 1) */
		MPP8_TW_SDA,
		MPP9_TW_SCK,
		MPP10_UART0_TXD,
		MPP11_UART0_RXD,
		MPP12_GPO,		/* Red led */
		MPP14_GPIO,		/* USB fuse */
		MPP16_GPIO,		/* SATA 0 power */
		MPP17_GPIO,		/* SATA 1 power */
		MPP18_NF_IO0,
		MPP19_NF_IO1,
		MPP20_SATA1_ACTn,
		MPP21_SATA0_ACTn,
		MPP22_GPIO,		/* Fan speed (bit 0) */
		MPP23_GPIO,		/* Fan power */
		MPP24_GPIO,		/* USB mode select */
		MPP25_GPIO,		/* Fan rotation fail */
		MPP26_GPIO,		/* USB vbus-in detection */
		MPP28_GPIO,		/* USB enable vbus-out */
		MPP29_GPIO,		/* Blue led (slow register) */
		MPP30_GPIO,		/* Blue led (command register) */
		MPP31_GPIO,		/* Board power off */
		MPP32_GPIO,		/* Button (0 = Released, 1 = Pushed) */
		MPP33_GPIO,		/* Fan speed (bit 2) */
		0
	};
	kirkwood_mpp_conf(kwmpp_config, NULL);

	return 0;
}

int board_eth_init(struct bd_info *bis)
{
	return cpu_eth_init(bis);
}

int board_init(void)
{
#ifdef CONFIG_MACH_TYPE
	/* Machine number */
	gd->bd->bi_arch_number = CONFIG_MACH_TYPE;
#endif

	/* Boot parameters address */
	gd->bd->bi_boot_params = mvebu_sdram_bar(0) + 0x100;

	return 0;
}

#if defined(CONFIG_KIRKWOOD_GPIO)
/* Return GPIO button status */
static int
do_read_button(struct cmd_tbl *cmdtp, int flag, int argc, char *const argv[])
{
	return kw_gpio_get_value(NETSPACE_V2_GPIO_BUTTON);
}

U_BOOT_CMD(button, 1, 1, do_read_button,
	   "Return GPIO button status 0=off 1=on", "");
#endif
