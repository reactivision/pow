#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "game-render.h"
#include "level.h"

#define BUTTON_BINDINGS { 'w', 's', 'a', 'd', ' ', 'k', 'j', 'l', 'm', 'p' }
#define WINDOW_WIDTH   800
#define WINDOW_HEIGHT  600
#define SPEED 0.1

enum {
	FLOOR, SKATER
};

static char *button_name[] = {
	"Up", "Down", "Left", "Right",
	"Ollie", "Grind", "Grab", "Flip", "LSpin", "RSpin"
};

static char *file[] = {
	"cube.lff", "sphere.lff", NULL
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

static void skate(int state[GAME_NBUTTONS], struct game_output *p)
{
	if (state[GAME_LEFT])
		p->mdl[SKATER].pos[2] -= SPEED;
	else if (state[GAME_RIGHT])
		p->mdl[SKATER].pos[2] += SPEED;
	else if (state[GAME_UP])
		p->mdl[SKATER].pos[0] += SPEED;
	else if (state[GAME_DOWN])
		p->mdl[SKATER].pos[0] -= SPEED;
}

static void set_init(struct game_output *p)
{
	int i;

	for (i = 0; i < p->nmdl; i++) {
		p->mdl[i].pos[0] = 0.0;
		p->mdl[i].pos[1] = 0.0;
		p->mdl[i].pos[2] = -5.0;
	}
}

int main(void)
{
	static struct model models[sizeof file / sizeof file[0]];
	static float geom[sizeof file / sizeof file[0]][8192];
	struct game_output output = { 0 };
	int state[GAME_NBUTTONS] = { 0 };
	int old[GAME_NBUTTONS];
	int i;

	if (game_init(CLIENT_NAME, WINDOW_WIDTH, WINDOW_HEIGHT, button_bind)) {
		fprintf(stderr, "error: game_init failed\n");
		return EXIT_FAILURE;
	}

	output.mdl = models;
	for (i = 0; file[i] != NULL; i++) {
		output.mdl[i].geom = geom[i];
		output.mdl[i].vert = level_parsef(file[i], output.mdl[i].geom);
		if (output.mdl[i].vert <= 0) {
			fprintf(stderr, "error: can't read %s\n", file[i]);
			game_quit();
			return EXIT_FAILURE;
		}
	}

	output.nmdl = i;
	set_init(&output);
	memcpy(old, state, sizeof old);
	while (!game_input(state)) {
		update(old, state);
		memcpy(old, state, sizeof old);
		skate(state, &output);
		game_render(&output);
	}
	game_quit();
	return 0;
}
