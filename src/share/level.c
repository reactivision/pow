#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "level.h"

static int for_each_float(const char *s, void fn(float f, void *p), void *p);
static char *read_all(FILE *fin);

int level_parsef(struct level *to, const char *path)
{
	FILE *fin;
	char *s;
	int r;

	if ((fin = fopen(path, "r")) == NULL)
		return -5;  /* unable to open file */
	if ((s = read_all(fin)) == NULL)
		return -4;  /* malloc() failed */
	if (fclose(fin)) {
		free(s);
		return -6;  /* error reading file */
	}
	r = level_parse(to, s);
	free(s);
	return r;
}

static void count(float f, void *data)
{
	long *p;

	(void) f;
	p = data;
	if (*p == LONG_MAX)
		*p = -1;
	else
		*p += (*p >= 0);
}

static void copy(float f, void *data)
{
	float **p;

	p = data;
	**p = f;
	++*p;
}

int level_parse(struct level *to, const char *s)
{
	float *p;

	to->ngeom = 0;
	if (for_each_float(s, count, &to->ngeom))
		return -1;  /* invalid level format */
	if (to->ngeom < 0)
		return -2;  /* the level is too large */
	if (to->ngeom%9 != 0)
		return -3;  /* incomplete triangle */
	if ((to->geom = malloc(to->ngeom * sizeof *to->geom)) == NULL)
		return -4;  /* malloc() failed */
	p = to->geom;
	for_each_float(s, copy, &p);
	return 0;
}

int for_each_float(const char *s, void fn(float f, void *p), void *p)
{
	char *tmp;
	float f;

	errno = 0;
	for (tmp = NULL; f = strtod(s, &tmp), s != tmp; s = tmp)
		if (errno != 0)
			return -1;
		else
			fn(f, p);
	return -(s[strspn(s, " \n\r\t")] != '\0');
}

char *read_all(FILE *fin)
{
	char buf[BUFSIZ];
	size_t n, m;
	char *s, *t;

	s = NULL, m = 0;
	while ((n = fread(buf, 1, sizeof buf, fin)) == sizeof buf) {
		if ((t = realloc(s, m + n)) == NULL)
			goto error;
		memcpy(t + m, buf, n);
		s = t, m += n;
	}
	if ((t = realloc(s, m + n + 1)) == NULL)
		goto error;
	memcpy(t + m, buf, n);
	t[m + n] = '\0';
	return t;
error:
	free(s);
	return NULL;
}
