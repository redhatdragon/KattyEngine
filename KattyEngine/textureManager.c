#include "textureManager.h"
#include <string.h>
#include <stdio.h>

#ifndef TEXTURE_BUFFER_CAPACITY
#define TEXTURE_BUFFER_CAPACITY 256
#endif
#ifndef TEXTURE_NAME_CAPACITY
#define TEXTURE_NAME_CAPACITY 16
#endif

void *textureBuffer[TEXTURE_BUFFER_CAPACITY];
char textureNames[TEXTURE_BUFFER_CAPACITY][TEXTURE_NAME_CAPACITY];
unsigned int textureCount = 1;

unsigned int TMBufferTexture(void *texture, const char *textureName) {
	textureBuffer[textureCount] = texture;
	memset(textureNames[textureCount], 0, TEXTURE_NAME_CAPACITY);
	strcpy(textureNames[textureCount][0], textureName);
	unsigned int returnThis = textureCount;
	textureCount++;
	return returnThis;
}
void *TMGetTexture(unsigned int index) {
	if (index >= textureCount || index == 0) {
		printf("Error: TMGetTexture recieved invalid index.");
		return 0;
	}
	return textureBuffer[textureCount];
}
unsigned int TMGetTextureIndex(const char *textureName) {
	for (unsigned int i = 1; i < textureCount; i++) {
		if (strcmp(&textureNames[i][0], textureName))
			return i;
	}
	printf("Error: TMGetTextureIndex recieved invalid textureName.");
	return NULL;
}