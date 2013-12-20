#ifndef GAME_H
#define GAME_H

#include <allegro5/allegro5.h>
#include <iostream>

#include "input.h"
#include "render.h"
#include "mapdata.h"
#include "gamedata.h"
#include "audio.h"


enum state
{
	PRELUDE,
	THEME,
	FINALE
}; //enum state()


class Game
{
private:
	ALLEGRO_EVENT_QUEUE **event_queue;
	ALLEGRO_TIMER **timer;
	Mapdata mapdata;
	Gamedata gamedata;
	Render render;
	Audio audio;
	unsigned int counter;
	int mode, first;

public:
	Input inputs;

	Game(ALLEGRO_EVENT_QUEUE **event_queue, ALLEGRO_TIMER **timer,
		ALLEGRO_DISPLAY **display);
	void update();
	void draw();

	void prelude();
	void theme();
	void finale();
};

#endif
