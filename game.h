#pragma once
#include <time.h>
#include <stdio.h>
#include "IO_API/IO_API.h"

#include <Windows.h>

struct Entity {  //Basically the game object
	void *component[20];  //Indirection looks innefecient right?
	unsigned int componentType[20];
	unsigned int componentCount = 0;
};

//A collection of components of varying types stored in a 2D buffer
//Casting will be required
struct EntityManager {
	#define TOTAL_BUFFERED_PER_TYPE 64*1000
	#define MAX_TYPES 256
	uint8_t componentArray[MAX_TYPES][TOTAL_BUFFERED_PER_TYPE];
	struct Entity *parentEntity[MAX_TYPES][TOTAL_BUFFERED_PER_TYPE];
	unsigned int componentArrayCount[MAX_TYPES] = { 0 };
	#undef MAX_TYPES
	#undef TOTAL_BUFFERED_PER_TYPE
} entityManager;
inline void EntityManagerAddComponent(unsigned int type, void *componentToCopy, unsigned int sizeOfComponent) {
	void *component = &entityManager.componentArray[type][entityManager.componentArrayCount[type]];
	memcpy(component, componentToCopy, sizeOfComponent);
}

struct ECS {
	struct Entity entity[100000];
	unsigned int entityCount = 0;
} ecs;
#define ADD_ENTITY(_entity) \
ecs.entity[entityCount] = _entity; \
entityCount++;



clock_t c;

void gameStart() {
	c = clock();
	
}

void gameEnd() {

}

void gameTick() {
	double duration = (clock() - c) / (double)CLOCKS_PER_SEC;

	if (duration < (double)1 / 60) {
		if (duration < (double)1 / 80)
			Sleep(((double)1 / 120));
		0;
		return;
	}
	c = clock();

	
}