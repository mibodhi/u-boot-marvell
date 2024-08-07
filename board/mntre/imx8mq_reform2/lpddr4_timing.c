/*
 * Copyright 2019 NXP
 *
 * SPDX-License-Identifier:	GPL-2.0+
 *
 * Generated code from MX8M_DDR_tool
 * Align with uboot version:
 * imx_v2018.03_4.14.78_1.0.0_ga ~ imx_v2018.04_4.19.35_1.0.0_ga
 */
#include "lpddr4_timing_ch2.h"

static struct dram_cfg_param lpddr4_ddrc_cfg[] = {
	/** Initialize DDRC registers **/
	{ DDRC_DBG1(0), 1 },
	/* selfref_en=1, SDRAM enter self-refresh state */
	{ DDRC_PWRCTL(0), 1 },
	{ DDRC_MSTR(0), 0xa0080020 | (CH2_LPDDR4_CS << 24) },
	{ DDRC_MSTR2(0), 0 },
	{ DDRC_DERATEEN(0), 0x0203 },
	{ DDRC_DERATEINT(0), 0x0003e800 },
	{ DDRC_RFSHTMG(0), 0x006100e0 },
	{ DDRC_INIT0(0), 0xc003061c },
	{ DDRC_INIT1(0), 0x009e0000 },
	{ DDRC_INIT3(0), 0x00d4002d },
	{ DDRC_INIT4(0), CH2_VAL_INIT4 },
	{ DDRC_INIT6(0), 0x0066004a },
	{ DDRC_INIT7(0), 0x0016004a },
	{ DDRC_DRAMTMG0(0), 0x1a201b22 },
	{ DDRC_DRAMTMG1(0), 0x00060633 },
	{ DDRC_DRAMTMG3(0), 0x00c0c000 },
	{ DDRC_DRAMTMG4(0), 0x0f04080f },
	{ DDRC_DRAMTMG5(0), 0x02040c0c },
	{ DDRC_DRAMTMG6(0), 0x01010007 },
	{ DDRC_DRAMTMG7(0), 0x0401 },
	{ DDRC_DRAMTMG12(0), 0x00020600 },
	{ DDRC_DRAMTMG13(0), 0x0c100002 },
	{ DDRC_DRAMTMG14(0), 0xe6 },
	{ DDRC_DRAMTMG17(0), 0x00a00050 },
	{ DDRC_ZQCTL0(0), 0xc3200018 },
	{ DDRC_ZQCTL1(0), 0x028061a8 },
	{ DDRC_ZQCTL2(0), 0 },
	{ DDRC_DFITMG0(0), 0x0497820a },
	{ DDRC_DFITMG1(0), 0x00080303 },
	{ DDRC_DFIUPD0(0), 0xe0400018 },
	{ DDRC_DFIUPD1(0), 0x00df00e4 },
	{ DDRC_DFIUPD2(0), 0x80000000 },
	{ DDRC_DFIMISC(0), 0x11 },
	{ DDRC_DFITMG2(0), 0x170a },
	{ DDRC_DBICTL(0), 1 },
	{ DDRC_DFIPHYMSTR(0), 1 },
	{ DDRC_RANKCTL(0), 0x0639 },
	{ DDRC_DRAMTMG2(0), 0x070e1617 },

	/* address mapping */
	{ DDRC_ADDRMAP0(0), CH2_VAL_DDRC_ADDRMAP0 },
	{ DDRC_ADDRMAP3(0), 0 },
	/* addrmap_col_b10 and addrmap_col_b11 set to de-activated (5-bit width) */
	{ DDRC_ADDRMAP4(0), 0x1f1f },
	/* bank interleave */
	/* addrmap_bank_b2, addrmap_bank_b1, addrmap_bank_b0 */
	{ DDRC_ADDRMAP1(0), 0x00080808 },
	/* addrmap_row_b11, addrmap_row_b10_b2, addrmap_row_b1, addrmap_row_b0 */
	{ DDRC_ADDRMAP5(0), 0x07070707 },
	/* addrmap_row_b15, addrmap_row_b14, addrmap_row_b13, addrmap_row_b12 */
	{ DDRC_ADDRMAP6(0), CH2_VAL_DDRC_ADDRMAP6 },
	{ DDRC_ADDRMAP7(0), 0x0f0f },
	{ DDRC_FREQ1_DERATEEN(0), 1 },
	{ DDRC_FREQ1_DERATEINT(0), 0xd0c0 },
	{ DDRC_FREQ1_RFSHCTL0(0), 0x0020d040 },
	{ DDRC_FREQ1_RFSHTMG(0), 0x0014002f },
	{ DDRC_FREQ1_INIT3(0), 0x00940009 },
	{ DDRC_FREQ1_INIT4(0), CH2_VAL_INIT4 },
	{ DDRC_FREQ1_INIT6(0), 0x0066004a },
	{ DDRC_FREQ1_INIT7(0), 0x0016004a },
	{ DDRC_FREQ1_DRAMTMG0(0), 0x0b070508 },
	{ DDRC_FREQ1_DRAMTMG1(0), 0x0003040b },
	{ DDRC_FREQ1_DRAMTMG2(0), 0x0305090c },
	{ DDRC_FREQ1_DRAMTMG3(0), 0x00505000 },
	{ DDRC_FREQ1_DRAMTMG4(0), 0x04040204 },
	{ DDRC_FREQ1_DRAMTMG5(0), 0x02030303 },
	{ DDRC_FREQ1_DRAMTMG6(0), 0x01010004 },
	{ DDRC_FREQ1_DRAMTMG7(0), 0x0301 },
	{ DDRC_FREQ1_DRAMTMG12(0), 0x00020300 },
	{ DDRC_FREQ1_DRAMTMG13(0), 0x0a100002 },
	{ DDRC_FREQ1_DRAMTMG14(0), 0x31 },
	{ DDRC_FREQ1_DRAMTMG17(0), 0x00220011 },
	{ DDRC_FREQ1_ZQCTL0(0), 0xc0a70006 },
	{ DDRC_FREQ1_DFITMG0(0), 0x03858202 },
	{ DDRC_FREQ1_DFITMG1(0), 0x00080303 },
	{ DDRC_FREQ1_DFITMG2(0), 0x0502 },
	{ DDRC_ODTMAP(0), 0 },
	{ DDRC_SCHED(0), 0x29001505 },
	{ DDRC_SCHED1(0), 0x2c },
	{ DDRC_PERFHPR1(0), 0x5900575b },
	{ DDRC_PERFLPR1(0), 0x90000096 },
	{ DDRC_PERFWR1(0), 0x1000012c },
	{ DDRC_DBG0(0), 0x16 },
	{ DDRC_DBG1(0), 0 },
	{ DDRC_DBGCMD(0), 0 },
	{ DDRC_SWCTL(0), 1 },
	{ DDRC_POISONCFG(0), 0x11 },
	{ DDRC_PCCFG(0), 0x0111 },
	{ DDRC_PCFGR_0(0), 0x10f3 },
	{ DDRC_PCFGW_0(0), 0x72ff },
	{ DDRC_PCTRL_0(0), 1 },
	{ DDRC_PCFGQOS0_0(0), 0x0e00 },
	{ DDRC_PCFGQOS1_0(0), 0x0062ffff },
	{ DDRC_PCFGWQOS0_0(0), 0x0e00 },
	{ DDRC_PCFGWQOS1_0(0), 0xffff },
};

/* PHY Initialize Configuration */
static struct dram_cfg_param lpddr4_ddrphy_cfg[] = {
	{ 0x100a0, 0 },
	{ 0x100a1, 1 },
	{ 0x100a2, 2 },
	{ 0x100a3, 3 },
	{ 0x100a4, 4 },
	{ 0x100a5, 5 },
	{ 0x100a6, 6 },
	{ 0x100a7, 7 },
	{ 0x110a0, 0 },
	{ 0x110a1, 1 },
	{ 0x110a2, 2 },
	{ 0x110a3, 3 },
	{ 0x110a4, 4 },
	{ 0x110a5, 5 },
	{ 0x110a6, 6 },
	{ 0x110a7, 7 },
	{ 0x120a0, 0 },
	{ 0x120a1, 1 },
	{ 0x120a2, 2 },
	{ 0x120a3, 3 },
	{ 0x120a4, 4 },
	{ 0x120a5, 5 },
	{ 0x120a6, 6 },
	{ 0x120a7, 7 },
	{ 0x130a0, 0 },
	{ 0x130a1, 1 },
	{ 0x130a2, 2 },
	{ 0x130a3, 3 },
	{ 0x130a4, 4 },
	{ 0x130a5, 5 },
	{ 0x130a6, 6 },
	{ 0x130a7, 7 },
	{ 0x1005f, 0x01ff },
	{ 0x1015f, 0x01ff },
	{ 0x1105f, 0x01ff },
	{ 0x1115f, 0x01ff },
	{ 0x1205f, 0x01ff },
	{ 0x1215f, 0x01ff },
	{ 0x1305f, 0x01ff },
	{ 0x1315f, 0x01ff },
	{ 0x11005f, 0x01ff },
	{ 0x11015f, 0x01ff },
	{ 0x11105f, 0x01ff },
	{ 0x11115f, 0x01ff },
	{ 0x11205f, 0x01ff },
	{ 0x11215f, 0x01ff },
	{ 0x11305f, 0x01ff },
	{ 0x11315f, 0x01ff },
	{ 0x0055, 0x01ff },
	{ 0x1055, 0x01ff },
	{ 0x2055, 0x01ff },
	{ 0x3055, 0x01ff },
	{ 0x4055, 0x01ff },
	{ 0x5055, 0x01ff },
	{ 0x6055, 0x01ff },
	{ 0x7055, 0x01ff },
	{ 0x8055, 0x01ff },
	{ 0x9055, 0x01ff },
	{ 0x200c5, 0x19 },
	{ 0x1200c5, 7 },
	{ 0x2002e, 2 },
	{ 0x12002e, 1 },
	{ 0x90204, 0 },
	{ 0x190204, 0 },
	{ 0x20024, 0x01ab },
	{ 0x2003a, 0 },
	{ 0x120024, 0x01ab },
	{ 0x2003a, 0 },
	{ 0x20056, 3 },
	{ 0x120056, 3 },
	{ 0x1004d, 0x0e00 },
	{ 0x1014d, 0x0e00 },
	{ 0x1104d, 0x0e00 },
	{ 0x1114d, 0x0e00 },
	{ 0x1204d, 0x0e00 },
	{ 0x1214d, 0x0e00 },
	{ 0x1304d, 0x0e00 },
	{ 0x1314d, 0x0e00 },
	{ 0x11004d, 0x0e00 },
	{ 0x11014d, 0x0e00 },
	{ 0x11104d, 0x0e00 },
	{ 0x11114d, 0x0e00 },
	{ 0x11204d, 0x0e00 },
	{ 0x11214d, 0x0e00 },
	{ 0x11304d, 0x0e00 },
	{ 0x11314d, 0x0e00 },
	{ 0x10049, 0x0eba },
	{ 0x10149, 0x0eba },
	{ 0x11049, 0x0eba },
	{ 0x11149, 0x0eba },
	{ 0x12049, 0x0eba },
	{ 0x12149, 0x0eba },
	{ 0x13049, 0x0eba },
	{ 0x13149, 0x0eba },
	{ 0x110049, 0x0eba },
	{ 0x110149, 0x0eba },
	{ 0x111049, 0x0eba },
	{ 0x111149, 0x0eba },
	{ 0x112049, 0x0eba },
	{ 0x112149, 0x0eba },
	{ 0x113049, 0x0eba },
	{ 0x113149, 0x0eba },
	{ 0x0043, 0x63 },
	{ 0x1043, 0x63 },
	{ 0x2043, 0x63 },
	{ 0x3043, 0x63 },
	{ 0x4043, 0x63 },
	{ 0x5043, 0x63 },
	{ 0x6043, 0x63 },
	{ 0x7043, 0x63 },
	{ 0x8043, 0x63 },
	{ 0x9043, 0x63 },
	{ 0x20018, 3 },
	{ 0x20075, 4 },
	{ 0x20050, 0 },
	{ 0x20008, 0x0320 },
	{ 0x120008, 0xa7 },
	{ 0x20088, 9 },
	{ 0x200b2, 0xdc },
	{ 0x10043, 0x05a1 },
	{ 0x10143, 0x05a1 },
	{ 0x11043, 0x05a1 },
	{ 0x11143, 0x05a1 },
	{ 0x12043, 0x05a1 },
	{ 0x12143, 0x05a1 },
	{ 0x13043, 0x05a1 },
	{ 0x13143, 0x05a1 },
	{ 0x1200b2, 0xdc },
	{ 0x110043, 0x05a1 },
	{ 0x110143, 0x05a1 },
	{ 0x111043, 0x05a1 },
	{ 0x111143, 0x05a1 },
	{ 0x112043, 0x05a1 },
	{ 0x112143, 0x05a1 },
	{ 0x113043, 0x05a1 },
	{ 0x113143, 0x05a1 },
	{ 0x200fa, 1 },
	{ 0x1200fa, 1 },
	{ 0x20019, 1 },
	{ 0x120019, 1 },
	{ 0x200f0, 0 },
	{ 0x200f1, 0 },
	{ 0x200f2, 0x4444 },
	{ 0x200f3, 0x8888 },
	{ 0x200f4, 0x5555 },
	{ 0x200f5, 0 },
	{ 0x200f6, 0 },
	{ 0x200f7, 0xf000 },
	{ 0x20025, 0 },
	{ 0x2002d, 0 },
	{ 0x12002d, 0 },
	{ 0x200c7, 0x80 },
	{ 0x1200c7, 0x80 },
	{ 0x200ca, 0x0106 },
	{ 0x1200ca, 0x0106 },
	{ 0x20110, 2 },
	{ 0x20111, 3 },
	{ 0x20112, 4 },
	{ 0x20113, 5 },
	{ 0x20114, 0 },
	{ 0x20115, 1 },
};

/* P0 message block parameter for training firmware */
static struct dram_cfg_param lpddr4_fsp0_cfg[] = {
	{ 0xd0000, 0 },
	{ 0x54003, 0x0c80 },
	{ 0x54004, 2 },
	{ 0x54005, 0x2228 },
	{ 0x54006, LPDDR4_PHY_VREF_VALUE },
	{ 0x54008, 0x131f },
	{ 0x54009, LPDDR4_HDT_CTL_3200_1D },
	{ 0x5400b, 2 },
	{ 0x54012, 0x10 | (CH2_LPDDR4_CS << 8) },
	{ 0x54019, 0x2dd4 },
	{ 0x5401a, 0x31 },
	{ 0x5401b, 0x4a66 },
	{ 0x5401c, 0x4a08 },
	{ 0x5401e, 0x16 },
	{ 0x5401f, 0x2dd4 },
	{ 0x54020, 0x31 },
	{ 0x54021, 0x4a66 },
	{ 0x54022, 0x4a08 },
	{ 0x54024, 0x16 },
	{ 0x5402b, 0x1000 },
	{ 0x5402c, CH2_LPDDR4_CS },
	{ 0x54032, 0xd400 },
	{ 0x54033, 0x312d },
	{ 0x54034, 0x6600 },
	{ 0x54035, 0x084a },
	{ 0x54036, 0x4a },
	{ 0x54037, 0x1600 },
	{ 0x54038, 0xd400 },
	{ 0x54039, 0x312d },
	{ 0x5403a, 0x6600 },
	{ 0x5403b, 0x084a },
	{ 0x5403c, 0x4a },
	{ 0x5403d, 0x1600 },
	{ 0xd0000, 1 },
};

/* P1 message block parameter for training firmware */
static struct dram_cfg_param lpddr4_fsp1_cfg[] = {
	{ 0xd0000, 0 },
	{ 0x54002, 1 },
	{ 0x54003, 0x029c },
	{ 0x54004, 2 },
	{ 0x54005, 0x2228 },
	{ 0x54006, LPDDR4_PHY_VREF_VALUE },
	{ 0x54008, 0x121f },
	{ 0x54009, LPDDR4_HDT_CTL_3200_1D },
	{ 0x5400b, 2 },
	{ 0x54012, 0x10 | (CH2_LPDDR4_CS << 8) },
	{ 0x54019, 0x0994 },
	{ 0x5401a, 0x31 },
	{ 0x5401b, 0x4a66 },
	{ 0x5401c, 0x4a08 },
	{ 0x5401e, 0x16 },
	{ 0x5401f, 0x0994 },
	{ 0x54020, 0x31 },
	{ 0x54021, 0x4a66 },
	{ 0x54022, 0x4a08 },
	{ 0x54024, 0x16 },
	{ 0x5402b, 0x1000 },
	{ 0x5402c, CH2_LPDDR4_CS },
	{ 0x54032, 0x9400 },
	{ 0x54033, 0x3109 },
	{ 0x54034, 0x6600 },
	{ 0x54035, 0x084a },
	{ 0x54036, 0x4a },
	{ 0x54037, 0x1600 },
	{ 0x54038, 0x9400 },
	{ 0x54039, 0x3109 },
	{ 0x5403a, 0x6600 },
	{ 0x5403b, 0x084a },
	{ 0x5403c, 0x4a },
	{ 0x5403d, 0x1600 },
	{ 0xd0000, 1 },
};

/* P0 2D message block parameter for training firmware */
static struct dram_cfg_param lpddr4_fsp0_2d_cfg[] = {
	{ 0xd0000, 0 },
	{ 0x54003, 0x0c80 },
	{ 0x54004, 2 },
	{ 0x54005, 0x2228 },
	{ 0x54006, LPDDR4_PHY_VREF_VALUE },
	{ 0x54008, 0x61 },
	{ 0x54009, LPDDR4_HDT_CTL_3200_1D },
	{ 0x5400b, 2 },
	{ 0x5400d, 0x0100 },
	{ 0x5400f, 0x0100 },
	{ 0x54010, 0x1f7f },
	{ 0x54012, 0x10 | (CH2_LPDDR4_CS << 8) },
	{ 0x54019, 0x2dd4 },
	{ 0x5401a, 0x31 },
	{ 0x5401b, 0x4a66 },
	{ 0x5401c, 0x4a08 },
	{ 0x5401e, 0x16 },
	{ 0x5401f, 0x2dd4 },
	{ 0x54020, 0x31 },
	{ 0x54021, 0x4a66 },
	{ 0x54022, 0x4a08 },
	{ 0x54024, 0x16 },
	{ 0x5402b, 0x1000 },
	{ 0x5402c, CH2_LPDDR4_CS },
	{ 0x54032, 0xd400 },
	{ 0x54033, 0x312d },
	{ 0x54034, 0x6600 },
	{ 0x54035, 0x084a },
	{ 0x54036, 0x4a },
	{ 0x54037, 0x1600 },
	{ 0x54038, 0xd400 },
	{ 0x54039, 0x312d },
	{ 0x5403a, 0x6600 },
	{ 0x5403b, 0x084a },
	{ 0x5403c, 0x4a },
	{ 0x5403d, 0x1600 },
	{ 0xd0000, 1 },
};

/* DRAM PHY init engine image */
static struct dram_cfg_param lpddr4_phy_pie[] = {
	{ 0xd0000, 0 },
	{ 0x90000, 0x10 },
	{ 0x90001, 0x0400 },
	{ 0x90002, 0x010e },
	{ 0x90003, 0 },
	{ 0x90004, 0 },
	{ 0x90005, 8 },
	{ 0x90029, 0x0b },
	{ 0x9002a, 0x0480 },
	{ 0x9002b, 0x0109 },
	{ 0x9002c, 8 },
	{ 0x9002d, 0x0448 },
	{ 0x9002e, 0x0139 },
	{ 0x9002f, 8 },
	{ 0x90030, 0x0478 },
	{ 0x90031, 0x0109 },
	{ 0x90032, 0 },
	{ 0x90033, 0xe8 },
	{ 0x90034, 0x0109 },
	{ 0x90035, 2 },
	{ 0x90036, 0x10 },
	{ 0x90037, 0x0139 },
	{ 0x90038, 0x0f },
	{ 0x90039, 0x07c0 },
	{ 0x9003a, 0x0139 },
	{ 0x9003b, 0x44 },
	{ 0x9003c, 0x0630 },
	{ 0x9003d, 0x0159 },
	{ 0x9003e, 0x014f },
	{ 0x9003f, 0x0630 },
	{ 0x90040, 0x0159 },
	{ 0x90041, 0x47 },
	{ 0x90042, 0x0630 },
	{ 0x90043, 0x0149 },
	{ 0x90044, 0x4f },
	{ 0x90045, 0x0630 },
	{ 0x90046, 0x0179 },
	{ 0x90047, 8 },
	{ 0x90048, 0xe0 },
	{ 0x90049, 0x0109 },
	{ 0x9004a, 0 },
	{ 0x9004b, 0x07c8 },
	{ 0x9004c, 0x0109 },
	{ 0x9004d, 0 },
	{ 0x9004e, 1 },
	{ 0x9004f, 8 },
	{ 0x90050, 0 },
	{ 0x90051, 0x045a },
	{ 0x90052, 9 },
	{ 0x90053, 0 },
	{ 0x90054, 0x0448 },
	{ 0x90055, 0x0109 },
	{ 0x90056, 0x40 },
	{ 0x90057, 0x0630 },
	{ 0x90058, 0x0179 },
	{ 0x90059, 1 },
	{ 0x9005a, 0x0618 },
	{ 0x9005b, 0x0109 },
	{ 0x9005c, 0x40c0 },
	{ 0x9005d, 0x0630 },
	{ 0x9005e, 0x0149 },
	{ 0x9005f, 8 },
	{ 0x90060, 4 },
	{ 0x90061, 0x48 },
	{ 0x90062, 0x4040 },
	{ 0x90063, 0x0630 },
	{ 0x90064, 0x0149 },
	{ 0x90065, 0 },
	{ 0x90066, 4 },
	{ 0x90067, 0x48 },
	{ 0x90068, 0x40 },
	{ 0x90069, 0x0630 },
	{ 0x9006a, 0x0149 },
	{ 0x9006b, 0x10 },
	{ 0x9006c, 4 },
	{ 0x9006d, 0x18 },
	{ 0x9006e, 0 },
	{ 0x9006f, 4 },
	{ 0x90070, 0x78 },
	{ 0x90071, 0x0549 },
	{ 0x90072, 0x0630 },
	{ 0x90073, 0x0159 },
	{ 0x90074, 0x0d49 },
	{ 0x90075, 0x0630 },
	{ 0x90076, 0x0159 },
	{ 0x90077, 0x094a },
	{ 0x90078, 0x0630 },
	{ 0x90079, 0x0159 },
	{ 0x9007a, 0x0441 },
	{ 0x9007b, 0x0630 },
	{ 0x9007c, 0x0149 },
	{ 0x9007d, 0x42 },
	{ 0x9007e, 0x0630 },
	{ 0x9007f, 0x0149 },
	{ 0x90080, 1 },
	{ 0x90081, 0x0630 },
	{ 0x90082, 0x0149 },
	{ 0x90083, 0 },
	{ 0x90084, 0xe0 },
	{ 0x90085, 0x0109 },
	{ 0x90086, 0x0a },
	{ 0x90087, 0x10 },
	{ 0x90088, 0x0109 },
	{ 0x90089, 9 },
	{ 0x9008a, 0x03c0 },
	{ 0x9008b, 0x0149 },
	{ 0x9008c, 9 },
	{ 0x9008d, 0x03c0 },
	{ 0x9008e, 0x0159 },
	{ 0x9008f, 0x18 },
	{ 0x90090, 0x10 },
	{ 0x90091, 0x0109 },
	{ 0x90092, 0 },
	{ 0x90093, 0x03c0 },
	{ 0x90094, 0x0109 },
	{ 0x90095, 0x18 },
	{ 0x90096, 4 },
	{ 0x90097, 0x48 },
	{ 0x90098, 0x18 },
	{ 0x90099, 4 },
	{ 0x9009a, 0x58 },
	{ 0x9009b, 0x0a },
	{ 0x9009c, 0x10 },
	{ 0x9009d, 0x0109 },
	{ 0x9009e, 2 },
	{ 0x9009f, 0x10 },
	{ 0x900a0, 0x0109 },
	{ 0x900a1, 5 },
	{ 0x900a2, 0x07c0 },
	{ 0x900a3, 0x0109 },
	{ 0x900a4, 0x10 },
	{ 0x900a5, 0x10 },
	{ 0x900a6, 0x0109 },
	{ 0x40000, 0x0811 },
	{ 0x40020, 0x0880 },
	{ 0x40040, 0 },
	{ 0x40060, 0 },
	{ 0x40001, 0x4008 },
	{ 0x40021, 0x83 },
	{ 0x40041, 0x4f },
	{ 0x40061, 0 },
	{ 0x40002, 0x4040 },
	{ 0x40022, 0x83 },
	{ 0x40042, 0x51 },
	{ 0x40062, 0 },
	{ 0x40003, 0x0811 },
	{ 0x40023, 0x0880 },
	{ 0x40043, 0 },
	{ 0x40063, 0 },
	{ 0x40004, 0x0720 },
	{ 0x40024, 0x0f },
	{ 0x40044, 0x1740 },
	{ 0x40064, 0 },
	{ 0x40005, 0x16 },
	{ 0x40025, 0x83 },
	{ 0x40045, 0x4b },
	{ 0x40065, 0 },
	{ 0x40006, 0x0716 },
	{ 0x40026, 0x0f },
	{ 0x40046, 0x2001 },
	{ 0x40066, 0 },
	{ 0x40007, 0x0716 },
	{ 0x40027, 0x0f },
	{ 0x40047, 0x2800 },
	{ 0x40067, 0 },
	{ 0x40008, 0x0716 },
	{ 0x40028, 0x0f },
	{ 0x40048, 0x0f00 },
	{ 0x40068, 0 },
	{ 0x40009, 0x0720 },
	{ 0x40029, 0x0f },
	{ 0x40049, 0x1400 },
	{ 0x40069, 0 },
	{ 0x4000a, 0x0e08 },
	{ 0x4002a, 0x0c15 },
	{ 0x4004a, 0 },
	{ 0x4006a, 0 },
	{ 0x4000b, 0x0623 },
	{ 0x4002b, 0x15 },
	{ 0x4004b, 0 },
	{ 0x4006b, 0 },
	{ 0x4000c, 0x4028 },
	{ 0x4002c, 0x80 },
	{ 0x4004c, 0 },
	{ 0x4006c, 0 },
	{ 0x4000d, 0x0e08 },
	{ 0x4002d, 0x0c1a },
	{ 0x4004d, 0 },
	{ 0x4006d, 0 },
	{ 0x4000e, 0x0623 },
	{ 0x4002e, 0x1a },
	{ 0x4004e, 0 },
	{ 0x4006e, 0 },
	{ 0x4000f, 0x4040 },
	{ 0x4002f, 0x80 },
	{ 0x4004f, 0 },
	{ 0x4006f, 0 },
	{ 0x40010, 0x2604 },
	{ 0x40030, 0x15 },
	{ 0x40050, 0 },
	{ 0x40070, 0 },
	{ 0x40011, 0x0708 },
	{ 0x40031, 5 },
	{ 0x40051, 0 },
	{ 0x40071, 0x2002 },
	{ 0x40012, 8 },
	{ 0x40032, 0x80 },
	{ 0x40052, 0 },
	{ 0x40072, 0 },
	{ 0x40013, 0x2604 },
	{ 0x40033, 0x1a },
	{ 0x40053, 0 },
	{ 0x40073, 0 },
	{ 0x40014, 0x0708 },
	{ 0x40034, 0x0a },
	{ 0x40054, 0 },
	{ 0x40074, 0x2002 },
	{ 0x40015, 0x4040 },
	{ 0x40035, 0x80 },
	{ 0x40055, 0 },
	{ 0x40075, 0 },
	{ 0x40016, 0x060a },
	{ 0x40036, 0x15 },
	{ 0x40056, 0x1200 },
	{ 0x40076, 0 },
	{ 0x40017, 0x061a },
	{ 0x40037, 0x15 },
	{ 0x40057, 0x1300 },
	{ 0x40077, 0 },
	{ 0x40018, 0x060a },
	{ 0x40038, 0x1a },
	{ 0x40058, 0x1200 },
	{ 0x40078, 0 },
	{ 0x40019, 0x0642 },
	{ 0x40039, 0x1a },
	{ 0x40059, 0x1300 },
	{ 0x40079, 0 },
	{ 0x4001a, 0x4808 },
	{ 0x4003a, 0x0880 },
	{ 0x4005a, 0 },
	{ 0x4007a, 0 },
	{ 0x900a7, 0 },
	{ 0x900a8, 0x0790 },
	{ 0x900a9, 0x011a },
	{ 0x900aa, 8 },
	{ 0x900ab, 0x07aa },
	{ 0x900ac, 0x2a },
	{ 0x900ad, 0x10 },
	{ 0x900ae, 0x07b2 },
	{ 0x900af, 0x2a },
	{ 0x900b0, 0 },
	{ 0x900b1, 0x07c8 },
	{ 0x900b2, 0x0109 },
	{ 0x900b3, 0x10 },
	{ 0x900b4, 0x02a8 },
	{ 0x900b5, 0x0129 },
	{ 0x900b6, 8 },
	{ 0x900b7, 0x0370 },
	{ 0x900b8, 0x0129 },
	{ 0x900b9, 0x0a },
	{ 0x900ba, 0x03c8 },
	{ 0x900bb, 0x01a9 },
	{ 0x900bc, 0x0c },
	{ 0x900bd, 0x0408 },
	{ 0x900be, 0x0199 },
	{ 0x900bf, 0x14 },
	{ 0x900c0, 0x0790 },
	{ 0x900c1, 0x011a },
	{ 0x900c2, 8 },
	{ 0x900c3, 4 },
	{ 0x900c4, 0x18 },
	{ 0x900c5, 0x0e },
	{ 0x900c6, 0x0408 },
	{ 0x900c7, 0x0199 },
	{ 0x900c8, 8 },
	{ 0x900c9, 0x8568 },
	{ 0x900ca, 0x0108 },
	{ 0x900cb, 0x18 },
	{ 0x900cc, 0x0790 },
	{ 0x900cd, 0x016a },
	{ 0x900ce, 8 },
	{ 0x900cf, 0x01d8 },
	{ 0x900d0, 0x0169 },
	{ 0x900d1, 0x10 },
	{ 0x900d2, 0x8558 },
	{ 0x900d3, 0x0168 },
	{ 0x900d4, 0x70 },
	{ 0x900d5, 0x0788 },
	{ 0x900d6, 0x016a },
	{ 0x900d7, 0x1ff8 },
	{ 0x900d8, 0x85a8 },
	{ 0x900d9, 0x01e8 },
	{ 0x900da, 0x50 },
	{ 0x900db, 0x0798 },
	{ 0x900dc, 0x016a },
	{ 0x900dd, 0x60 },
	{ 0x900de, 0x07a0 },
	{ 0x900df, 0x016a },
	{ 0x900e0, 8 },
	{ 0x900e1, 0x8310 },
	{ 0x900e2, 0x0168 },
	{ 0x900e3, 8 },
	{ 0x900e4, 0xa310 },
	{ 0x900e5, 0x0168 },
	{ 0x900e6, 0x0a },
	{ 0x900e7, 0x0408 },
	{ 0x900e8, 0x0169 },
	{ 0x900e9, 0x6e },
	{ 0x900ea, 0 },
	{ 0x900eb, 0x68 },
	{ 0x900ec, 0 },
	{ 0x900ed, 0x0408 },
	{ 0x900ee, 0x0169 },
	{ 0x900ef, 0 },
	{ 0x900f0, 0x8310 },
	{ 0x900f1, 0x0168 },
	{ 0x900f2, 0 },
	{ 0x900f3, 0xa310 },
	{ 0x900f4, 0x0168 },
	{ 0x900f5, 0x1ff8 },
	{ 0x900f6, 0x85a8 },
	{ 0x900f7, 0x01e8 },
	{ 0x900f8, 0x68 },
	{ 0x900f9, 0x0798 },
	{ 0x900fa, 0x016a },
	{ 0x900fb, 0x78 },
	{ 0x900fc, 0x07a0 },
	{ 0x900fd, 0x016a },
	{ 0x900fe, 0x68 },
	{ 0x900ff, 0x0790 },
	{ 0x90100, 0x016a },
	{ 0x90101, 8 },
	{ 0x90102, 0x8b10 },
	{ 0x90103, 0x0168 },
	{ 0x90104, 8 },
	{ 0x90105, 0xab10 },
	{ 0x90106, 0x0168 },
	{ 0x90107, 0x0a },
	{ 0x90108, 0x0408 },
	{ 0x90109, 0x0169 },
	{ 0x9010a, 0x58 },
	{ 0x9010b, 0 },
	{ 0x9010c, 0x68 },
	{ 0x9010d, 0 },
	{ 0x9010e, 0x0408 },
	{ 0x9010f, 0x0169 },
	{ 0x90110, 0 },
	{ 0x90111, 0x8b10 },
	{ 0x90112, 0x0168 },
	{ 0x90113, 0 },
	{ 0x90114, 0xab10 },
	{ 0x90115, 0x0168 },
	{ 0x90116, 0 },
	{ 0x90117, 0x01d8 },
	{ 0x90118, 0x0169 },
	{ 0x90119, 0x80 },
	{ 0x9011a, 0x0790 },
	{ 0x9011b, 0x016a },
	{ 0x9011c, 0x18 },
	{ 0x9011d, 0x07aa },
	{ 0x9011e, 0x6a },
	{ 0x9011f, 0x0a },
	{ 0x90120, 0 },
	{ 0x90121, 0x01e9 },
	{ 0x90122, 8 },
	{ 0x90123, 0x8080 },
	{ 0x90124, 0x0108 },
	{ 0x90125, 0x0f },
	{ 0x90126, 0x0408 },
	{ 0x90127, 0x0169 },
	{ 0x90128, 0x0c },
	{ 0x90129, 0 },
	{ 0x9012a, 0x68 },
	{ 0x9012b, 9 },
	{ 0x9012c, 0 },
	{ 0x9012d, 0x01a9 },
	{ 0x9012e, 0 },
	{ 0x9012f, 0x0408 },
	{ 0x90130, 0x0169 },
	{ 0x90131, 0 },
	{ 0x90132, 0x8080 },
	{ 0x90133, 0x0108 },
	{ 0x90134, 8 },
	{ 0x90135, 0x07aa },
	{ 0x90136, 0x6a },
	{ 0x90137, 0 },
	{ 0x90138, 0x8568 },
	{ 0x90139, 0x0108 },
	{ 0x9013a, 0xb7 },
	{ 0x9013b, 0x0790 },
	{ 0x9013c, 0x016a },
	{ 0x9013d, 0x1f },
	{ 0x9013e, 0 },
	{ 0x9013f, 0x68 },
	{ 0x90140, 8 },
	{ 0x90141, 0x8558 },
	{ 0x90142, 0x0168 },
	{ 0x90143, 0x0f },
	{ 0x90144, 0x0408 },
	{ 0x90145, 0x0169 },
	{ 0x90146, 0x0c },
	{ 0x90147, 0 },
	{ 0x90148, 0x68 },
	{ 0x90149, 0 },
	{ 0x9014a, 0x0408 },
	{ 0x9014b, 0x0169 },
	{ 0x9014c, 0 },
	{ 0x9014d, 0x8558 },
	{ 0x9014e, 0x0168 },
	{ 0x9014f, 8 },
	{ 0x90150, 0x03c8 },
	{ 0x90151, 0x01a9 },
	{ 0x90152, 3 },
	{ 0x90153, 0x0370 },
	{ 0x90154, 0x0129 },
	{ 0x90155, 0x20 },
	{ 0x90156, 0x02aa },
	{ 0x90157, 9 },
	{ 0x90158, 0 },
	{ 0x90159, 0x0400 },
	{ 0x9015a, 0x010e },
	{ 0x9015b, 8 },
	{ 0x9015c, 0xe8 },
	{ 0x9015d, 0x0109 },
	{ 0x9015e, 0 },
	{ 0x9015f, 0x8140 },
	{ 0x90160, 0x010c },
	{ 0x90161, 0x10 },
	{ 0x90162, 0x8138 },
	{ 0x90163, 0x010c },
	{ 0x90164, 8 },
	{ 0x90165, 0x07c8 },
	{ 0x90166, 0x0101 },
	{ 0x90167, 8 },
	{ 0x90168, 0 },
	{ 0x90169, 8 },
	{ 0x9016a, 8 },
	{ 0x9016b, 0x0448 },
	{ 0x9016c, 0x0109 },
	{ 0x9016d, 0x0f },
	{ 0x9016e, 0x07c0 },
	{ 0x9016f, 0x0109 },
	{ 0x90170, 0 },
	{ 0x90171, 0xe8 },
	{ 0x90172, 0x0109 },
	{ 0x90173, 0x47 },
	{ 0x90174, 0x0630 },
	{ 0x90175, 0x0109 },
	{ 0x90176, 8 },
	{ 0x90177, 0x0618 },
	{ 0x90178, 0x0109 },
	{ 0x90179, 8 },
	{ 0x9017a, 0xe0 },
	{ 0x9017b, 0x0109 },
	{ 0x9017c, 0 },
	{ 0x9017d, 0x07c8 },
	{ 0x9017e, 0x0109 },
	{ 0x9017f, 8 },
	{ 0x90180, 0x8140 },
	{ 0x90181, 0x010c },
	{ 0x90182, 0 },
	{ 0x90183, 1 },
	{ 0x90184, 8 },
	{ 0x90185, 8 },
	{ 0x90186, 4 },
	{ 0x90187, 8 },
	{ 0x90188, 8 },
	{ 0x90189, 0x07c8 },
	{ 0x9018a, 0x0101 },
	{ 0x90006, 0 },
	{ 0x90007, 0 },
	{ 0x90008, 8 },
	{ 0x90009, 0 },
	{ 0x9000a, 0 },
	{ 0x9000b, 0 },
	{ 0xd00e7, 0x0400 },
	{ 0x90017, 0 },
	{ 0x9001f, 0x2a },
	{ 0x90026, 0x6a },
	{ 0x400d0, 0 },
	{ 0x400d1, 0x0101 },
	{ 0x400d2, 0x0105 },
	{ 0x400d3, 0x0107 },
	{ 0x400d4, 0x010f },
	{ 0x400d5, 0x0202 },
	{ 0x400d6, 0x020a },
	{ 0x400d7, 0x020b },
	{ 0x2003a, 2 },
	{ 0x2000b, 0x64 },
	{ 0x2000c, 0xc8 },
	{ 0x2000d, 0x07d0 },
	{ 0x2000e, 0x2c },
	{ 0x12000b, 0x14 },
	{ 0x12000c, 0x29 },
	{ 0x12000d, 0x01a1 },
	{ 0x12000e, 0x10 },
	{ 0x9000c, 0 },
	{ 0x9000d, 0x0173 },
	{ 0x9000e, 0x60 },
	{ 0x9000f, 0x6110 },
	{ 0x90010, 0x2152 },
	{ 0x90011, 0xdfbd },
	{ 0x90012, 0x60 },
	{ 0x90013, 0x6152 },
	{ 0x20010, 0x5a },
	{ 0x20011, 3 },
	{ 0x40080, 0xe0 },
	{ 0x40081, 0x12 },
	{ 0x40082, 0xe0 },
	{ 0x40083, 0x12 },
	{ 0x40084, 0xe0 },
	{ 0x40085, 0x12 },
	{ 0x140080, 0xe0 },
	{ 0x140081, 0x12 },
	{ 0x140082, 0xe0 },
	{ 0x140083, 0x12 },
	{ 0x140084, 0xe0 },
	{ 0x140085, 0x12 },
	{ 0x400fd, 0x0f },
	{ 0x10011, 1 },
	{ 0x10012, 1 },
	{ 0x10013, 0x0180 },
	{ 0x10018, 1 },
	{ 0x10002, 0x6209 },
	{ 0x100b2, 1 },
	{ 0x101b4, 1 },
	{ 0x102b4, 1 },
	{ 0x103b4, 1 },
	{ 0x104b4, 1 },
	{ 0x105b4, 1 },
	{ 0x106b4, 1 },
	{ 0x107b4, 1 },
	{ 0x108b4, 1 },
	{ 0x11011, 1 },
	{ 0x11012, 1 },
	{ 0x11013, 0x0180 },
	{ 0x11018, 1 },
	{ 0x11002, 0x6209 },
	{ 0x110b2, 1 },
	{ 0x111b4, 1 },
	{ 0x112b4, 1 },
	{ 0x113b4, 1 },
	{ 0x114b4, 1 },
	{ 0x115b4, 1 },
	{ 0x116b4, 1 },
	{ 0x117b4, 1 },
	{ 0x118b4, 1 },
	{ 0x12011, 1 },
	{ 0x12012, 1 },
	{ 0x12013, 0x0180 },
	{ 0x12018, 1 },
	{ 0x12002, 0x6209 },
	{ 0x120b2, 1 },
	{ 0x121b4, 1 },
	{ 0x122b4, 1 },
	{ 0x123b4, 1 },
	{ 0x124b4, 1 },
	{ 0x125b4, 1 },
	{ 0x126b4, 1 },
	{ 0x127b4, 1 },
	{ 0x128b4, 1 },
	{ 0x13011, 1 },
	{ 0x13012, 1 },
	{ 0x13013, 0x0180 },
	{ 0x13018, 1 },
	{ 0x13002, 0x6209 },
	{ 0x130b2, 1 },
	{ 0x131b4, 1 },
	{ 0x132b4, 1 },
	{ 0x133b4, 1 },
	{ 0x134b4, 1 },
	{ 0x135b4, 1 },
	{ 0x136b4, 1 },
	{ 0x137b4, 1 },
	{ 0x138b4, 1 },
	{ 0x2003a, 2 },
	{ 0xc0080, 2 },
	{ 0xd0000, 1 }
};

static struct dram_fsp_msg lpddr4_dram_fsp_msg[] = {
	{
		/* P0 3200mts 1D */
		.drate = 3200,
		.fw_type = FW_1D_IMAGE,
		.fsp_cfg = lpddr4_fsp0_cfg,
		.fsp_cfg_num = ARRAY_SIZE(lpddr4_fsp0_cfg),
	},
	{
		/* P1 667mts 1D */
		.drate = 667,
		.fw_type = FW_1D_IMAGE,
		.fsp_cfg = lpddr4_fsp1_cfg,
		.fsp_cfg_num = ARRAY_SIZE(lpddr4_fsp1_cfg),
	},
	{
		/* P0 3200mts 2D */
		.drate = 3200,
		.fw_type = FW_2D_IMAGE,
		.fsp_cfg = lpddr4_fsp0_2d_cfg,
		.fsp_cfg_num = ARRAY_SIZE(lpddr4_fsp0_2d_cfg),
	},
};

/* ddr timing config params */
struct dram_timing_info dram_timing_ch2 = {
	.ddrc_cfg = lpddr4_ddrc_cfg,
	.ddrc_cfg_num = ARRAY_SIZE(lpddr4_ddrc_cfg),
	.ddrphy_cfg = lpddr4_ddrphy_cfg,
	.ddrphy_cfg_num = ARRAY_SIZE(lpddr4_ddrphy_cfg),
	.fsp_msg = lpddr4_dram_fsp_msg,
	.fsp_msg_num = ARRAY_SIZE(lpddr4_dram_fsp_msg),
	.ddrphy_pie = lpddr4_phy_pie,
	.ddrphy_pie_num = ARRAY_SIZE(lpddr4_phy_pie),
	.fsp_table = { 3200, 667, },
};
