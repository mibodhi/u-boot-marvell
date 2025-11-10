// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2024 bodhi <mibodhi@gmail.com>
 *
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

/* low GPIO's */
#define USB_POWER		BIT(21)

#define MOI_PLUS_OE_LOW		(~(USB_POWER))
#define MOI_PLUS_VAL_LOW	(USB_POWER)

/* high GPIO's */
#define HDD2_POWER		BIT(15)

#define MOI_PLUS_OE_HIGH	(~(HDD2_POWER))
#define MOI_PLUS_VAL_HIGH	(HDD2_POWER)

int board_early_init_f(void)
{
	/*
	 * default gpio configuration
	 * There are maximum 64 gpios controlled through 2 sets of registers
	 * the below configuration configures mainly initial LED status
	 */
	mvebu_config_gpio(MOI_PLUS_VAL_LOW, MOI_PLUS_VAL_HIGH,
			  MOI_PLUS_OE_LOW, MOI_PLUS_OE_HIGH);

	/* Multi-Purpose Pins Functionality configuration */
	/* (all LEDs & power off active high) */
	u32 kwmpp_config[] = {
		MPP0_NF_IO2,
		MPP1_NF_IO3,
		MPP2_NF_IO4,
		MPP3_NF_IO5,
		MPP4_NF_IO6,
		MPP5_NF_IO7,
		MPP6_SYSRST_OUTn,
		MPP7_GPO,
		MPP8_TW_SDA,		/* PCF8563 RTC chip   */	/* To remove */
		MPP9_TW_SCK,		/* connected to TWSI  */        /* To remove */
		MPP10_UART0_TXD,
		MPP11_UART0_RXD,
		MPP12_GPO,		/* HDD2 LED (green)   */        /* To remove */
		MPP13_GPIO,		/* HDD2 LED (red)     */        /* To remove */
		MPP14_GPIO,		/* MCU DATA pin (in)  */        /* To remove */
		MPP15_GPIO,		/* USB LED (green)    */        /* To remove */
		MPP16_GPIO,		/* MCU CLK pin (out)  */        /* To remove */
		MPP17_GPIO,		/* MCU ACT pin (out)  */        /* To remove */
		MPP18_NF_IO0,
		MPP19_NF_IO1,
		MPP20_GPIO,
		MPP21_GPIO,		/* USB power          */
		MPP22_GPIO,
		MPP23_GPIO,
		MPP24_GPIO,
		MPP25_GPIO,
		MPP26_GPIO,
		MPP27_GPIO,
		MPP28_GPIO,		/* SYS LED (green)    */        /* To remove */
		MPP29_GPIO,		/* SYS LED (orange)   */        /* To remove */
		MPP30_GPIO,
		MPP31_GPIO,
		MPP32_GPIO,
		MPP33_GPIO,
		MPP34_GPIO,
		MPP35_GPIO,
		MPP36_GPIO,		/* reset button       */        /* To remove */
		MPP37_GPIO,		/* copy button        */        /* To remove */
		MPP38_GPIO,		/* VID B0             */        /* To remove */
		MPP39_GPIO,		/* COPY LED (green)   */        /* To remove */
		MPP40_GPIO,		/* COPY LED (red)     */        /* To remove */
		MPP41_GPIO,		/* HDD1 LED (green)   */        /* To remove */
		MPP42_GPIO,		/* HDD1 LED (red)     */        /* To remove */
		MPP43_GPIO,		/* HTP pin            */        /* To remove */
		MPP44_GPIO,		/* buzzer             */        /* To remove */
		MPP45_GPIO,		/* VID B1             */        /* To remove */
		MPP46_GPIO,		/* power button       */        /* To remove */
		MPP47_GPIO,		/* HDD2 power         */
		MPP48_GPIO,		/* power off          */        /* To remove */
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

int board_late_init(void)
{
	/* Do late init to ensure successful enumeration of attached devices */
	pci_init();
	return 0;
}
