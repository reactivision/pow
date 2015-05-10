#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "game-render.h"
#include "level.h"

#define BUTTON_BINDINGS { 'w', 's', 'a', 'd', ' ', 'k', 'j', 'l', 'm', 'p' }
#define WINDOW_WIDTH   800
#define WINDOW_HEIGHT  600

static char *button_name[] = {
	"Up", "Down", "Left", "Right",
	"Ollie", "Grind", "Grab", "Flip", "LSpin", "RSpin"
};

static int button_bind[] = BUTTON_BINDINGS;

static void update(int *old, int *new)
{
	int i;

	for (i = 0; i < GAME_NBUTTONS; i++)
		if (old[i] != new[i])
			printf("%s: %s\n", button_name[i],
			       new[i] ? "press" : "release");
}

int main(void)
{
	struct game_output output = { 0 };
	int state[GAME_NBUTTONS] = { 0 };
	int old[GAME_NBUTTONS];
	static float buf[8192];
	int v;

	if (game_init(CLIENT_NAME, WINDOW_WIDTH, WINDOW_HEIGHT, button_bind)) {
		fprintf(stderr, "error: game_init failed\n");
		return EXIT_FAILURE;
	}
	if ((v = level_parsef("cube.lff", buf)) <= 0) {
		fprintf(stderr, "error: can't read cube.lff\n");
		game_quit();
		return EXIT_FAILURE;
	}
	output.v = v;
	output.buf = buf;
	memcpy(old, state, sizeof old);
	while (!game_input(state)) {
		update(old, state);
		memcpy(old, state, sizeof old);
		game_render(&output);
	}
	game_quit();
	return 0;
}
