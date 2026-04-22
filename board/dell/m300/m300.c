// SPDX-License-Identifier: GPL-2.0+ 
/*
 * (C) Copyright 2021-2025 Tony Dinh <mibodhi@gmail.com>
 *
 */

#include <netdev.h>
#include <asm/arch/soc.h>
#include <asm/arch/mpp.h>
#include <asm/arch/cpu.h>
#include <asm/gpio.h>
#include <asm/io.h>
#include <asm/arch/gpio.h>
#include <asm/mach-types.h>
#include <bootstage.h>
#include "m300.h"

DECLARE_GLOBAL_DATA_PTR;

int board_early_init_f(void)
{
	/*
	 * default gpio configuration
	 * There are maximum 64 gpios controlled through 2 sets of registers
	 * the below configuration configures mainly initial LED status
	 */
	mvebu_config_gpio(M300_OE_VAL_LOW, M300_OE_VAL_HIGH,
		       M300_OE_LOW, M300_OE_HIGH);

	/* Multi-Purpose Pins Functionality configuration */
	/* (all LEDs & power off active high) */
	u32 kwmpp_config[] = {

		MPP0_GPIO,
		MPP1_SPI_MOSI,
		MPP2_SPI_SCK,
		MPP3_SPI_MISO,
		MPP4_NF_IO6,
		MPP5_NF_IO7,
		MPP6_SYSRST_OUTn,
                MPP7_SPI_SCn,
		MPP8_UART0_RTS,
		MPP9_UART0_CTS,
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
                MPP20_GPIO,
                MPP21_GPIO,
		MPP22_GPIO,
		MPP23_GPIO,
		MPP24_GPIO,
		MPP25_GPIO,
		MPP26_GPIO,
		MPP27_GPIO,
		MPP28_GPIO,
		MPP29_TSMP9,
		MPP30_GPIO,
		MPP31_GPIO,
		MPP32_GPIO,
		MPP33_GPIO,
                MPP34_GPIO,
                MPP35_GPIO,
		MPP34_GPIO,
		MPP35_GPIO,
		MPP36_GPIO,
                MPP37_GPIO,             /* SYS LED (orange) */
                MPP38_GPIO,             /* SYS LED (white)  */
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

#ifdef CONFIG_SHOW_BOOT_PROGRESS
void show_boot_progress(int val)
{
	struct kwgpio_registers *gpio0 = (struct kwgpio_registers *)MVEBU_GPIO0_BASE;
	u32 dout0 = readl(&gpio0->dout);
	u32 blen0 = readl(&gpio0->blink_en);

	struct kwgpio_registers *gpio1 = (struct kwgpio_registers *)MVEBU_GPIO1_BASE;
	u32 dout1 = readl(&gpio1->dout);
	u32 blen1 = readl(&gpio1->blink_en);

	switch (val) {
	case BOOTSTAGE_ID_DECOMP_IMAGE:
		writel(blen1 & ~(SYS_WHITE_LED | SYS_ORANGE_LED), &gpio1->blink_en);
		writel((dout1 & ~SYS_WHITE_LED) | SYS_ORANGE_LED, &gpio1->dout);
		break;
	case BOOTSTAGE_ID_RUN_OS:
		writel(dout0 & ~SYS_ORANGE_LED, &gpio1->dout);
		writel(blen0 | SYS_WHITE_LED, &gpio1->blink_en);
		break;
	case BOOTSTAGE_ID_NET_START:
		break;
	case BOOTSTAGE_ID_NET_LOADED:
		break;
	case -BOOTSTAGE_ID_NET_NETLOOP_OK:
	case -BOOTSTAGE_ID_NET_LOADED:
		break;
	default:
		if (val < 0) {
			/* error */
			printf("Error occured, error code = %d\n", -val);
			writel(dout0 & ~SYS_WHITE_LED, &gpio0->dout);
			writel(blen0 | SYS_ORANGE_LED, &gpio0->blink_en);
		}
		break;
	}
}
#endif
