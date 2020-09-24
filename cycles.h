/***
 * Lifted from the parsec library @ https://github.com/gwsystems/ps/.
 *
 * Copyright 2015 by Gabriel Parmer.  All rights reserved.
 * Redistribution of this file is permitted under the BSD 2 clause license.
 *
 * Authors: Gabriel Parmer, gparmer@gwu.edu, 2015
 */

typedef unsigned long long u64_t;
typedef u64_t ps_tsc_t; 	/* our time-stamp counter representation */

static inline ps_tsc_t
ps_tsc(void)
{
	unsigned long a, d, c;

	__asm__ __volatile__("rdtsc" : "=a" (a), "=d" (d), "=c" (c) : : );

	return ((u64_t)d << 32) | (u64_t)a;
}
