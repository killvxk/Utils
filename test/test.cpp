#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	WORD wSize; /* in words 0x000D */
	WORD CodePage;
	WORD MaxCharSize; /* 1 or 2 */
	BYTE DefaultChar[MAX_DEFAULTCHAR];
	WCHAR UnicodeDefaultChar;
	WCHAR unknown1;
	WCHAR unknown2;
	BYTE LeadByte[MAX_LEADBYTES];
} NLS_FILE_HEADER;

static size_t
fsize(FILE *f)
{
	size_t p;
	size_t s;

	p = ftell(f);
	fseek(f, 0, SEEK_END);
	s = ftell(f);
	fseek(f, p, SEEK_SET);
	return s;
}

static void *
readfile(char *path, size_t *psize)
{
	FILE *f = fopen(path, "rb");
	size_t s = fsize(f);
	void *p = malloc(s);
	fread(p, 1, s, f);
	fclose(f);
	*psize = s;
	return p;
}

static void
writefile(char *path, void *data, size_t size)
{
	FILE *f = fopen(path, "wb");
	fwrite(data, 1, size, f);
	fclose(f);
}

int main(int argc, char **argv)
{
	size_t s;
	WORD *base;

	base = (WORD *)readfile(argv[1], &s);

	NLS_FILE_HEADER *nls = (NLS_FILE_HEADER *)&base[0];
	printf("Size = %d\n", nls->wSize);
	printf("CodePage = %d\n", nls->CodePage);
	printf("MaxCharSize = %d\n", nls->MaxCharSize);
	printf("DefaultChar = %02x%02x\n", nls->DefaultChar[1], nls->DefaultChar[0]);
	printf("UnicodeDefaultChar = %04x\n", nls->UnicodeDefaultChar);
	printf("unknown1 = %04x\n", nls->unknown1);
	printf("unknown1 = %04x\n", nls->unknown2);
	printf("LeadByte = %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\n", nls->LeadByte[0], nls->LeadByte[1], nls->LeadByte[2], nls->LeadByte[3], nls->LeadByte[4], nls->LeadByte[5], nls->LeadByte[6], nls->LeadByte[7], nls->LeadByte[8], nls->LeadByte[9], nls->LeadByte[10], nls->LeadByte[11]);

	WORD *cp_to_wc_table_size = base + nls->wSize;
	WORD *cp_to_wc_table_base = base + nls->wSize + 1;

	printf("offset of Unicode To CP table in words = %d\n", *cp_to_wc_table_size);

	WORD *primary_table_base = cp_to_wc_table_base;
	printf("primary table\n");
	for (int i = 0; i < 256; ++i)
		printf("0x%02x => U+%04x\n", i, primary_table_base[i]);

	WORD *oem_table_size = primary_table_base + 256;
	WORD *oem_table_base = primary_table_base + 256 + 1;
	printf("oem size = %d\n", *oem_table_size);
	for (int i = 0; i < *oem_table_size; ++i)
		printf("oem[0x%02x] => U+%04x\n", i, oem_table_base[i]);

	WORD *num_of_dbcs_leadbyte_range = oem_table_base + *oem_table_size;
	WORD *dbcs_table_base = oem_table_base + *oem_table_size + 1;
	WORD *dbcs_leadbyte_offs = dbcs_table_base;

	WORD num_of_dbcs_leadbyte = 0;
	if (*num_of_dbcs_leadbyte_range != 0) {
		for (int i = 0; i < 256; ++i) {
			if (dbcs_leadbyte_offs[i] != 0)
				num_of_dbcs_leadbyte++;
		}
	}

	WORD dbcs_table_size = 0;
	if (*num_of_dbcs_leadbyte_range != 0)
		dbcs_table_size = 256 + 256 * num_of_dbcs_leadbyte;

	printf("num_of_dbcs_leadbyte_range = %d\n", *num_of_dbcs_leadbyte_range);
	printf("num_of_dbcs_leadbyte = %d\n", num_of_dbcs_leadbyte);

	if (*num_of_dbcs_leadbyte_range != 0) {
		for (int i = 0; i < 256; ++i)
			printf("off[%d] = %d\n", i, dbcs_leadbyte_offs[i]);
		for (int i = 0; i < 256; ++i) {
			if (dbcs_leadbyte_offs[i] == 0)
				continue;
			for (int j = 0; j < 256; ++j)
				printf("0x%02x%02x => U+%04x\n", i, j, dbcs_table_base[dbcs_leadbyte_offs[i] + j]);
		}
	}

	WORD *p_unknown = cp_to_wc_table_base + *cp_to_wc_table_base;
	printf("p_unknown = %04x\n", *p_unknown);

	WORD *wc_to_cp_table_base2 = cp_to_wc_table_base + *cp_to_wc_table_size ;
	BYTE *wc_to_cp_table_base1 = (BYTE *)wc_to_cp_table_base2;

	for (int i = 0; i < 65536; ++i) {
		if (nls->MaxCharSize == 1)
			printf("offset:%08x U+%04x => 0x%02x\n", (int)&wc_to_cp_table_base1[i]-(int) base,i, wc_to_cp_table_base1[i]);
		else
			printf("offset:%08x U+%04x => 0x%04x\n", (int)&wc_to_cp_table_base2[i]- (int)base, i, wc_to_cp_table_base2[i]);
	}

	return 0;
}