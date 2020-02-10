#pragma once

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