// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2023 bodhi <mibodhi@gmail.com>
 */

#include <stdio_dev.h>

/*
 * If overwrite_console returns 1, the stdin, stderr and stdout
 * are switched to the serial port, else the settings in the
 * environment are used
 */
int overwrite_console(void)
{
	printf ("Resetting console stdin/stdout/stderr to serial...\n");
	return 1;
}
