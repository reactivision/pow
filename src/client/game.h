enum {
	GAMEK_UP, GAMEK_DOWN, GAMEK_LEFT, GAMEK_RIGHT, GAMEK_OLLIE, GAMEK_GRIND,
	GAMEK_GRAB, GAMEK_FLIP, GAMEK_LSPIN, GAMEK_RSPIN, GAME_NBUTTONS
};

struct game_output {
	int unused;
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
