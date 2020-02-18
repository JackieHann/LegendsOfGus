#ifndef ROOM_DATA_H
#define ROOM_DATA_H

#include "LevelDefines.h"
#include "Door.h"
#include <vector>

//Pure data representation of rooms
struct RoomData
{
	const char* m_file_path;
	Coord m_dimensions;
	std::vector<Door> m_doors;

	RoomData() :
		m_dimensions({ 0, 0 })
	{
		m_doors.clear();
	}

	RoomData(const char* str, int size, std::vector<Door> doors) :
		m_dimensions({ size, size }),
		m_doors(doors),
		m_file_path(str)
	{
	}

	void rotate90(int amt)
	{
		for (int i = 0; i < amt; i++)
		{
			for (int door_idx = 0; door_idx < m_doors.size(); door_idx++)
			{
				Door curr_door_data = m_doors[door_idx];
				Coord new_door_pos = { 0,0 };
				Cardinal_Direction new_door_dir = CD_NORTH;

				new_door_pos.y = curr_door_data.m_local_pos.x;
				new_door_pos.x = (m_dimensions.y - 1) - curr_door_data.m_local_pos.y;

				switch (curr_door_data.m_local_dir)
				{
				case CD_NORTH:	new_door_dir = CD_EAST;		break;
				case CD_EAST:	new_door_dir = CD_SOUTH;	break;
				case CD_SOUTH:	new_door_dir = CD_WEST;		break;
				case CD_WEST:	new_door_dir = CD_NORTH;	break;
				}

				m_doors[door_idx].m_local_dir = new_door_dir;
				m_doors[door_idx].m_local_pos = new_door_pos;
			}
		}
	}

};


//Below defines all blueprint rooms

static RoomData start_room_5x5_1door(
	"Rooms/5x5_1door_start.5x5_1door_start'", 5,
	{
		{{2, 4}, CD_SOUTH}
	});

static RoomData corridor_room(
	"Rooms/Corridor.Corridor'", 1,
	{
		
	});

static RoomData door_room(
	"Rooms/Door.Door'", 1,
	{

	});

static RoomData room_3x3_2door_straight(
	"Rooms/3x3_2door_straight_BP.3x3_2door_straight_BP'", 3,
	{
		{{1, 0}, CD_NORTH },
		{{1, 2}, CD_SOUTH}
	});

static RoomData room_3x3_4door_cross(
	"Rooms/3x3_4door_BP.3x3_4door_BP'", 3,
	{
		{{1, 0}, CD_NORTH },
		{{2, 1}, CD_EAST },
		{{1, 2}, CD_SOUTH},
		{{0, 1}, CD_WEST}
	});

static RoomData room_3x3_3door_T(
	"Rooms/3x3_3door_T_BP.3x3_3door_T_BP'", 3,
	{
		//{{1, 0}, CD_NORTH },
		{{2, 1}, CD_EAST },
		{{1, 2}, CD_SOUTH},
		{{0, 1}, CD_WEST}
	});

static RoomData room_3x3_2door_R(
	"Rooms/3x3_2door_R_BP.3x3_2door_R_BP'", 3,
	{
		{{2, 1}, CD_EAST },
		{{1, 2}, CD_SOUTH}
	});

static RoomData room_3x3_1door(
	"Rooms/3x3_1door_BP.3x3_1door_BP'", 3,
	{
		{{1, 2}, CD_SOUTH}
	});


//Contains reference to all potential rooms
static std::vector<RoomData> GLOBAL_ROOM_DATA =
{
	room_3x3_2door_straight,
	room_3x3_4door_cross,
	room_3x3_3door_T,
	room_3x3_2door_R,
	room_3x3_1door
};

#endif