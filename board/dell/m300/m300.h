// SPDX-License-Identifier: GPL-2.0+ 
/*
 * Copyright (C) 2014-2025 Tony Dinh <mibodhi@gmail.com>
 */

#ifndef __M300_H
#define __M300_H

/* low GPIO's 30 21 */

#define GPIO_21          (1 << 21)
#define GPIO_30          (1 << 30)

#define M300_OE_LOW		(~(GPIO_21 | GPIO_30))
#define M300_OE_VAL_LOW		(GPIO_21 | GPIO_30)

/* high GPIO's 48 40 39 38 37 */

#define SYS_ORANGE_LED	(1 << 5)
#define SYS_WHITE_LED	(1 << 6)
#define GPIO_39		(1 << 7)
#define GPIO_40		(1 << 8)
#define GPIO_48		(1 << 16)

#define M300_OE_HIGH		(~(SYS_ORANGE_LED | SYS_WHITE_LED | GPIO_39 | GPIO_40 | GPIO_48))
#define M300_OE_VAL_HIGH	(SYS_ORANGE_LED | SYS_WHITE_LED | GPIO_39 | GPIO_40 | GPIO_48)


/* PHY related */
#define MV88E1318_PGADR_REG		22
#define MV88E1318_MAC_CTRL_PG	2
#define MV88E1318_MAC_CTRL_REG	21
#define MV88E1318_RGMII_TXTM_CTRL	(1 << 4)
#define MV88E1318_RGMII_RXTM_CTRL	(1 << 5)
#define MV88E1318_LED_PG        3
#define MV88E1318_LED_POL_REG	17
#define MV88E1318_LED2_4	(1 << 4)
#define MV88E1318_LED2_5	(1 << 5)

/* Button GPIO's */

#define BTN_RESET		41

#endif /* __M300_H */
