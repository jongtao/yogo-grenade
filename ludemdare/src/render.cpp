#include "render.h"

Render::Render(ALLEGRO_DISPLAY **display, Mapdata *mapdata,
	Gamedata *gamedata): display(display), mapdata(mapdata), gamedata(gamedata)
{
	al_init_font_addon();
	al_init_ttf_addon();

	font24 = al_load_font("OldNewspaperTypes.ttf", 24, 0);
	font16 = al_load_font("OldNewspaperTypes.ttf", 16, 0);
	if(font24 == NULL || font16 == NULL)
		abort_game("null font");

	bitmaps[0] = al_load_bitmap("orange.png");
	bitmaps[1] = al_load_bitmap("dirt.png");
	bitmaps[2] = al_load_bitmap("bunny.png");
	bitmaps[3] = al_load_bitmap("gun.png");
	bitmaps[4] = al_load_bitmap("bullet.png");
	bitmaps[5] = al_load_bitmap("grenade.png");
	bitmaps[6] = al_load_bitmap("white.png");
	bitmaps[7] = al_load_bitmap("portal.png");

	for(int i = 0; i <= 7; i++)
		if(bitmaps[i] == NULL)
			abort_game("null sprite");
			//load error
} // Render()



Render::~Render()
{
	al_shutdown_font_addon();
} // ~Render()



void Render::draw(int mode)
{
	switch(mode)
	{
		case 0:
			prelude();
			break;
		case 1:
			theme();
			break;
		case 2:
			finale();
			break;
	} // switch mode
} // draw()



void Render::prelude()
{
	al_clear_to_color(al_map_rgb(0, 65, 34));

	al_draw_text(font24, al_map_rgb(10, 10, 0), 50, 200, 0,
		"You only get one holy hand grenade.");
	al_draw_text(font16, al_map_rgb(10, 10, 0), 150, 250, 0,
		"The WASD moves thy body. The left mouse fires thy trusty weapon.");
	al_draw_text(font16, al_map_rgb(10, 10, 0), 100, 300, 0,
		"With the right mouse, lobbest thou thy Holy Hand Grenade of Antioch towards thy foe,");
	al_draw_text(font16, al_map_rgb(10, 10, 0), 125, 315, 0,
		"who being naughty in My sight, shall snuff it.");
	al_draw_text(font16, al_map_rgb(10, 10, 0), 200, 400, 0,
		"Press any key to do battle.");

	al_flip_display();
} // prelude



void Render::theme()
{
	al_clear_to_color(al_map_rgb(0, 65, 34));
	mapbg();
	if((int)gamedata->player.aim_x > 0)
		al_draw_scaled_rotated_bitmap(bitmaps[PLAYER],
						23, 2,
						GAME_WIDTH/2, GAME_HEIGHT/2,	
						-1, 1,
						0, 0);
	if((int)gamedata->player.aim_x <= 0)
		al_draw_scaled_rotated_bitmap(bitmaps[PLAYER],
						13, 2,
						GAME_WIDTH/2, GAME_HEIGHT/2,	
						1, 1,
						0, 0);

	double angle = atan2(-gamedata->player.aim_y, gamedata->player.aim_x);

	if((int)gamedata->player.aim_x > 0)
		al_draw_scaled_rotated_bitmap(bitmaps[GUN],
				21, 19,
				GAME_WIDTH/2 + 2, GAME_HEIGHT/2 + 17,	
				-1, 1,
				-angle, 0);

	if((int)gamedata->player.aim_x <= 0)
		al_draw_scaled_rotated_bitmap(bitmaps[GUN],
				21, 19,
				GAME_WIDTH/2 + 8, GAME_HEIGHT/2 + 17,	
				1, 1,
				-angle + 3.14159, 0);


	// draw bullets
	
	for(unsigned int i = 0; i < gamedata->player.bullets.size(); i++)
	{
		al_draw_scaled_rotated_bitmap(bitmaps[BULLET],
				0, 0,
				- gamedata->player.x+GAME_WIDTH/2+gamedata->player.bullets[i].x,
				floor(-gamedata->player.y)+GAME_HEIGHT/2+gamedata->player.bullets[i].y,	
				1, 1,
				gamedata->player.bullets[i].angle + 3.14159, 0);
	} // for i

		

	// draw bunnies
	for(unsigned int i = 0; i < gamedata->bunnies.size(); i++)
		if(gamedata->bunnies[i].is_alive != false)
		{
			if(gamedata->bunnies[i].direction >= 0)
				al_draw_scaled_rotated_bitmap(bitmaps[BUNNY],
					0, 0,
					- gamedata->player.x+GAME_WIDTH/2+gamedata->bunnies[i].x-1,
					floor(-gamedata->player.y)+GAME_HEIGHT/2+gamedata->bunnies[i].y-1,
					1, 1,
					0, 0);
			else
				al_draw_scaled_rotated_bitmap(bitmaps[BUNNY],
					10, 0,
					- gamedata->player.x+GAME_WIDTH/2+gamedata->bunnies[i].x-1,
					floor(-gamedata->player.y)+GAME_HEIGHT/2+gamedata->bunnies[i].y-1,
					-1, 1,
					0, 0);
		} // if bunny alive

	if(gamedata->player.grenade->is_alive)
		al_draw_scaled_rotated_bitmap(bitmaps[GRENADE],
				4, 6,
				- gamedata->player.x+GAME_WIDTH/2+gamedata->player.grenade->x+4,
				floor(-gamedata->player.y)+GAME_HEIGHT/2+gamedata->player.grenade->y+4,
				1, 1,
				0, 0);



	//font

	sprintf(string1, "%d", gamedata->player.health);
	al_draw_text(font24, al_map_rgb(10, 10, 0), 50, 525, 0, string1);

	unsigned int tempy = gamedata->bunnies.size();
	unsigned int tempy2 = gamedata->numBunnies;
	sprintf(string1, "%d yet to feel thy wrath. %d shall commeth.",
		tempy, tempy2);
	al_draw_text(font16, al_map_rgb(10, 10, 0), 50, 25, 0, string1);

	tempy = gamedata->player.killed;
	sprintf(string1, "%d snuffed.", tempy);
	al_draw_text(font24, al_map_rgb(10, 10, 0), 75, 50, 0, string1);

	if(gamedata->player.has_grenade)
		al_draw_text(font24, al_map_rgb(10, 10, 0), 325, 525, 0,
			"You have only 1 Holy Hand Grenades.");
	else
		al_draw_text(font24, al_map_rgb(10, 10, 0), 325, 525, 0,
			"You have 0 Holy Hand Grenades.");



	// whiteout
	if(gamedata->player.grenade->is_alive)
	{
		double temp = 1.0 - gamedata->player.grenade->death_timer/300.0;
		al_draw_tinted_bitmap(bitmaps[WHITE],
			al_map_rgba_f(temp, temp, temp, 0),
		   0, 0, 0);
	}

	al_flip_display();
} // theme()



void Render::mapbg()
{
	for(int i = 0; i < mapdata->length; i++)
		for(int j = 0; j < 256; j++)
			if(mapdata->data[i][j] == 'M')
			{
				al_draw_bitmap(bitmaps[GROUND],
					- gamedata->player.x + (i * 32) + GAME_WIDTH/2,
					floor(- gamedata->player.y) - (j * 32) + GAME_HEIGHT/2,
					0);
			}

	
	al_draw_bitmap(bitmaps[PORTAL],
		- gamedata->player.x + (mapdata->bunny_x * 32) + GAME_WIDTH/2,
		floor(- gamedata->player.y) - (mapdata->bunny_y * 32) + GAME_HEIGHT/2,
		0);
} // mapbg



void Render::finale()
{
	al_clear_to_color(al_map_rgb(169, 13, 13));

	al_draw_text(font24, al_map_rgb(10, 10, 0), 50, 200, 0,
		"You have been consumed...");

	al_flip_display();
} // finale()
