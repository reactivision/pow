#include <SDL.h>
#include "game.h"
#include "game-render.h"

static int bind[GAME_NBUTTONS];

static SDL_Window *window;
static SDL_Renderer *renderer;

int game_init(const char *title, int width, int height, int kb[GAME_NBUTTONS])
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return -1;

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		SDL_Quit();
		return -1;
	}
	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) {
		SDL_Quit();
		return -1;
	}
	
	
	SDL_RenderClear(renderer);

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
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = NULL;
	window = NULL;
	SDL_Quit();
}

void game_render(const struct game_output *p)
{
	game_render_draw(p);
	SDL_GL_SwapWindow(window);
}
