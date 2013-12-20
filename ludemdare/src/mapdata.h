#ifndef MAPDATA_H
#define MAPDATA_H
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "init.h"

class Mapdata
{
private:
	void load_map();

public:
	char **data;
	int length;
	int spawn_x, spawn_y;
	int bunny_x, bunny_y;
	Mapdata();
	~Mapdata();
	bool fetch_wall(int x, int y);

}; // class Mapdata

#endif
