#include "audio.h"

Audio::Audio(): song_instance(NULL)
{
	sounds[0] = al_load_sample("jump.wav");
	sounds[1] = al_load_sample("gun.wav");
	sounds[2] = al_load_sample("explosion.wav");
	sounds[3] = al_load_sample("rabbit_jump.wav");
	sounds[4] = al_load_sample("dead_rabbit.wav");
	sounds[5] = al_load_sample("hurt.wav");
	sounds[6] = al_load_sample("song.ogg");

	for(int i = 0; i <= 4; i++)
		if(sounds[i] == NULL)
			abort_game("null sound");
	
} // Audio


void Audio::play(int num)
{
	al_play_sample(sounds[num], 1.75, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
}


void Audio::play_r(int num)
{
	song_instance = al_create_sample_instance(sounds[num]);
	al_set_sample_instance_playmode(song_instance, ALLEGRO_PLAYMODE_LOOP);
	
	al_set_sample_instance_gain(song_instance, 1.5);
		al_attach_sample_instance_to_mixer(song_instance, al_get_default_mixer());

	al_play_sample_instance(song_instance);

}

void Audio::stop_r()
{
	al_stop_sample_instance(song_instance);
}
