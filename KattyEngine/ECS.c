#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ECS.h"

struct Entity {  //Basically the game object
	void *component[20];  //Indirection looks innefecient but the below manager explains things.
	unsigned int componentType[20];
	unsigned int componentCount;
};

//A collection of components of varying types stored in a 2D buffer
//Casting will be required
struct EntityManager {
	#define TOTAL_BUFFERED_PER_TYPE 64*10000
	#define MAX_TYPES 64
	uint8_t componentArray[MAX_TYPES][TOTAL_BUFFERED_PER_TYPE];
	struct Entity *parentEntity[MAX_TYPES][10000];
	unsigned int componentArrayCount[MAX_TYPES];
	char *componentName[MAX_TYPES];
	unsigned int componentSize[MAX_TYPES];
	unsigned int componentTypeCount;
} entityManager = { 0 };
void EntityManagerAddComponent(unsigned int type, void *componentToCopy, unsigned int sizeOfComponent) {
	void *component = &entityManager.componentArray[type][entityManager.componentArrayCount[type]];
	memcpy(component, componentToCopy, sizeOfComponent);
}

struct ECS {
	struct Entity entity[100000];
	unsigned int entityCount;
} ecs = { 0 };



void *ECSGetNewEntity() {
	void *returnThis = &ecs.entity[ecs.entityCount];
	memset(returnThis, 0, sizeof(struct Entity));
	ecs.entityCount++;
	return returnThis;
}
void ECSDestroyEntity(void *entity) {
	struct Entity *ent = entity;
	unsigned int componentCount = ent->componentCount;
	for (unsigned int i = 0; i < componentCount; i++) {
		ECSRemoveComponentFromEntity(entity, 0);
	}
	unsigned int entityCount = ecs.entityCount;
	for (unsigned int i = 0; i < entityCount; i++) {
		if (&ecs.entity[i] == ent) {
			ecs.entityCount--;
			ecs.entity[i] = ecs.entity[ecs.entityCount];
			return;
		}
	}
	printf("Error: invalid entity address passed to ECSDestroyEntity.");
	system("pause");
	exit(EXIT_FAILURE);
}
unsigned int ECSRegisterComponent(const char *name, unsigned int sizeOfComponent) {
	unsigned int nameCount = entityManager.componentTypeCount;
	for (unsigned int i = 0; i < nameCount; i++) {
		const char *otherName = entityManager.componentName[i];
		if (strcmp(name, otherName) == 0) {
			printf("Error: Registering component '", name, "' more than once.");
			printf("Will proceed anyway.");
			return i;
		}
	}
	entityManager.componentTypeCount++;
	entityManager.componentSize[nameCount] = sizeOfComponent;
	unsigned int nameLen = strlen(name)+1;
	entityManager.componentName[nameCount] = malloc(nameLen);
	memcpy(entityManager.componentName[nameCount], name, nameLen);
	return nameCount;
}
int ECSGetComponentTypeFromName(const char *name) {
	unsigned int nameCount = entityManager.componentTypeCount;
	for (unsigned int i = 0; i < nameCount; i++) {
		const char *otherName = entityManager.componentName[i];
		if (strcmp(name, otherName) == 0)
			return i;
	}
	printf("Error: Component '", name, "' does not exist.");
	printf("Returning -1 and proceeding anyway.");
	return -1;
}
void ECSAddComponentToEntity(void *entity, void *componentToCopy, unsigned int componentID) {
	struct Entity *ent = entity;
	unsigned int cmpSize = entityManager.componentSize[componentID];
	//entityManager.componentArray[componentID][entityManager.componentArrayCount[componentID]] = malloc(cmpSize);
	void *cmpDest =
		&entityManager.componentArray[componentID][entityManager.componentArrayCount[componentID]*cmpSize];
	memcpy(cmpDest, componentToCopy, cmpSize);
	entityManager.parentEntity[componentID][entityManager.componentArrayCount[componentID]] = ent;
	entityManager.componentArrayCount[componentID] += 1;
	ent->component[ent->componentCount] = cmpDest;
	//ent->component[ent->componentCount] = &entityManager.componentArray[componentID][entityManager.componentArrayCount[componentID]];
	ent->componentType[ent->componentCount] = componentID;
	ent->componentCount++;
	return;
}
void ECSRemoveComponentFromEntity(void *entity, unsigned int index) {
	struct Entity *ent = entity;
	if (index >= ent->componentCount) {
		printf("Error: ECSRemoveComponentFromEntity was passed an invalid index.");
		exit(EXIT_FAILURE);
	}
	void *componentToReplace = ent->component[index];
	ent->componentCount--;
	ent->component[index] = &ent->component[ent->componentCount];
	unsigned int componentID = ent->componentType[ent->componentCount];
	void *componentToMove = entityManager.componentArray[entityManager.componentArrayCount[componentID]];
	memcpy(componentToReplace, componentToMove, entityManager.componentSize[componentID]);


	entityManager.componentArrayCount[componentID]--;
}
void *ECSGetAllComponentsOfType(unsigned int componentID, unsigned int *outCount) {
	*outCount = entityManager.componentArrayCount[componentID];
	return &entityManager.componentArray[componentID][0];
}

void *ECSGetParentEntity(unsigned int componentID, unsigned int index) {
	struct Entity *entity = entityManager.parentEntity[componentID][index];
	//printf("%d", &entity->component[0]);
	return entity;
}
void *ECSGetComponentFromEntity(unsigned int componentID, void *parentEntity) {
	struct Entity *parent = parentEntity;
	unsigned int componentCount = parent->componentCount;
	for (unsigned int i = 0; i < componentCount; i++) {
		if (componentID == parent->componentType[i]) {
			void *returnThis = parent->component[i];
			return returnThis;
		}
	}
	return NULL;
}