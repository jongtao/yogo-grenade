#ifndef PHYSICS_H
#define PHYSICS_H

#include <cmath>
#include <cstdio>
#include "mapdata.h"
#include "constants.h"


class Physics
{
private:
	int grav_a;
	int fric_a;


	void check_x_wall(float *vx, float *vy, float x, float y, int width,
		int height, Mapdata* mapdata);
	void check_y_wall(float *vx, float *vy, float x, float y, int width,
		int height, Mapdata* mapdata);

public:
	Physics();

	bool on_ground(float x, float y, int width, int height, Mapdata *mapdata);
	void friction(float *vx, float *vy);
	void gravity(float *vy);
	void check_wall_col(float *vx, float *vy, float x, float y, int width,
		int height, Mapdata* mapdata);
}; // class Physics


#endif
