#pragma once

#include "LevelDefines.h"
#include "RoomData.h"
#include <vector>
#include <string>
#include "UObject.h"

struct Room
{
	Coord	m_origin;
	Coord	m_dimensions;

	std::vector<Door> m_doors;
	std::string m_file_path;

	Prefab_Rotation m_rot = PR_0_DEG;

	UObject* m_object_ref = NULL;

	Room(RoomData data, Coord new_origin)
	{
		m_dimensions = data.m_dimensions;
		m_origin = new_origin;
		m_doors = data.m_doors;
		m_file_path = data.m_file_path;

		/*char buffer[100];
		const char* root_directory = "/Game/Blueprints/";
		strcpy(buffer, root_directory);
		strcat(buffer, m_file_path.c_str());
		const FString test2(buffer);

		//const TCHAR* test = TEXT(*test2);
		// Load room using file path

		UObject* RoomObject = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, ANSI_TO_TCHAR(buffer)));
		//static ConstructorHelpers::FObjectFinder<UObject> room_obj(TEXT("/Game/Blueprints/Rooms/5x5_1door_start.5x5_1door_start"));
		if (RoomObject)
		{
			m_object_ref = RoomObject;
		}*/
	}


	//Returns whether the current room intersects with another
	bool Intersects(Room& room, int offset = 0)
	{
		Coord l_room_1 = m_origin;
		Coord r_room_1 = { m_origin.x + m_dimensions.x - 1, m_origin.y + m_dimensions.y - 1 };

		Coord l_room_2 = room.m_origin;
		Coord r_room_2 = { room.m_origin.x + room.m_dimensions.x - 1, room.m_origin.y + room.m_dimensions.y - 1 };

		l_room_2.x -= offset;
		l_room_2.y -= offset;
		r_room_2.x += offset;
		r_room_2.y += offset;

		// If one rectangle is on left side of other 
		if (l_room_1.x > r_room_2.x || l_room_2.x > r_room_1.x)
			return false;

		// If one rectangle is above other 
		if (l_room_1.y > r_room_2.y || l_room_2.y > r_room_1.y)
			return false;

		return true;

	}
};