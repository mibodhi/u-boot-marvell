// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2024 bodhi <mibodhi@gmail.com>
 */

#include <asm/arch/soc.h>
#include <asm/arch/mpp.h>
#include <netdev.h>
#include <asm/arch/cpu.h>
#include <asm/gpio.h>
#include <asm/io.h>
#include <asm/arch/gpio.h>
#include <asm/global_data.h>
#include <asm/mach-types.h>
#include <command.h>
#include <init.h>
#include <linux/bitops.h>


DECLARE_GLOBAL_DATA_PTR;

/* GPIOs */
#define DS211_OE_LOW		(~(0))
#define DS211_OE_HIGH		(~(0))
#define DS211_OE_VAL_LOW	(BIT(15) | BIT(30))
#define DS211_OE_VAL_HIGH	(BIT(2))

int board_early_init_f(void)
{
	/*
	 * default gpio configuration
	 * There are maximum 64 gpios controlled through 2 sets of registers.
	 */
	mvebu_config_gpio(DS211_OE_VAL_LOW,
			  DS211_OE_VAL_HIGH,
			  DS211_OE_LOW,
			  DS211_OE_HIGH);

	/* Multi-Purpose Pins Functionality configuration */
	static const u32 kwmpp_config[] = {
		MPP0_SPI_SCn,
		MPP1_SPI_MOSI,
		MPP2_SPI_SCK,
		MPP3_SPI_MISO,
		MPP4_GPIO,
		MPP5_GPO,
		MPP6_SYSRST_OUTn,
		MPP7_GPO,
		MPP8_TW_SDA,
		MPP9_TW_SCK,
		MPP10_UART0_TXD,
		MPP11_UART0_RXD,
		MPP12_GPO,
		MPP13_UART1_TXD,
		MPP14_UART1_RXD,
		MPP15_GPIO,
		MPP16_GPIO,
		MPP17_GPIO,
		MPP18_GPO,
		MPP19_GPO,
		MPP20_SATA1_ACTn,
		MPP21_SATA0_ACTn,
		MPP22_GPIO,
		MPP23_GPIO,
		MPP24_GPIO,
		MPP25_GPIO,
		MPP26_GPIO,
		MPP27_GPIO,
		MPP28_GPIO,
		MPP29_GPIO,
		MPP30_GPIO,	// MPP30_SATA0_ACTn,
		MPP31_GPIO,
		MPP32_GPIO,
		MPP33_GPIO,
		MPP34_GPIO,	// MPP34_SATA1_ACTn,
		MPP35_GPIO,
		MPP36_GPIO,
		MPP37_GPIO,
		MPP38_GPIO,
		MPP39_GPIO,
		MPP40_GPIO,
		MPP41_GPIO,
		MPP42_GPIO,
		MPP43_GPIO,
		MPP44_GPIO,
		MPP45_GPIO,
		MPP46_GPIO,
		MPP47_GPIO,
		MPP48_GPIO,
		MPP49_GPIO,
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
	/* address of boot parameters */
	gd->bd->bi_boot_params = mvebu_sdram_bar(0) + 0x100;

	return 0;
}
