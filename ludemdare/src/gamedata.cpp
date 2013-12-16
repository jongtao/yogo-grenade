#include "gamedata.h"


Entity::Entity(Mapdata *mapdata, Physics *physics, Audio *audio):
	mapdata(mapdata), physics(physics), audio(audio),
	x(0), y(0), vx(0), vy(0), accel(0), max_speed(0)
{
} // Entity



Player::Player(int x, int y, Mapdata *mapdata, Physics *physics, Audio *audio,
	std::vector<Bunny> *bunnies):
	Entity(mapdata, physics, audio),
	p_x(0), p_y(0), p_vx(0), p_vy(0),
	health(500), width(10), height(30), jump_height(11),
	has_grenade(true), is_alive(true),
	cooldown(6), bunnies(bunnies), killed(0)
{
	this->x = x*32;
	this->y = y*-32;
	this->accel = 0.8;
	this->max_speed = 4;
	grenade = new Grenade(mapdata, physics, audio);
} // Player()



Player::~Player()
{
	delete grenade;
}



void Player::update(Input *inputs)
{
	if(health <= 0 || y > 32*20)
	{
		is_alive = 0;
		return;
	} // health


	// deal with movement
	this->aim_x = inputs->aim_x - GAME_WIDTH/2;
	this->aim_y = inputs->aim_y - GAME_HEIGHT/2 - 16;

	if(inputs->left && (vx - accel) >= -max_speed)
		vx -= accel;
	if(inputs->right && (vx + accel) <= max_speed)
		vx += accel;
	if(inputs->up && physics->on_ground(x, y, width, height, mapdata))
	{
		vy -= jump_height;
		audio->play(JUMP_S);
	}
	if(inputs->down && (vy + accel) <= max_speed)
		vy += accel;

	if(!physics->on_ground(x, y, width, height, mapdata))
		physics->gravity(&vy);

	physics->friction(&vx, &vy);
	physics->check_wall_col(&vx, &vy, x, y, width, height, mapdata);

	x += vx;
	y += vy;

	// actions
	if(inputs->leftmouse && cooldown == 0)
	{
		double angle = -atan2(-aim_y, aim_x);
		printf("%f, %f, %f\n", angle,
			30 * cos(angle), 30 * sin(angle));

		Bullet bull(x, y+18, 30 * cos(angle), 30 * sin(angle),
			angle, mapdata, physics, audio);
		bullets.push_back(bull);

		audio->play(GUN_S);

		cooldown = 6;
	} // if shoot

	if(cooldown > 0)
		cooldown--;

	for(unsigned int i = 0; i < bullets.size(); i++)
	{
		killed += bullets[i].update(bunnies);

		if(!bullets[i].is_alive)
			bullets.erase(bullets.begin() + i);
	} // update bullets


	// Grenade
	if(has_grenade && inputs->rightmouse)
	{
		double angle = -atan2(-aim_y, aim_x);
		printf("%f, %f, %f\n", angle,
			15 * cos(angle), 15 * sin(angle));

		has_grenade = false;
		grenade->activate(x, y+18, 15 * cos(angle), 15 * sin(angle));
	}

	if(grenade->is_alive)
		killed += grenade->update(bunnies);
	

} // update()



Bunny::Bunny(int size, int x, int y,  Mapdata *mapdata, Physics *physics,
	Audio *audio, Player *player, int dx):
	Entity(mapdata, physics, audio), player(player), size(size), health(size * 3),
	width(8), height(7), is_alive(true),bitten(false), timer(dx), direction(0),
	jump_height(15)
{
	this->x = x * 32 + dx;
	this->y = y * -32;
	this->accel = 5;
	this->max_speed = 10;
} // Bunny()



void Bunny::update()
{
	bool is_on_ground = physics->on_ground(x, y, width, height, mapdata);

	if(health <=0 || (y > 10 * 32))
		kill();

	if(timer == 0)
	{
		
		direction = player->x - x;

		if(direction > 0 && (vx + accel) <= max_speed)
			vx += accel; // direction positive is right
		else
			if(direction < 0 && (vx - accel) >= -max_speed)
				vx -= accel;


		if(is_on_ground)
		{
			srand(1000 * al_get_time());
			timer = rand() % 61 + 32;

			vy -= jump_height;
			audio->play(RABBIT_JUMP_S);
			bitten = false;
		} // if on ground
		else
			timer = 0;

	} // if timer is 0
	else
		timer--;
		


	if(!is_on_ground)
		physics->gravity(&vy);

	physics->friction(&vx, &vy);
	physics->check_wall_col(&vx, &vy, x, y, width, height, mapdata);

	x += vx;
	y += vy;

	// ACTION
	float temp_x = x;
	float temp_y = y;

	for(int j = 0; j < 4; j++)
	{
		switch(j)
		{
			case 0:
				break;
			case 1:
				temp_x = x + width;
				break;
			case 2:
				temp_y = y + height;
				break;
			case 3:
				temp_x = x;
				break;
		} // switch j

		if(temp_x >= player->x &&
			temp_x <= player->x + player->width &&
			temp_y >= player->y &&
			temp_y <= player->y + player->height &&
			!is_on_ground &&
			!bitten)
		{
			printf("BITE\n");
			bitten = true;
			audio->play(HURT_S);
			player->health--;
		}
	} // for i
} // update()



void Bunny::kill()
{
	timer = 300;
	is_alive = false;
	audio->play(DEAD_RABBIT_S);
} // kill()



Bullet::Bullet(float x, float y, float vx, float vy, double angle,
	Mapdata* mapdata, Physics *physics, Audio* audio):
	Entity(mapdata, physics, audio), is_alive(true),
	width(13), height(13), life(300), angle(angle)
{
	this->x = x;
	this->y = y;
	this->vx = vx;
	this->vy = vy;
} // Bullet()



int Bullet::update(std::vector<Bunny> *bunnies)
{
	bool killed = false;

	physics->check_wall_col(&vx, &vy, x, y, 3, 3, mapdata);
	if( sqrt(vx * vx + vy * vy) < 8)
		kill();

	life--;
	if(life <= 0)
		kill();

	x += vx;
	y += vy;

	for(unsigned int i = 0; i < bunnies->size(); i++)
	{
		float temp_x = (*bunnies)[i].x;
		float temp_y = (*bunnies)[i].y;

		for(int j = 0; j < 4; j++)
		{
			switch(j)
			{
				case 0:
					break;
				case 1:
					temp_x = (*bunnies)[i].x + (*bunnies)[i].width;
					break;
				case 2:
					temp_y = (*bunnies)[i].y + (*bunnies)[i].height;
					break;
				case 3:
					temp_x = (*bunnies)[i].x;
					break;
			} // switch j

			if(temp_x >= x &&
				temp_x <= x + width &&
				temp_y >= y &&
				temp_y <= y + height)
			{
				printf("KILL\n");
				kill();
				(*bunnies)[i].kill();
				killed++;
				break;
			} // if corners within
		} // for j
	} // for i
	return killed;
} // update()



void Bullet::kill()
{
	is_alive = false;
} // kill()



Grenade::Grenade(Mapdata* mapdata, Physics* physics, Audio* audio):
	Entity(mapdata, physics, audio), is_alive(false), timer(300), death_timer(300)
{
} // Grenade()



void Grenade::activate(float x, float y, float vx, float vy)
{
	this->x = x;
	this->y = y;
	this->vx = vx;
	this->vy = vy;
	is_alive = true;
	audio->play(RABBIT_JUMP_S);
} // activate()



int Grenade::update(std::vector<Bunny> *bunnies)
{
	int killed = 0;

	physics->gravity(&vy);
	physics->friction(&vx, &vy);
	physics->check_wall_col(&vx, &vy, x, y, 7, 7, mapdata);

	x += vx;
	y += vy;

	timer--;

	if(timer <= 0)
	{
		if(death_timer == 300)
			audio->play(EXPLOSION_S);
		death_timer--;
		if(death_timer <=0)
		{
			printf("explode\n");
			is_alive = false;
			killed = bunnies->size();
			bunnies->clear();
		}
	}

	return killed;
} // update()


Gamedata::Gamedata(Mapdata *mapdata, Audio* audio):
	mapdata(mapdata), audio(audio),
	player(mapdata->spawn_x, mapdata->spawn_y, mapdata, &physics, audio,
		&bunnies),
	numBunniesOld(0), numBunnies(0)
{
} // Gamedata()




Gamedata::~Gamedata()
{
} // ~Gamedata()



void Gamedata::add_bunnies(Mapdata *mapdata)
{

	if(numBunnies <= 1024) // too much bunny
	{
		if(numBunnies == 0)
		{
			numBunnies = 1;
		} // if first add
		else
		{
			int temp = numBunniesOld + numBunnies;
			numBunniesOld = numBunnies;
			numBunnies = temp;
		} // fib()
	} // add fib untill too much bunny;

	// add bunnies
	if(bunnies.size() <= 1024)
		for(int i = 0; i < numBunnies; i++)
		{
			printf("num:%lu, numBun: %u\n", bunnies.size(),
				numBunnies);

			srand(i);
			float dx = rand() % 31;

			Bunny bun(1, mapdata->bunny_x, mapdata->bunny_y, mapdata, &physics,
				audio, &player, dx);
			bunnies.push_back(bun);
		}
	
} // add_bunnies

