#include "mapdata.h"

Mapdata::Mapdata()
{
	load_map();
} // Mapdata()



Mapdata::~Mapdata()
{
	for(int i = 0; i <= 1024; i++)
		free(data[i]);

	free(data);
} // ~Mapdata()



void Mapdata::load_map()
{
	FILE *fp;
	char *ptr;
	int i = 0;

	// start with 1024x256 char array. 256 is max height
	data = (char**)calloc(sizeof(char*), 1024);
	for(int i = 0; i <= 1024; i++)
		data[i] = (char*)calloc(sizeof(char), 256);

	if(!(fp = fopen("map.txt", "r")))
		abort_game("Could not find and open map.txt");

	while((fgets(data[i], 255, fp)) != NULL)
	{
		printf("%s", data[i]); // debug printing

		if((ptr = strchr(data[i], 'S')))
		{
			spawn_x = i;
			spawn_y = ptr - data[i];
		} // if spawn point found

		if((ptr = strchr(data[i], 'E')))
		{
			bunny_x = i;
			bunny_y = ptr - data[i];
		} // if bunny spawn found

		i++;

		if(i > 1024)
			abort_game("Map too long (> 1024)");

	} //while not null

	length = i;
	fclose(fp);
} // load_map()



bool Mapdata::fetch_wall(int x, int y)
{
	if(x <0 || x>=1024 || y < 0 || y >= 256)
		return true;

	if(data[x][y] == 'M')	
		return false;	//false means there is wall

	return true;
} // fetch_wall

