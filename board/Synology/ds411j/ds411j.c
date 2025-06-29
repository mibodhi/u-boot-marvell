// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2025 bodhi <mibodhi@gmail.com>
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

#define DS411J_OE_LOW		(0)
#define DS411J_OE_HIGH		(0)
#define DS411J_OE_VAL_LOW	(BIT(12) | BIT(16))
#define DS411J_OE_VAL_HIGH      (BIT(0) | BIT(1) | BIT(5) | BIT(7) | BIT(9) | BIT(11) | BIT(12) | BIT(13) | BIT(15))

int board_early_init_f(void)
{
	/*
	 * Default gpio configuration
	 * There are maximum 64 gpios controlled through 2 sets of registers
	 * the  below configuration configures mainly initial LED status
	 */
	mvebu_config_gpio(DS411J_OE_VAL_LOW,
			  DS411J_OE_VAL_HIGH,
			  DS411J_OE_LOW,
			  DS411J_OE_HIGH);

	/* TODO the MPPs are wrong - redo it using md.l dumps in document*/

	/* Multi-Purpose Pins Functionality configuration */
	static const u32 kwmpp_config[] = {

                MPP0_SPI_SCn,           /* SPI Flash */
                MPP1_SPI_MOSI,
                MPP2_SPI_SCK,
                MPP3_SPI_MISO,
                MPP4_GPIO,
                MPP5_GPO,
                MPP6_SYSRST_OUTn,       /* Reset signal */
                MPP7_GPO,
                MPP8_TW_SDA,            /* I2C */
                MPP9_TW_SCK,            /* I2C */
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
		MPP20_GE1_0,
		MPP21_GE1_1,
		MPP22_GE1_2,
		MPP23_GE1_3,
		MPP24_GE1_4,
		MPP25_GE1_5,
		MPP26_GE1_6,
		MPP27_GE1_7,
		MPP28_GPIO,
		MPP29_GPIO,
		MPP30_GE1_10,
		MPP31_GE1_11,
		MPP32_GE1_12,
		MPP33_GE1_13,
		MPP34_SATA1_ACTn,
		MPP35_SATA0_ACTn,
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
