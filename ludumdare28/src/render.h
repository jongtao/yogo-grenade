#ifndef RENDER_H
#define RENDER_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <cstdio>
#include <cmath>

#include "init.h"
#include "constants.h"
#include "input.h"
#include "mapdata.h"
#include "gamedata.h"



enum bitmap_names
{
	PLAYER,
	GROUND,
	BUNNY,
	GUN,
	BULLET,
	GRENADE,
	WHITE,
	PORTAL
}; // enum bitmap_names



class Render
{
private:
	int px, py;
	int width, height;
	
	ALLEGRO_DISPLAY **display;
	ALLEGRO_BITMAP *bitmaps[16];
	ALLEGRO_FONT *font24, *font16;

	char string1[32];
	char string2[32];

	Mapdata* mapdata;
	Gamedata* gamedata;

	void prelude();
	void theme();
	void finale();

	void mapbg();

public:
	Render(ALLEGRO_DISPLAY **display, Mapdata *mapdata, Gamedata *gamedata);
	~Render();
	void draw(int mode);
}; // class Render

#endif

