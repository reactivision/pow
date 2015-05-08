struct game_input {
	int up;
	int down;
	int left;
	int right;
	int ollie;
	int grind;
	int grab;
	int flip;
	int lspin;
	int rspin;
};

struct game_output {
	int unused;
};

/* game_init: create a game window */
int game_init(const char *title, int width, int height);

/* game_quit: release resources */
void game_quit(void);

/* game_input: convert keycodes in *p to 0 (released) or 1 (pressed); return
 *             non-zero if window was closed */
int game_input(struct game_input *p);

/* game_render: draw *p on the screen, regulate frame-rate */
void game_render(const struct game_output *p);
