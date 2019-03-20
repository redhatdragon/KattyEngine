#pragma once
#include <time.h>
#include <stdio.h>
#include "IO_API/IO_API.h"
#include "ECS.h"

#include <Windows.h>

clock_t c;

void gameStart() {
	c = clock();
	
	unsigned int healthID = ECSRegisterComponent("health", sizeof(struct CHealth));

	void *player = ECSGetNewEntity();
	struct CHealth newHealth = { 5 };
	ECSAddComponentToEntity(player, &newHealth, healthID);
	//ECSRegisterEntity(player);

	unsigned int componentCount;
	//uint8_t *component = ECSGetAllComponentsOfType(healthID, &componentCount);
	struct CHealth *component = ECSGetAllComponentsOfType(healthID, &componentCount);
	for (unsigned int i = 0; i < componentCount; i++) {
		//struct CHealth *currentComponent = &component[sizeof(struct CHealth)*i];
		struct CHealth *currentComponent = &component[i];
		printf("%i", currentComponent->data);
		currentComponent->data++;
		printf("%i", currentComponent->data);
	}
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