#include <SDL.h>
#include "game.h"
#include "game-render.h"

static int bind[GAME_NBUTTONS];

int game_init(const char *title, int width, int height, int kb[GAME_NBUTTONS])
{
	int flags;

	flags = SDL_OPENGL;
	flags |= SDL_GL_DOUBLEBUFFER;
	flags |= SDL_HWSURFACE;
	flags |= SDL_GL_SWAP_CONTROL;
	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO) != 0)
		return -1;
	if (SDL_SetVideoMode(width, height, 32, flags) == NULL) {
		SDL_Quit();
		return -1;
	}
	SDL_WM_SetCaption(title, title);
	memcpy(bind, kb, sizeof bind);
	game_render_init(width, height);
	return 0;
}

static void set(int state[GAME_NBUTTONS], int button, int value)
{
	int i;

	for (i = 0; i < GAME_NBUTTONS; i++)
		if (bind[i] == button)
			state[i] = value;
}

int game_input(int state[GAME_NBUTTONS])
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
			return -1;
		if (event.type == SDL_KEYUP)
			set(state, event.key.keysym.sym, 0);
		if (event.type == SDL_KEYDOWN)
			set(state, event.key.keysym.sym, 1);
	}
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
