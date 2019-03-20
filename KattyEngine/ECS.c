#include <stdint.h>
#include <string.h>
#include <stdio.h>

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
	struct Entity *parentEntity[MAX_TYPES][TOTAL_BUFFERED_PER_TYPE];
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
	ecs.entityCount++;
	return returnThis;
}
unsigned int ECSRegisterComponent(const char *name, unsigned int sizeOfComponent) {
	unsigned int nameCount = entityManager.componentTypeCount;
	for (unsigned int i = 0; i < nameCount; i++) {
		if (strcmp(name, entityManager.componentArray[i])) {
			return i;
			printf("Error: Registering component '", name, "' more than once.");
			printf("Will proceed anyway.");
		}
	}
	entityManager.componentTypeCount++;
	entityManager.componentSize[nameCount] = sizeOfComponent;
	return nameCount;
}
int ECSGetComponentTypeFromName(const char *name) {
	unsigned int nameCount = entityManager.componentTypeCount;
	for (unsigned int i = 0; i < nameCount; i++) {
		if (strcmp(name, entityManager.componentArray[i]))
			return i;
	}
	printf("Error: Component '", name, "' does not exist.");
	printf("Returning -1 and proceeding anyway.");
	return -1;
}
void ECSAddComponentToEntity(void *entity, void *componentToCopy, unsigned int componentID) {
	struct Entity *ent = entity;
	unsigned int cmpSize = entityManager.componentSize[componentID];
	entityManager.componentArray[componentID][entityManager.componentArrayCount[componentID]] = malloc(cmpSize);
	void *cmpDest =
		&entityManager.componentArray[componentID][entityManager.componentArrayCount[componentID]];
	memcpy(cmpDest, componentToCopy, cmpSize);
	entityManager.parentEntity[componentID][entityManager.componentArrayCount[componentID]] = entity;
	entityManager.componentArrayCount[componentID]++;
}
//void ECSRegisterEntity(void *entity);
/*void ECSGetAllComponentsOfType(unsigned int componentID,
	void *outFirstComponent, unsigned int *outCount) {
	outFirstComponent = entityManager.componentArray[componentID][0];
	outCount = entityManager.componentArrayCount[componentID];
}*/
void *ECSGetAllComponentsOfType(unsigned int componentID, unsigned int *outCount) {
	*outCount = entityManager.componentArrayCount[componentID];
	return &entityManager.componentArray[componentID][0];
}