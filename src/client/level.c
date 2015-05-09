#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "level.h"

int level_parse(char *s, double buf[])
{
	char *p, *tmp;
	int i;

	i = 0;
	p = s;
	for (tmp = NULL; (buf[i] = strtod(p, &tmp), p != tmp); p = tmp)
		i++;
	return i;
}
