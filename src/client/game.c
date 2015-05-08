#include "SDL/SDL.h"
#include "GL/gl.h"
#include "GL/glu.h"
#include "game.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>
#define WIDTH 1024
#define HEIGHT 768
#define PI 3.14159265358979323846

static void init(void);

int game_init(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0 ||
	    SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_OPENGL) == 0)
		return -1;
	init();
	return 1;
}

void game_quit(void)
{
	SDL_Quit();
}

int game_parse(char *path, float buf[])
{
	FILE *fp;
	int i;
	
	if ((fp = fopen(path, "r")) == NULL)
		return -1;
	for (i = 0; fscanf(fp, "%f", &buf[i]) == 1; i++)
		;
	fclose(fp);
	return i;
}

void loop(float buf[], int v)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
	glRotated(60.0, 3.0, 3.0, 3.0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, buf);
	glDrawArrays(GL_TRIANGLES, 0, v);
	glDisableClientState(GL_VERTEX_ARRAY);
	SDL_GL_SwapBuffers();

}

static void init(void)
{
	double fW, fH;
	fH = tan(60.0 / 360 * PI) * 1.0;
	fW = fH * ((float) WIDTH / (float) HEIGHT);
	glClearColor(0, 0, 0, 0);
	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-fW, fW, -fH, fH, 1.0, 1024.0);
}
