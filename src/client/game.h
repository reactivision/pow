enum {
	GAME_UP, GAME_DOWN, GAME_LEFT, GAME_RIGHT, GAME_OLLIE, GAME_GRIND,
	GAME_GRAB, GAME_FLIP, GAME_LSPIN, GAME_RSPIN, GAME_NBUTTONS
};

struct model {
	float *geom;
	int vert;
	float pos[3], vel[3];
};

struct game_output {
	struct model *mdl;
	int nmdl;
};

/* game_init: create a game window, register button bindings */
int game_init(const char *title, int xres, int yres, int binds[GAME_NBUTTONS]);

/* game_quit: release resources */
void game_quit(void);

/* game_input: update button_states, 0=released, 1=pressed; return non-zero on
 *             close */
int game_input(int button_states[GAME_NBUTTONS]);

/* game_render: draw *p on the screen, regulate frame-rate */
void game_render(const struct game_output *p);
