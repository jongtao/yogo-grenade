#include "game.h"



Game::Game(ALLEGRO_EVENT_QUEUE **event_queue, ALLEGRO_TIMER **timer,
	ALLEGRO_DISPLAY **display):
	event_queue(event_queue), timer(timer),
	gamedata(&mapdata, &audio),
	render(display, &mapdata, &gamedata),
 	counter(0), mode(0), first(1)
{
} // Game()



void Game::update()
{
	switch(mode)
	{
		case PRELUDE:
			prelude();
			break;
		case THEME:
			theme();
			break;
		case FINALE:
			finale();
			break;
	}; // switch state
} // update()



void Game::draw()
{
	render.draw(mode);
} // draw()



void Game::prelude()
{
	if(inputs.wild_down != 0)
		mode = THEME;
} // prelude()



void Game::theme()
{
	if(first == 1)
	{
		first = 0;
		audio.play_r(SONG_S);
	} // if need to begin song

	counter++;
	if(counter > 4000000000)
		counter = 0;

	if(counter % 600 == 0)
		gamedata.add_bunnies(&mapdata);

	if(gamedata.player.is_alive)
		gamedata.player.update(&inputs);	
	else
	{
		mode = FINALE;
		return;
	} // if dead

	for(unsigned int i = 0; i < gamedata.bunnies.size(); i++)
	{
		if(!gamedata.bunnies[i].is_alive)
			gamedata.bunnies.erase(gamedata.bunnies.begin() + i);
		gamedata.bunnies[i].update();
	} // for all bunnies
} // theme()



void Game::finale()
{
	audio.stop_r();
} // finale()

