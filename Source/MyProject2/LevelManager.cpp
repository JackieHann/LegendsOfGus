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

void LevelManager::SpawnBlueprintActor(std::string file_path, FVector world_pos, FRotator world_rot)
{
	char buffer[100];
	const char* root_dir = "Blueprint'/Game/Blueprints/";
	strcpy(buffer, root_dir);
	strcat(buffer, file_path.c_str());

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
	AActor* spawnedActor = World->SpawnActor<AActor>(GeneratedBP->GeneratedClass, world_pos, world_rot);
}

void LevelManager::SpawnRoomActor(std::string file_path, FVector world_pos, FRotator world_rot, int room_size)
{
	char buffer[100];
	const char* root_directory = "Blueprint'/Game/Blueprints/";
	strcpy(buffer, root_directory);
	strcat(buffer, file_path.c_str());

	// Load room using file path
	UObject* RoomObject = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, ANSI_TO_TCHAR(buffer)));

	// Cast loaded room to blueprint class
	UBlueprint* RoomBlueprint = Cast<UBlueprint>(RoomObject);
	// break if object cannot be converted
	if (!RoomBlueprint)
		return;
	// Get class data of loaded blueprint
	UClass* RoomClass = RoomBlueprint->StaticClass();
	// break if class data not found
	if (RoomClass == NULL)
		return;
	// Get world pointer
	UWorld* World = GWorld;
	// Create the actor to spawn in the level
	ARoomActor* RoomActor = World->SpawnActor<ARoomActor>(RoomBlueprint->GeneratedClass, world_pos, world_rot);
	
	// Initialise the room - set box collider values
	RoomActor->InitializeRoom(room_size);
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
	const float cell_to_unreal_size = (unreal_individual_tile_size * our_scale);

	int x = room.m_origin.x - (MAP_DIMENSIONS_X / 2) -2;
	int y = room.m_origin.y - (MAP_DIMENSIONS_Y / 2) -2;
	int room_size = room.m_dimensions.x;

	//Take that out, scale it to unreal
	float xScaled = x * cell_to_unreal_size;
	float yScaled = y * cell_to_unreal_size;
	float offset = ((float)room_size / 2.f) * cell_to_unreal_size;

	SpawnRoomActor(room.m_file_path, { xScaled + offset, yScaled + offset, 0 }, FRotator(0, 90*(int)room.m_rot, 0), room_size);
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
