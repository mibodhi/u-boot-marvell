// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2017, STMicroelectronics - All Rights Reserved
 * Author(s): Patrice Chotard, <patrice.chotard@foss.st.com> for STMicroelectronics.
 */

#define LOG_CATEGORY UCLASS_RESET

#include <dm.h>
#include <errno.h>
#include <log.h>
#include <malloc.h>
#include <reset-uclass.h>
#include <stm32_rcc.h>
#include <asm/io.h>
#include <dm/device_compat.h>
#include <linux/bitops.h>

/* offset of register without set/clear management */
#define RCC_MP_GCR_OFFSET 0x10C

/* reset clear offset for STM32MP RCC */
#define RCC_CL 0x4

struct stm32_reset_priv {
	fdt_addr_t base;
};

static int stm32_reset_assert(struct reset_ctl *reset_ctl)
{
	struct stm32_reset_priv *priv = dev_get_priv(reset_ctl->dev);
	int bank = (reset_ctl->id / (sizeof(u32) * BITS_PER_BYTE)) * 4;
	int offset = reset_ctl->id % (sizeof(u32) * BITS_PER_BYTE);

	dev_dbg(reset_ctl->dev, "reset id = %ld bank = %d offset = %d)\n",
		reset_ctl->id, bank, offset);

	if (dev_get_driver_data(reset_ctl->dev) == STM32MP1)
		if (bank != RCC_MP_GCR_OFFSET)
			/* reset assert is done in rcc set register */
			writel(BIT(offset), priv->base + bank);
		else
			clrbits_le32(priv->base + bank, BIT(offset));
	else
		setbits_le32(priv->base + bank, BIT(offset));

	return 0;
}

static int stm32_reset_deassert(struct reset_ctl *reset_ctl)
{
	struct stm32_reset_priv *priv = dev_get_priv(reset_ctl->dev);
	int bank = (reset_ctl->id / (sizeof(u32) * BITS_PER_BYTE)) * 4;
	int offset = reset_ctl->id % (sizeof(u32) * BITS_PER_BYTE);

	dev_dbg(reset_ctl->dev, "reset id = %ld bank = %d offset = %d)\n",
		reset_ctl->id, bank, offset);

	if (dev_get_driver_data(reset_ctl->dev) == STM32MP1)
		if (bank != RCC_MP_GCR_OFFSET)
			/* reset deassert is done in rcc clr register */
			writel(BIT(offset), priv->base + bank + RCC_CL);
		else
			setbits_le32(priv->base + bank, BIT(offset));
	else
		clrbits_le32(priv->base + bank, BIT(offset));

	return 0;
}

static const struct reset_ops stm32_reset_ops = {
	.rst_assert	= stm32_reset_assert,
	.rst_deassert	= stm32_reset_deassert,
};

static int stm32_reset_probe(struct udevice *dev)
{
	struct stm32_reset_priv *priv = dev_get_priv(dev);

	priv->base = dev_read_addr(dev);
	if (priv->base == FDT_ADDR_T_NONE) {
		/* for MFD, get address of parent */
		priv->base = dev_read_addr(dev->parent);
		if (priv->base == FDT_ADDR_T_NONE)
			return -EINVAL;
	}

	return 0;
}

U_BOOT_DRIVER(stm32_rcc_reset) = {
	.name			= "stm32_rcc_reset",
	.id			= UCLASS_RESET,
	.probe			= stm32_reset_probe,
	.priv_auto	= sizeof(struct stm32_reset_priv),
	.ops			= &stm32_reset_ops,
};
