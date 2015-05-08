#include <SDL.h>
#include "game.h"
#include "game-render.h"

int game_init(const char *title, int width, int height)
{
	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO) != 0 ||
	    SDL_SetVideoMode(width, height, 32, SDL_OPENGL) == 0)
		return -1;
	game_render_init(width, height);
	return 0;
}

int game_input(struct game_input *p)
{
	return 0;
}

void game_quit(void)
{
	game_render_quit();
	SDL_Quit();
}

void game_render(const struct game_output *p)
{
	game_render_draw(p);
	SDL_GL_SwapBuffers();
}
