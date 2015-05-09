#include "game.h"

int game_init(const char *title, int width, int height, int bind[GAME_NBUTTONS])
{
	(void) title;
	(void) width;
	(void) height;
	(void) bind;
	return 0;
}

int game_input(int state[GAME_NBUTTONS])
{
	(void) state;
	return -1;
}

void game_quit(void)
{
}

void game_render(const struct game_output *p)
{
	(void) p;
}
