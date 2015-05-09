#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "level.h"

int level_parse(char *s, float buf[])
{
	char *p, *tmp;
	int i;

	i = 0;
	p = s;
	for (tmp = NULL; (buf[i] = strtod(p, &tmp), p != tmp); p = tmp)
		i++;
	return i;
}

char *level_readfile(char *path)
{
	FILE *fp;
	static char s[8192];

	if ((fp = fopen(path, "r")) == NULL)
		return NULL;
	fread(s, 1, sizeof s, fp);
	fclose(fp);
	return s;
}
	
