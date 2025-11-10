// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2021-2023 bodhi <mibodhi@gmail.com>
 *
 * Based on
 * Copyright (C) 2013 Rafal Kazmierowski
 *
 * Based on NSA320.c Peter Schildmann <linux@schildmann.info>
 * originally written by
 * Marvell Semiconductor <www.marvell.com>
 * Written-by: Prafulla Wadaskar <prafulla@marvell.com>
 */

#include <asm/arch/soc.h>
#include <asm/arch/mpp.h>
#include <netdev.h>
#include <asm/arch/cpu.h>
#include <asm/gpio.h>
#include <asm/io.h>
#include <asm/arch/gpio.h>
#include <asm/mach-types.h>
#include <bootstage.h>
#include <command.h>
#include <init.h>
#include <linux/bitops.h>

DECLARE_GLOBAL_DATA_PTR;

/* GPIO low */
#define SYS_GREEN_LED		(1 << 28)
#define SYS_RED_LED		(1 << 29)
#define SATA2_GREEN_LED		(1 << 12)
#define SATA2_RED_LED		(1 << 13)
#define USB_GREEN_LED		(1 << 15)
#define USB_RED_LED		(1 << 21)

/* GPIO high */
#define SATA1_GREEN_LED		(1 << 9)
#define SATA1_RED_LED		(1 << 10)
#define COPY_GREEN_LED		(1 << 7)
#define COPY_RED_LED		(1 << 8)

#define NSA310_OE_LOW   (0)
#define NSA310_VAL_LOW    (SYS_GREEN_LED)
#define NSA310_OE_HIGH		((COPY_GREEN_LED | COPY_RED_LED | \
                                   SATA1_GREEN_LED | SATA1_RED_LED))
#define NSA310_VAL_HIGH		(0)

int board_early_init_f(void)
{
	/*
	 * default gpio configuration
	 * There are maximum 64 gpios controlled through 2 sets of registers
	 * the below configuration configures mainly initial LED status
	 */
	mvebu_config_gpio(NSA310_VAL_LOW, NSA310_VAL_HIGH,
		       NSA310_OE_LOW, NSA310_OE_HIGH);

	/* Multi-Purpose Pins Functionality configuration */
	/* (all LEDs & power off active high) */
	static const u32 kwmpp_config[] = {
		MPP0_NF_IO2,
		MPP1_NF_IO3,
		MPP2_NF_IO4,
		MPP3_NF_IO5,
		MPP4_NF_IO6,
		MPP5_NF_IO7,
		MPP6_SYSRST_OUTn,
		MPP7_GPO,
		MPP8_TW_SDA,	/* PCF8563 RTC chip   */
		MPP9_TW_SCK,	/* connected to TWSI  */
		MPP10_UART0_TXD,
		MPP11_UART0_RXD,
		MPP12_GPO,		/* SATA2 LED (green)  */
		MPP13_GPIO,		/* SATA2 LED (red)    */
		MPP14_GPIO,		/* MCU DATA pin (in)  */
		MPP15_GPIO,		/* USB LED (green)    */
		MPP16_GPIO,		/* MCU CLK pin (out)  */
		MPP17_GPIO,		/* MCU ACT pin (out)  */
		MPP18_NF_IO0,
		MPP19_NF_IO1,
		MPP20_GPIO,
		MPP21_GPIO,		/* USB LED (red)-Power*/
		MPP22_GPIO,
		MPP23_GPIO,
		MPP24_GPIO,
		MPP25_GPIO,
		MPP26_GPIO,
		MPP27_GPIO,
		MPP28_GPIO,		/* SYS LED (green)    */
		MPP29_GPIO,		/* SYS LED (red)      */
		MPP30_GPIO,
		MPP31_GPIO,
		MPP32_GPIO,
		MPP33_GPIO,
		MPP34_GPIO,
		MPP35_GPIO,
		MPP36_GPIO,		/* Reset button       */
		MPP37_GPIO,		/* Copy button        */
		MPP38_GPIO,		/* VID B0             */
		MPP39_GPIO,		/* COPY LED (green)   */
		MPP40_GPIO,		/* COPY LED (red)     */
		MPP41_GPIO,		/* SATA1 LED (green)  */
		MPP42_GPIO,		/* SATA1 LED (red)    */
		MPP43_GPIO,		/* HTP pin            */
		MPP44_GPIO,		/* Buzzer             */
		MPP45_GPIO,		/* VID B1             */
		MPP46_GPIO,		/* Power button       */
		MPP47_GPIO,		/* Power resume data  */
		MPP48_GPIO,		/* Power off          */
		MPP49_GPIO,		/* Power resume clock */
		0
	};
	kirkwood_mpp_conf(kwmpp_config,NULL);
	return 0;
}

int board_eth_init(struct bd_info *bis)
{
	cpu_eth_init(bis); /* Built in controller(s) come first */
	return pci_eth_init(bis);
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
		writel(blen0 & ~(SYS_GREEN_LED | SYS_RED_LED), &gpio0->blink_en);
		writel((dout0 & ~SYS_GREEN_LED) | SYS_RED_LED, &gpio0->dout);
		break;
	case BOOTSTAGE_ID_RUN_OS:
		writel(dout0 & ~SYS_RED_LED, &gpio0->dout);
		writel(blen0 | SYS_GREEN_LED, &gpio0->blink_en);
		break;
	case BOOTSTAGE_ID_NET_START:
		writel(dout1 & ~COPY_RED_LED, &gpio1->dout);
		writel((blen1 & ~COPY_RED_LED) | COPY_GREEN_LED, &gpio1->blink_en);
		break;
	case BOOTSTAGE_ID_NET_LOADED:
		writel(blen1 & ~(COPY_RED_LED | COPY_GREEN_LED), &gpio1->blink_en);
		writel((dout1 & ~COPY_RED_LED) | COPY_GREEN_LED, &gpio1->dout);
		break;
	case -BOOTSTAGE_ID_NET_NETLOOP_OK:
	case -BOOTSTAGE_ID_NET_LOADED:
		writel(dout1 & ~COPY_GREEN_LED, &gpio1->dout);
		writel((blen1 & ~COPY_GREEN_LED) | COPY_RED_LED, &gpio1->blink_en);
		break;
	default:
		if (val < 0) {
			/* error */
			printf("Error occured, error code = %d\n", -val);
			writel(dout0 & ~SYS_GREEN_LED, &gpio0->dout);
			writel(blen0 | SYS_RED_LED, &gpio0->blink_en);
		}
		break;
	}
}
#endif /* CONFIG_SHOW_BOOT_PROGRESS */
