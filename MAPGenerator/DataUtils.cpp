#define _CRT_SECURE_NO_WARNINGS

#include "DataUtils.h"

char* SetTimeGMT(struct tm* gm)
{
	char s[40];
	char* tmp;

	for (int i = 0; i < 40; i++)
	{
		s[i] = 0;
	}

	int length = strftime(s, 40, "%a %b %e %H:%M:%S %Y", gm);
	tmp = (char*)malloc(sizeof(s));
	strcpy(tmp, s);

	return(tmp);
}