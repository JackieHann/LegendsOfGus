#ifndef ROOM_DATA_H
#define ROOM_DATA_H

#include "LevelDefines.h"
#include "Door.h"
#include <vector>
#include <string>
#include <algorithm>

//Pure data representation of rooms
struct RoomData
{
	std::string m_file_path;
	Coord m_dimensions;
	std::vector<Door> m_doors;

	RoomData() :
		m_dimensions({ 0, 0 })
	{
		m_doors.clear();
	}

	RoomData(std::string str, int size, std::vector<Door> doors) :
		m_dimensions({ size, size }),
		m_file_path(str),
		m_doors(doors)
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

// Start Room
static RoomData start_room_5x5_1door(
	"Rooms/5x5_1door_start.5x5_1door_start'", 5,
	{
		{{2, 4}, CD_SOUTH}
	});

// End Room

static RoomData room_9x9_3_door_T_Boss(
	"Rooms/9x9_3door_T_BossRoom_BP.9x9_3door_T_BossRoom_BP'", 9,
	{
		{{4, 0}, CD_NORTH},
		{{8, 4}, CD_EAST},
		{{0, 2}, CD_WEST}
	});

// Spawn Room

// 1x1 Corridors
static RoomData corridor_room(
	"Rooms/Corridor.Corridor'", 1,
	{
		
	});

static RoomData corridor2_room(
	"Rooms/Corridor_2.Corridor_2'", 1,
	{

	});

static RoomData corridor3_room(
	"Rooms/Corridor_3.Corridor_3'", 1,
	{

	});

static RoomData corridor4_room(
	"Rooms/Corridor_4.Corridor_4'", 1,
	{

	});

// Corridor Intersections
static RoomData corridor_room_cross(
	"Rooms/Corridor_Cross.Corridor_Cross'", 1,
	{

	});

static RoomData corridor_room_t(
	"Rooms/Corridor_T.Corridor_T'", 1,
	{

	});




// Blockades
static RoomData door_room(
	"Rooms/Blockade.Blockade'", 1,
	{

	});

static RoomData room_3x3_1door(
	"Rooms/3x3_1door_BP.3x3_1door_BP'", 3,
	{
		{{1, 2}, CD_SOUTH}
	});

static RoomData room_3x3_1_door_fire(
	"Rooms/3x3_1door_fire_BP.3x3_1door_fire_BP'", 3,
	{
		{{1, 0}, CD_NORTH}
	});

static RoomData room_3x3_1_door_kitchen(
	"Rooms/3x3_1door_kitchen_BP.3x3_1door_kitchen_BP'", 3,
	{
		{{1, 0}, CD_NORTH}
	});

static RoomData room_3x3_2door_R(
	"Rooms/3x3_2door_R_BP.3x3_2door_R_BP'", 3,
	{
		{{2, 1}, CD_EAST },
		{{1, 2}, CD_SOUTH}
	});

static RoomData room_3x3_2door_R_Font(
	"Rooms/3x3_2door_R_Font_BP.3x3_2door_R_Font_BP'", 3,
	{
		{{2, 1}, CD_EAST },
		{{1, 2}, CD_SOUTH}
	});

static RoomData room_3x3_2door_R_Storeroom(
	"Rooms/3x3_2door_R_Storeroom_BP.3x3_2door_R_Storeroom_BP'", 3,
	{
		{{2, 1}, CD_EAST },
		{{1, 2}, CD_SOUTH}
	});

static RoomData room_3x3_2door_straight(
	"Rooms/3x3_2door_straight_BP.3x3_2door_straight_BP'", 3,
	{
		{{1, 0}, CD_NORTH },
		{{1, 2}, CD_SOUTH}
	});

static RoomData room_3x3_2door_straight_corridor(
	"Rooms/3x3_2door_straight_Corridor_BP.3x3_2door_straight_Corridor_BP'", 3,
	{
		{{1, 0}, CD_NORTH },
		{{1, 2}, CD_SOUTH}
	});

static RoomData room_3x3_3door_T(
	"Rooms/3x3_3door_T_BP.3x3_3door_T_BP'", 3,
	{
		{{2, 1}, CD_EAST },
		{{1, 2}, CD_SOUTH},
		{{0, 1}, CD_WEST}
	});

static RoomData room_3x3_3door_T_dark(
	"Rooms/3x3_3door_TDark_BP.3x3_3door_TDark_BP'", 3,
	{
		{{2, 1}, CD_EAST },
		{{1, 2}, CD_SOUTH},
		{{0, 1}, CD_WEST}
	});

static RoomData room_3x3_4door_cross(
	"Rooms/3x3_4door_BP.3x3_4door_BP'", 3,
	{
		{{1, 0}, CD_NORTH },
		{{2, 1}, CD_EAST },
		{{1, 2}, CD_SOUTH},
		{{0, 1}, CD_WEST}
	});

static RoomData room_3x3_4door_cross_font(
	"Rooms/3x3_4door_Font_BP.3x3_4door_Font_BP'", 3,
	{
		{{1, 0}, CD_NORTH },
		{{2, 1}, CD_EAST },
		{{1, 2}, CD_SOUTH},
		{{0, 1}, CD_WEST}
	});

static RoomData room_5x5_3door_T(
	"Rooms/5x5_3door_T_BP.5x5_3door_T_BP'", 5,
	{
		{{2, 0}, CD_NORTH},
		{{4, 2}, CD_EAST},
		{{0, 2}, CD_WEST}
	});

static RoomData room_5x5_3door_T_Storeroom(
	"Rooms/5x5_3door_T_Storeroom_BP.5x5_3door_T_Storeroom_BP'", 5,
	{
		{{2, 0}, CD_NORTH},
		{{4, 2}, CD_EAST},
		{{0, 2}, CD_WEST}
	});

static RoomData room_5x5_3door_T_Circle(
	"Rooms/5x5_3door_T_Circle_BP.5x5_3door_T_Circle_BP'", 5,
	{
		{{2, 0}, CD_NORTH},
		{{4, 2}, CD_EAST},
		{{0, 2}, CD_WEST}
	});

static RoomData room_7x7_3door_T_Cage(
	"Rooms/7x7_3door_T_Cage_BP.7x7_3door_T_Cage_BP'", 7,
	{
		{{3, 0}, CD_NORTH},
		{{6, 3}, CD_EAST},
		{{0, 3}, CD_WEST}
	});

static RoomData room_7x7_3door_T_Pillars(
	"Rooms/7x7_3door_T_Pillars_BP.7x7_3door_T_Pillars_BP'", 7,
	{
		{{3, 0}, CD_NORTH},
		{{6, 3}, CD_EAST},
		{{0, 3}, CD_WEST}
	});

static RoomData room_7x7_3door_T_GreatHall(
	"Rooms/7x7_3door_T_GreatHall_BP.7x7_3door_T_GreatHall_BP'", 7,
	{
		{{3, 0}, CD_NORTH},
		{{6, 3}, CD_EAST},
		{{0, 3}, CD_WEST}
	});

static RoomData room_7x7_3door_T_Circle(
	"Rooms/7x7_3door_T_Circle_BP.7x7_3door_T_Circle_BP'", 7,
	{
		{{3, 0}, CD_NORTH},
		{{6, 3}, CD_EAST},
		{{0, 3}, CD_WEST}
	});

static RoomData room_9x9_3_door_T_Storeroom(
	"Rooms/9x9_3door_T_Storeroom_BP.9x9_3door_T_Storeroom_BP'", 9,
	{
		{{4, 0}, CD_NORTH},
		{{8, 4}, CD_EAST},
		{{0, 2}, CD_WEST}
	});

static RoomData room_9x9_3_door_T_Torture(
	"Rooms/9x9_3door_T_Torture_BP.9x9_3door_T_Torture_BP'", 9,
	{
		{{4, 0}, CD_NORTH},
		{{8, 4}, CD_EAST},
		{{0, 2}, CD_WEST}
	});

static RoomData room_9x9_3_door_T_Upper(
	"Rooms/9x9_3door_T_Upper_BP.9x9_3door_T_Upper_BP'", 9,
	{
		{{4, 0}, CD_NORTH},
		{{8, 4}, CD_EAST},
		{{0, 2}, CD_WEST}
	});



//Contains reference to all potential rooms
static std::vector<RoomData> GLOBAL_ROOM_DATA =
{
	room_3x3_1door,
	room_3x3_1_door_fire,
	room_3x3_1_door_kitchen,
	room_3x3_2door_R,
	room_3x3_2door_R_Font,
	room_3x3_2door_R_Storeroom,
	room_3x3_2door_straight,
	room_3x3_2door_straight_corridor,
	room_3x3_3door_T,
	room_3x3_3door_T_dark,
	room_3x3_4door_cross,
	room_3x3_4door_cross_font,
	room_5x5_3door_T,
	room_5x5_3door_T_Storeroom,
	room_5x5_3door_T_Circle,
	room_7x7_3door_T_Cage,
	room_7x7_3door_T_Pillars,
	room_7x7_3door_T_Circle,
	room_9x9_3_door_T_Storeroom,
	room_9x9_3_door_T_Torture,
	room_9x9_3_door_T_Upper
};

//Containers for futureproofing
static std::vector<RoomData> STRAIGHT_CORRIDOR_DATA =
{
	corridor_room,
	corridor2_room,
	corridor3_room,
	corridor4_room
};

static std::vector<RoomData> T_CORRIDOR_DATA =
{
	corridor_room_t
};

static std::vector<RoomData> CROSS_CORRIDOR_DATA =
{
	corridor_room_cross
};

//Matrix of all corridor variants/rooms
static std::vector<std::vector<RoomData>> GLOBAL_CORRIDOR_DATA = {
	STRAIGHT_CORRIDOR_DATA, CROSS_CORRIDOR_DATA, T_CORRIDOR_DATA
};

static RoomData GetRandomCorridorOfType(Corridor_Type type)
{
	std::vector<RoomData> potential_corridors = GLOBAL_CORRIDOR_DATA[type];
	std::random_shuffle(potential_corridors.begin(), potential_corridors.end());
	return potential_corridors[0];
};


#endif