// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelManager.h"

LevelManager::LevelManager()
{

}

LevelManager::~LevelManager()
{
}

void LevelManager::LM_DoSomething()
{
}

void LevelManager::SpawnBlueprintActor(const char* file_path, FVector world_pos, FRotator world_rot)
{
	char buffer[100];
	const char* root_dir = "Blueprint'/Game/Blueprints/";
	strcpy(buffer, root_dir);
	strcat(buffer, file_path);

	UObject* SpawnActor = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, ANSI_TO_TCHAR(buffer)));

	UBlueprint* GeneratedBP = Cast<UBlueprint>(SpawnActor);
	if (!SpawnActor)
	{
		return;
	}

	UClass* SpawnClass = SpawnActor->StaticClass();
	if (SpawnClass == NULL)
	{
		return;
	}

	UWorld* World = GWorld;
	World->SpawnActor<AActor>(GeneratedBP->GeneratedClass, world_pos, world_rot);
}

void LevelManager::CreateLevel(const int seed)
{
	this->_CreateLevel(seed);
}

void LevelManager::_CreateLevel(const int seed)
{
	//function that creates and stores the level, generated via the seed.
	Map new_map({ MAP_DIMENSIONS_X, MAP_DIMENSIONS_Y });

	// Spawn initial rooms
	new_map.GenerateFromRoomData(1);
	new_map.ConnectCorridors();

	_CreateRoomsFromMap(new_map);


}

void LevelManager::_CreateRoom(Room& room)
{
	const float unreal_individual_tile_size = 100.f;
	const float our_scale = 4.0f;
	float room_size = 3.0f;
	float offset = (room_size / 2.f) * (unreal_individual_tile_size * our_scale);

	const float cell_to_unreal_size = (unreal_individual_tile_size * our_scale);

	//Stuff that would be in room_data
	int x1 = room.m_origin.x - (MAP_DIMENSIONS_X / 2) -2;
	int y1 = room.m_origin.y - (MAP_DIMENSIONS_Y / 2) -2;
	int roomsize1 = room.m_dimensions.x;

	//Take that out, scale it to unreal
	float x1Scaled = x1 * cell_to_unreal_size;
	float y1Scaled = y1 * cell_to_unreal_size;
	float offset1 = ((float)roomsize1 / 2.f) * cell_to_unreal_size;

	SpawnBlueprintActor(room.m_file_path, { x1Scaled + offset1, y1Scaled + offset1, 0 }, FRotator(0, 90*(int)room.m_rot, 0));
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
}
