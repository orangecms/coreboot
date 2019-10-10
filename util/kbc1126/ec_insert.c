/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2017 Iru Cai <mytbk920423@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <stdio.h>
#include <stdlib.h>

static void usage(const char *s)
{
	printf("insert firmware blob:\n\t"
	       "%s <rom file> <fw file> <offset>\n\n",
	       s);
	printf(
	    "offset can be (example is put it to 0x7ffa00 when ROM is 8MB):\n"
	    "- file offset: 0x7ffa00\n"
	    "- distance to the end of file: -0x600\n"
	    "- the address when ROM is mapped to the end of memory: "
	    "0xfffffa00\n");
	exit(1);
}

static void FseekEnd(FILE *fp, long o)
{
	if (fseek(fp, o, SEEK_END) != 0) {
		puts("fseek() error!\n");
		exit(1);
	}
}

static long negoffset(long a, long romsz)
{
	if (a > 0) {
		if (a & 0x80000000) /* the address in memory, and sizeof(long)
				       is 8 */
			return a - 0x100000000;
		else /* the file offset */
			return a - romsz;
	} else {
		return a;
	}
}

int main(int argc, char *argv[])
{
	FILE *fp, *fw1;
	long offset1;

	if (argc != 4)
		usage(argv[0]);

	fp = fopen(argv[1], "rb+");
	if (fp == NULL) {
		puts("Error opening firmware image!");
		exit(1);
	}

        fw1 = fopen(argv[2], "rb");
        offset1 = strtoul(argv[3], NULL, 0);

        if (fw1 == NULL) {
                puts("Error opening file!");
                exit(1);
        }
	if ((offset1 & 0xff)) {
		puts("The offsets must be aligned to 0x100");
		exit(1);
	}

	long romsz;
	FseekEnd(fp, -1);
	romsz = ftell(fp) + 1;
	printf("size of %s: 0x%lx\n", argv[1], romsz);

	if (romsz & 0xff) {
		puts("The ROM size must be multiple of 0x100");
		exit(1);
	}

	offset1 = negoffset(offset1, romsz);

        /* write fw1 */
        char c;
        FseekEnd(fp, offset1);
        printf("writing to 0x%lx\n", ftell(fp));
        while (fread(&c, 1, 1, fw1) == 1)
                fwrite(&c, 1, 1, fp);
        fclose(fw1);

	fclose(fp);
	return 0;
}
