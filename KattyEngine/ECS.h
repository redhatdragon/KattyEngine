#pragma once
//id EntityManagerAddComponent(unsigned int type, void *componentToCopy, unsigned int sizeOfComponent);

//unsigned int ECSCreateEntityType(unsigned int sizeOfEntity);
//void ECSAddEntity(void *entity, unsigned int type, unsigned int sizeOfEntity);

void *ECSGetNewEntity();
unsigned int ECSRegisterComponent(const char *name, unsigned int sizeOfComponent);
int ECSGetComponentTypeFromName(const char *name);
void ECSAddComponentToEntity(void *entity, void *component, unsigned int componentID);
//void ECSRegisterEntity(void *entity);
//void ECSGetAllComponentsOfType(unsigned int componentID,
	//void *outFirstComponent, unsigned int *outCount);
void *ECSGetAllComponentsOfType(unsigned int componentID, unsigned int *outCount);

struct CHealth {
	unsigned int data;
};