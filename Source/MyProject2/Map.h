#pragma once

#include "LevelDefines.h"
#include "Room.h"
#include <algorithm>

struct Map
{
	Coord m_dimensions;
	std::vector<Room> m_rooms;
	std::vector<Room> m_corridors;

	Map()
	{
	}

	Map(Coord new_dimensions) :
		m_dimensions(new_dimensions)
	{
	}

	bool RoomIsValid(Room& room, int offset = 1)
	{
		bool valid = true;

		//A room is valid if it fits within the play area
		if (room.m_origin.x >= 0 &&
			room.m_origin.y >= 0 &&
			room.m_origin.x + room.m_dimensions.x - 1 < m_dimensions.x &&
			room.m_origin.y + room.m_dimensions.y - 1 < m_dimensions.y)
		{
			//Does it overlap with any other rooms?
			std::for_each(m_rooms.begin(), m_rooms.end(), [&](Room& r)
			{
				if (valid && r.Intersects(room, offset))
					valid = false;
			});
		}
		else
		{
			valid = false;
		}

		return valid;
	}
	

	//NEW FUNCTIONS
	void GenerateFromRoomData(int seed)
	{
		srand(seed);

		while (m_rooms.size() < 25)
		{
			m_rooms.clear();
			m_corridors.clear();

			AddRoomFromRoomData(start_room_5x5_1door, { (MAP_DIMENSIONS_X/2)-2, (MAP_DIMENSIONS_Y / 2) - 2 });

			for (int i = 0; i < 100; i++)
				AddRoomsToDoor();
		}
	}

	void AddRoomsToDoor()
	{
		std::vector<RoomData> potential_rooms = GLOBAL_ROOM_DATA;
		std::random_shuffle(potential_rooms.begin(), potential_rooms.end());
		std::random_shuffle(m_rooms.begin(), m_rooms.end());

		std::vector<int> potential_rotations = { 0, 1, 2, 3 };
		std::vector<int> potential_corridor_lengths = { 1, 1, 1, 2, 2, 3 };

		bool has_added_room = false;
		for (int curr_room_idx = 0; curr_room_idx < m_rooms.size() && !has_added_room; curr_room_idx++)
		{
			Room& curr_room = m_rooms[curr_room_idx];
			for (int curr_door_idx = 0; curr_door_idx < curr_room.m_doors.size() && !has_added_room; curr_door_idx++)
			{
				Door& curr_door = curr_room.m_doors[curr_door_idx];

				for (int new_room_idx = 0; new_room_idx < potential_rooms.size() && !has_added_room && !curr_door.IsConnected(); new_room_idx++)
				{
					RoomData new_room = potential_rooms[new_room_idx];

					//For every rotation of the room
					//std::random_shuffle(potential_rotations.begin(), potential_rotations.end());
					for (int r = 0; r < potential_rotations.size() && !has_added_room && !curr_door.IsConnected(); r++)
					{
						
						for (int new_door_idx = 0; new_door_idx < new_room.m_doors.size() && !has_added_room && !curr_door.IsConnected(); new_door_idx++)
						{
							Door& new_door = new_room.m_doors[new_door_idx];
							//Only try place rooms if they are of the right orientation
							if (IsOppositeDirection(curr_door.m_local_dir, new_door.m_local_dir))
							{
								//position the new room where it should be 
								Coord curr_door_world_pos = { curr_door.m_local_pos.x + curr_room.m_origin.x, curr_door.m_local_pos.y + curr_room.m_origin.y };
								Coord new_door_world_pos = { curr_door_world_pos.x - new_door.m_local_pos.x, curr_door_world_pos.y - new_door.m_local_pos.y };

								const int room_gap = 1;
								const int min_corridor_length = room_gap;
								const int max_corridor_length = min_corridor_length + 2;
								//const int corridor_length = RandomIntInRange(min_corridor_length, max_corridor_length);
								std::random_shuffle(potential_corridor_lengths.begin(), potential_corridor_lengths.end());
								const int corridor_length = potential_corridor_lengths[0];



								Coord corridor_dir = GetDirectionFromCardinal(curr_door.m_local_dir);
								switch (curr_door.m_local_dir)
								{
								case CD_NORTH:
								{
									new_door_world_pos.y -= (corridor_length + 1);
									break;
								}
								case CD_EAST:
								{
									new_door_world_pos.x += (corridor_length + 1);
									break;
								}
								case CD_SOUTH:
								{
									new_door_world_pos.y += (corridor_length + 1);
									break;
								}
								case CD_WEST:
								{
									new_door_world_pos.x -= (corridor_length + 1);
									break;
								}
								}

								new_door.SetConnected(true);
								Room room(new_room, new_door_world_pos);
								if (RoomIsValid(room, room_gap))
								{
									has_added_room = true;

									curr_door.SetConnected(true);

									room.m_rot = (Prefab_Rotation)r;
									m_rooms.push_back(room);

									//Add corridor between doors
									for (int i = 0; i < corridor_length; i++)
									{
										int corridor_num = i + 1;

										Room corr(corridor_room, { curr_door_world_pos.x + (corridor_dir.x * corridor_num), curr_door_world_pos.y + (corridor_dir.y * corridor_num) });
										corr.m_rot = (Prefab_Rotation)curr_door.m_local_dir;
										m_corridors.push_back(corr);// Room(PT_CORRIDOR, { curr_door_world_pos.x + (corridor_dir.x * corridor_num), curr_door_world_pos.y + (corridor_dir.y * corridor_num) }, PR_0_DEG));
									}
								}
								else
								{
									//Reset door state for next rotation check
									new_door.SetConnected(false);
								}
							}
						}

						new_room.rotate90(1);
					}
				}
			}
		}
	}

	bool IsOppositeDirection(Cardinal_Direction first, Cardinal_Direction second)
	{
		bool is_opposite = false;
		switch (first)
		{
		case CD_NORTH:
		{
			is_opposite = (second == CD_SOUTH);
			break;
		}
		case CD_EAST:
		{
			is_opposite = (second == CD_WEST);
			break;
		}
		case CD_SOUTH:
		{
			is_opposite = (second == CD_NORTH);
			break;
		}
		case CD_WEST:
		{
			is_opposite = (second == CD_EAST);
			break;
		}
		}
		return is_opposite;
	}

	void AddRoomFromRoomData(RoomData data, Coord origin)
	{
		Room new_room(data, origin);
		m_rooms.push_back(new_room);

	}

	void ConnectCorridors()
	{
		// check each room in the map
		for (int roomIndex = 0; roomIndex < m_rooms.size(); ++roomIndex)
		{
			// check each door in each room
			for (int doorIndex = 0; doorIndex < m_rooms[roomIndex].m_doors.size(); ++doorIndex)
			{
				// If door isnt connected to another room, try and connect to room/corridor
				if (!m_rooms[roomIndex].m_doors[doorIndex].IsConnected())
				{
					Coord oldDoorPos = { m_rooms[roomIndex].m_doors[doorIndex].m_local_pos.x + m_rooms[roomIndex].m_origin.x, m_rooms[roomIndex].m_doors[doorIndex].m_local_pos.y + m_rooms[roomIndex].m_origin.y };

					Door potentialConnectedDoor;
					bool validDoor = false;
					Room potentialConnectedCorr(corridor_room, { 0, 0 });
					bool validCorr = false;

					checkValidDoor(oldDoorPos, potentialConnectedDoor, validDoor);
					checkValidCorr(oldDoorPos, potentialConnectedCorr, validCorr);
					
					// if there is a valid door, connect corridor to valid door
					if (validDoor)
					{

					}
					// if there is a valid corridor, connect corridor to valid corridor
					else if (validCorr)
					{

					}
					// Block door as it cannot connect to anything
					else
					{

					}
				}
			}
		}
	}

	void checkValidDoor(Coord oldDoorPos, Door& newDoor, bool& valid)
	{
		// check each room in the map
		for (int roomIndex = 0; roomIndex < m_rooms.size(); ++roomIndex)
		{
			// check each door in each room
			for (int doorIndex = 0; doorIndex < m_rooms[roomIndex].m_doors.size(); ++doorIndex)
			{

			}
		}
	}

	void checkValidCorr(Coord oldDoorPos, Room& corridor, bool& valid)
	{

	}
};