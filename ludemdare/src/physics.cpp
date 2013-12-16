#include "physics.h"


Physics::Physics(): grav_a(40), fric_a(16)
{
} // physics()



bool Physics::on_ground(float x, float y, int width, int height,
	Mapdata *mapdata)
{
	int t_x = (int)floor(x+width/2) / 32.0;
	int t_y = (int)ceil(-(y+height + 1) / 32.0);
/*
	for(int i = 0; i <= width; i++)
	{ 
		t_x = (int)((x + i) / 32.0);
		mapdata->fetch_wall(t_x, t_y);
	}
*/

	return !mapdata->fetch_wall(t_x, t_y);
} // on_ground()



void Physics::friction(float *vx, float *vy)
{
	if(*vx > 0)
	{
		*vx -= (fric_a * TIMESTEP);

		if(*vx < 0)
			*vx = 0;
	} // if positive velocity


	if(*vx < 0)
	{
		*vx += (fric_a * TIMESTEP);

		if(*vx > 0)
			*vx = 0;
	} // if negative velocity


	if(*vy > 0)
	{
		*vy -= (fric_a * TIMESTEP);

		if(*vy < 0)
			*vy = 0;
	} // if positive velocity


	if(*vy < 0)
	{
		*vy += (fric_a * TIMESTEP);

		if(*vy > 0)
			*vy = 0;
	} // if negative velocity

} // ground_friction()




void Physics::check_x_wall(float *vx, float *vy, float x, float y, int width,
	int height,	Mapdata* mapdata)
{

	if(*vx == 0)
		return;

	int temp_vx = 0;
	int temp_x, temp_y;

	if(*vx > 0) // moving right
	{
		temp_vx = (int)ceil(*vx);
		// rounding position down to scale down game's position matrix to
		// the wallmask's (yeah truncate yadayada)
		temp_y = (int)floor(y / 32);

		// simulate steps
		for(int i = 1; i <= temp_vx; i++)
		{
			temp_x = (int)floor((x + i) / 32);
			// check if next step is in the wall
			if(!mapdata->fetch_wall(temp_x, -temp_y)) 
			{
				// get as close to the wall instead of going through it
				*vx = i - 1;
				return;
			} // if it is wall
		} // for i
	} // vx positive


	if(*vx < 0) // moving left
	{
		temp_vx = (int)floor(*vx);
		temp_y = (int)floor(y/ 32);

		for(int i = 1; i <= -temp_vx; i++)
		{
			temp_x = (int)floor((x - i) / 32);
			if(!mapdata->fetch_wall(temp_x, -temp_y))
			{
				*vx = -(i - 1);
				return;
			} // if it is wall
		} //for i
	} // vx negative
} // check_x_col()



void Physics::check_y_wall(float *vx, float *vy, float x, float y, int width,
	int height,	Mapdata* mapdata)
{
	int temp_vy = 0;
	int temp_x, temp_y;

	if(*vy == 0)
		return;

	if(*vy > 0) // moving down
	{
		temp_vy = (int)ceil(*vy);
		temp_x = (int)floor((x + *vx) / 32);

		for(int i = 1; i <= temp_vy; i++)
		{
			temp_y = (int)floor((y + i) / 32);
			if(!mapdata->fetch_wall(temp_x, -temp_y))
			{
				*vy = i - 1;
				return;
			} // if is wall
		} // for i
	} // vy positive


	if(*vy < 0) // moving up
	{
		temp_vy = (int)floor(*vy);
		temp_x = (int)floor((x + *vx) / 32);


		for(int i = 1; i <= -temp_vy; i++)
		{
			temp_y = (int)floor((y - i) / 32);
			if(!mapdata->fetch_wall(temp_x, -temp_y))
			{
				*vy = -(i - 1);
				//*vy = 0;
				return;
			} // if is wall
		} // for i
	} // vy positive

} // check_y_col()



void Physics::gravity(float *vy)
{
	*vy += grav_a * TIMESTEP;
} // gravity()



void Physics::check_wall_col(float *vx, float *vy, float x, float y, int width,
	int height, Mapdata* mapdata)
{
	//simulate stepping into wall mask and correct velocity

	float save_x = x;
	float save_y = y;
	//float distances[4] = {0, 0, 0, 0};

	for(int i = 0; i < 4; i++)
	{

		switch(i)
		{
			case 0:
				break;
			case 1:
				x = save_x + width;
				break;
			case 2:
				x = save_x + width;
				y = save_y + height;
				break;
			case 3:
				x = save_x;
				y = save_y + height;
				break;
		} // switch i


	check_x_wall(vx, vy, x, y, width, height, mapdata);
	check_y_wall(vx, vy, x, y, width, height, mapdata);
	} // for i

} // check_collision()

