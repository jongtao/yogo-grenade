// Ludem Dare 28

#include <allegro5/allegro5.h>
#include <cstdio>
#include "init.h"
#include "game.h"


void game_loop(ALLEGRO_EVENT_QUEUE **event_queue, ALLEGRO_TIMER **timer,
	ALLEGRO_DISPLAY **display, bool *done)
{
	al_start_timer(*timer);
	ALLEGRO_EVENT event;
	bool redraw = true;
	Game game(event_queue, timer, display);	

	while(!*done)
	{
		al_wait_for_event(*event_queue, &event);
		if(event.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;
			game.update();
		} // if timer ticks
		else
		{
			if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
				break;
			game.inputs.gather(&event);
		} // else
		if(redraw && al_is_event_queue_empty(*event_queue))
		{
			game.draw();
			redraw = false;
		} // if redraw
	} // while not done
} // gameloop()



int main(int argc, char* argv[])
{
	ALLEGRO_EVENT_QUEUE* event_queue;
	ALLEGRO_TIMER* timer;
	ALLEGRO_DISPLAY* display;

	bool done;

	init(&event_queue, &timer, &display, &done);
	game_loop(&event_queue, &timer, &display, &done);
	shutdown(&event_queue, &timer, &display);

	return 0;
} // main()
