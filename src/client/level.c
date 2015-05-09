#include <stdio.h>
#include "level.h"

int level_parse(char *s, float *buf)
{
	int i;

	for (i = 0; sscanf(s, "%f", &buf[i]) == 1; i++)
		;
	return i;
}
