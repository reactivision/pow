#include <stdio.h>
#include <stdlib.h>
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

int level_parsef(char *path, float buf[])
{
	char s[8192];
	FILE *fp;
	int n;

	if ((fp = fopen(path, "r")) == NULL)
		return -1;
	n = fread(s, 1, sizeof s - 1, fp);
	buf[n] = '\0';
	n = level_parse(s, buf);
	fclose(fp);
	return n;
}
