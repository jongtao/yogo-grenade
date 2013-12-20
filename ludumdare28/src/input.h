#ifndef INPUT_H
#define INPUT_H

#include <allegro5/allegro5.h>

#include <cmath>

#include "constants.h"

class Input
{
private:
public:
	bool up, down, left, right, space;
	bool leftmouse, middlemouse, rightmouse;
	double aim_angle;
	int aim_x, aim_y;
	int wild_down;

	Input();
	void gather(const ALLEGRO_EVENT *event);
}; // INPUT


#endif
