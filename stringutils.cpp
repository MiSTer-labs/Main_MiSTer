#include <inttypes.h>
#include <string.h>

#include "stringutils.h"

void strncpy_pad(char* pStr1, const char* pStr2, size_t nCount)
{
	// customized strncpy() function to fill remaing destination string part with spaces
	while (*pStr2 && nCount)
	{
		*pStr1++ = *pStr2++; // copy strings
		nCount--;
	}
	while (nCount--)
		*pStr1++ = ' '; // fill remaining space with spaces
}

void trim(char * s)
{
	char *p = s;
	int l = strlen(p);
	if (!l) return;

	while (p[l - 1] == ' ') p[--l] = 0;
	while (*p && (*p == ' ')) ++p, --l;

	memmove(s, p, l + 1);
}

