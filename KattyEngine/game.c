#include <time.h>
#include <stdio.h>
#include "IO_API/IO_API.h"
#include "ECS.h"
#include "math/math.h"
#include "engine.h"

#include <Windows.h>

clock_t c;

void gameStart() {
	c = clock();
	loadLevel();
}

void gameEnd() {

}

void render() {
	unsigned int textureCount;
	unsigned int positionID = ECSGetComponentTypeFromName("position");
	unsigned int textureID = ECSGetComponentTypeFromName("texture");
	struct Texture *textures = ECSGetAllComponentsOfType(textureID, &textureCount);
	for (unsigned int i = 0; i < textureCount; i++) {
		void *parentEntity = ECSGetParentEntity(textureID, i);
		struct Point2DI *drawPos = ECSGetComponentFromEntity(positionID, parentEntity);
		if (drawPos) {
			struct Texture *t = &textures[i];
			drawTexture(t, drawPos->x, drawPos->y);
		}
	}
}
void gameTick() {
	double duration = (clock() - c) / (double)CLOCKS_PER_SEC;

	if (duration < (double)1 / 60) {
		if (duration < (double)1 / 80)
			Sleep(((double)1 / 120));

		render();
		return;
	}
	c = clock();
}

void start() {
	cWidth = 640;
	cHeight = 480;
	gameStart();
}
void appLoop() {
	gameTick();
}
void end() {
	gameEnd();
}