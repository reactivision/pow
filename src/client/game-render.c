#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "game.h"
#include "game-render.h"

#define PI 3.14159265358979323846

void game_render_init(int width, int height)
{
	double fW, fH;
	fH = tan(60.0 / 360 * PI) * 1.0;
	fW = fH * ((float) width / (float) height);
	glClearColor(0, 0, 0, 0);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-fW, fW, -fH, fH, 1.0, 1024.0);
}

void game_render_draw(const struct game_output *p)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
	glRotated(60.0, 3.0, 3.0, 3.0);
/***
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, buf);
	glDrawArrays(GL_TRIANGLES, 0, v);
	glDisableClientState(GL_VERTEX_ARRAY);
 ***/
}

void game_render_quit(void)
{
}
