#ifndef GAMEDATA_H
#define GAMEDATA_H
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <vector>
#include "allegro5/allegro.h"
#include "mapdata.h"
#include "physics.h"
#include "constants.h"
#include "input.h"
#include "audio.h"

class Grenade;
class Bullet;
class Bunny;


class Entity
{
public:
	Mapdata *mapdata;
	Physics *physics;
	Audio* audio;
	float x, y, vx, vy;
	float accel, max_speed;

	Entity(Mapdata *mapdata, Physics *physics, Audio* audio);
}; // class Entity



class Player: public Entity
{
public:
	float p_x, p_y;
	float p_vx, p_vy;

	int health, width, height, jump_height;
	int aim_x, aim_y;
	bool has_grenade, is_alive;
	Grenade *grenade;

	std::vector<Bullet> bullets;
	int cooldown;
	std::vector<Bunny> *bunnies;
	int killed;

	Player(int x, int y, Mapdata* mapdata, Physics *physics, Audio *audio,
		std::vector<Bunny> *bunnies);
	~Player();
	void update(Input *inputs);
}; // class Entity



class Bunny: public Entity
{
public:
	Player *player;
	int size, health, width, height;
	bool is_alive, bitten;
	int timer, direction;
	float jump_height;



	Bunny(int size, int x, int y, Mapdata* mapdata, Physics *physics,
		Audio *audio, Player *player, int dx);
	void update();
	void kill();
}; // class Bunny



class Bullet: public Entity
{
public:
	bool is_alive;
	int width, height, life;
	double angle;

	Bullet(float x, float y, float vx, float vy, double angle, Mapdata* mapdata,
		Physics* physics, Audio *audio);
	int update(std::vector<Bunny> *bunnies);
	void kill();
}; // class Bullet



class Grenade: public Entity
{
public:
	bool is_alive;
	int timer, death_timer;

	Grenade( Mapdata* mapdata, Physics* physics, Audio *audio);
	void activate(float x, float y, float vx, float vy);
	int update(std::vector<Bunny> *bunnies);
}; // class Grenade



class Gamedata
{
private:
	Mapdata* mapdata;
	Audio* audio;
	Physics physics;
public:
	Player player;
	std::vector<Bunny> bunnies;
	int numBunniesOld;
	int numBunnies;

	Gamedata(Mapdata* mapdata, Audio* audio);
	~Gamedata();
	void add_bunnies(Mapdata *mapdata);
}; // class Gamedata

#endif
