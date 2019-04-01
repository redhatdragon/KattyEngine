#pragma once
//id EntityManagerAddComponent(unsigned int type, void *componentToCopy, unsigned int sizeOfComponent);

//unsigned int ECSCreateEntityType(unsigned int sizeOfEntity);
//void ECSAddEntity(void *entity, unsigned int type, unsigned int sizeOfEntity);

void *ECSGetNewEntity();
void ECSDestroyEntity(void *entity);
unsigned int ECSRegisterComponent(const char *name, unsigned int sizeOfComponent);
int ECSGetComponentTypeFromName(const char *name);
void ECSAddComponentToEntity(void *entity, void *component, unsigned int componentID);
void ECSRemoveComponentFromEntity(void *entity, unsigned int index);
void *ECSGetAllComponentsOfType(unsigned int componentID, unsigned int *outCount);
void *ECSGetParentEntity(unsigned int componentID, unsigned int index);
void *ECSGetComponentFromEntity(unsigned int componentID, void *parentEntity);