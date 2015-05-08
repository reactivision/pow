#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "game.h"

static void error(char *fmt, ...)
{
	va_list arg;
	va_start(arg, fmt);
	vfprintf(stderr, fmt, arg);
	va_end(arg);
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	int c;
	static float buf[8192];

	if (argc != 2)
		error("usage: thps2 [.raw file]\n");
	if (game_init() == -1)
		error("couldn't initialise game context\n");
	if ((c = game_parse(argv[1], buf)) == -1)
		error("couldn't parse .raw file\n");
	for (;;)
		loop(buf, c);
	game_quit();
	return 0;
}
