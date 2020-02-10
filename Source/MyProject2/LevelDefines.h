#pragma once

#include <cstdlib>
//File that contains all generation data that can be tweaked by the artists for UX

#define MAP_DIMENSIONS_X 30
#define MAP_DIMENSIONS_Y 30

#define START_ROOM_DIMENSIONS_X 3
#define START_ROOM_DIMENSIONS_Y 3

#define END_ROOM_DIMENSIONS_X 6
#define END_ROOM_DIMENSIONS_Y 6

#define MAP_ORIGIN_X 0
#define MAP_ORIGIN_Y 0

#define MIN_CORRIDOR_LENGTH 1
#define MAX_CORRIDOR_LENGTH 1

#define MAX_ROOM_SIZE 9
#define MIN_ROOM_SIZE 3

struct Coord
{
	int x;
	int y;
};

enum Prefab_Rotation
{
	PR_0_DEG = 0,
	PR_90_DEG,
	PR_180_DEG,
	PR_270_DEG,
};

enum Cardinal_Direction
{
	CD_NORTH = 0,
	CD_EAST,
	CD_SOUTH,
	CD_WEST
};

static int RandomIntInRange(const int min, const int max)
{
	return rand() % (max - min + 1) + min;
}

static Coord GetMiddleCoord(const Coord a, const Coord b)
{
	return { ((a.x + b.x) / 2), ((a.y + b.y) / 2) };
}

static Coord GetDirectionFromCardinal(Cardinal_Direction dir)
{
	switch (dir)
	{
	case CD_NORTH:	return { 0, -1 };
	case CD_EAST:	return { 1, 0 };
	case CD_SOUTH:	return { 0, 1 };
	case CD_WEST:	return { -1, 0 };
	}

	return { 0,0 };
}