#ifndef AUDIO_H
#define AUDIO_H
#include <allegro5/allegro5.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <cstdio>
#include "init.h"

enum sound_names
{
	JUMP_S,
	GUN_S,
	EXPLOSION_S,
	RABBIT_JUMP_S,
	DEAD_RABBIT_S,
	HURT_S,
	SONG_S
}; // enum sound_names


class Audio
{
public:
	ALLEGRO_SAMPLE *sounds[16];
	ALLEGRO_SAMPLE_INSTANCE *song_instance;

	Audio();

	void play(int num);
	void play_r(int num);
	void stop_r();
	
}; // 


#endif
