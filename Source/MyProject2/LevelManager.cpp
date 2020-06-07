// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelManager.h"
#include "UObject/ConstructorHelpers.h"
#include "EngineUtils.h"

LevelManager::LevelManager()
{

}

LevelManager::~LevelManager()
{
}

void LevelManager::LM_DoSomething()
{
}

UObject* LevelManager::GetObjectFromFile(FString file_path, FString object_name)
{
	//Blueprint class name / identifier uses _C Suffix
	FString class_name(object_name);
	class_name.Append("_C");

	const FString room_directory = file_path;

	//Looks through room directory and pulls out objects with blueprint name
	TArray<UObject*> tempArray;
	if (EngineUtils::FindOrLoadAssetsByPath(room_directory, tempArray, EngineUtils::ATL_Class))
	{
		for (int i = 0; i < tempArray.Num(); ++i)
		{
			UObject* temp = tempArray[i];
			if (temp != NULL && temp->GetName().Compare(class_name) == 0)
			{
				return temp;
			}
		}
	}

	return NULL;

}

void LevelManager::SpawnRoomActor(std::string blueprint_name, FVector world_pos, FRotator world_rot, int room_size, UObject* obj)
{
	UObject* RoomObject = this->GetObjectFromFile("/Game/Blueprints/Rooms", blueprint_name.c_str());
	if (RoomObject)
	{
		UClass* RoomClass = Cast<UClass>(RoomObject);
		if (RoomClass == NULL)
			return;

		// Create the actor to spawn in the level
		UWorld* World = GWorld;
		ARoomActor* RoomActor = World->SpawnActor<ARoomActor>(RoomClass, world_pos, world_rot);
		// Initialise the room - set box collider values
		if(RoomActor) RoomActor->InitializeRoom(room_size);
	}
	
	
}

void LevelManager::CreateLevel(const int seed)
{
	this->_CreateLevel(seed);
}

void LevelManager::_CreateLevel(const int seed)
{
	//function that creates and stores the level, generated via the seed.
	Map new_map({ MAP_DIMENSIONS_X, MAP_DIMENSIONS_Y });

	// generate all the rooms to be added
	new_map.GenerateFromRoomData(seed);
	new_map.ConnectCorridors();

	// add all rooms to the level
	_CreateRoomsFromMap(new_map);
}

void LevelManager::_CreateRoom(Room& room)
{
	const float unreal_individual_tile_size = 100.f;
	const float our_scale = 4.0f;
	const float cell_to_unreal_size = (unreal_individual_tile_size * our_scale);

	int x = room.m_origin.x - (MAP_DIMENSIONS_X / 2) -2;
	int y = room.m_origin.y - (MAP_DIMENSIONS_Y / 2) -2;
	int room_size = room.m_dimensions.x;

	//Take that out, scale it to unreal
	float xScaled = x * cell_to_unreal_size;
	float yScaled = y * cell_to_unreal_size;
	float offset = ((float)room_size / 2.f) * cell_to_unreal_size;

	SpawnRoomActor(room.m_file_path, { xScaled + offset, yScaled + offset, 0 }, FRotator(0, 90*(int)room.m_rot, 0), room_size, room.m_object_ref);
}

void LevelManager::_CreateRoomsFromMap(Map map)
{

	std::for_each(map.m_rooms.begin(), map.m_rooms.end(), [&](Room& room)
	{
		_CreateRoom(room);
	});
	std::for_each(map.m_corridors.begin(), map.m_corridors.end(), [&](Room& room)
	{
		_CreateRoom(room);
	});
	std::for_each(map.m_blockages.begin(), map.m_blockages.end(), [&](Room& room)
	{
		_CreateRoom(room);
	});
}
