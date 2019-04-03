#include "engine.h"
#include "IO_API/IO_API.h"
#include "ECS.h"
#include "JSON.h/json.h"
#include "math/math.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void jsonTest() {
	const char json[] = "{\"a\" : true, \"b\" : [false, null, \"foo\"]}";
	struct json_value_s* root = json_parse(json, strlen(json));
	/* root->type is json_type_object */

	struct json_object_s* object = (struct json_object_s*)root->payload;
	/* object->length is 2 */

	struct json_object_element_s* a = object->start;

	struct json_string_s* a_name = a->name;
	/* a_name->string is "a" */
	/* a_name->string_size is strlen("a") */

	struct json_value_s* a_value = a->value;
	/* a_value->type is json_type_true */
	/* a_value->payload is NULL */

	struct json_object_element_s* b = a->next;
	/* b->next is NULL */

	struct json_string_s* b_name = b->name;
	/* b_name->string is "b" */
	/* b_name->string_size is strlen("b") */

	struct json_value_s* b_value = b->value;
	/* b_value->type is json_type_array */

	struct json_array_s* array = (struct json_array_s*)b_value->payload;
	/* array->length is 3 */

	struct json_array_element_s* b_1st = array->start;

	struct json_value_s* b_1st_value = b_1st->value;
	/* b_1st_value->type is json_type_false */
	/* b_1st_value->payload is NULL */

	struct json_array_element_s* b_2nd = b_1st->next;

	struct json_value_s* b_2nd_value = b_2nd->value;
	/* b_2nd_value->type is json_type_null */
	/* b_2nd_value->payload is NULL */

	struct json_array_element_s* b_3rd = b_2nd->next;
	/* b_3rd->next is NULL */

	struct json_value_s* b_3rd_value = b_3rd->value;
	/* b_3rd_value->type is json_type_string */

	struct json_string_s* string = (struct json_string_s*)b_3rd_value->payload;
	/* string->string is "foo" */
	/* string->string_size is strlen("foo") */

	/* Don't forget to free the one allocation! */
	free(root);
}
struct json_object_element_s *jsonGetVariable(struct json_object_s *object, const char *variableName) {
	unsigned int length = object->length;
	for (unsigned int i = 0; i < length; i++) {
		struct json_object_element_s *element = object->start;
		struct json_string_s *name = element->name;
		if (strcmp(name->string, variableName) == 0) {
			return element;
		}
	}
	return 0;
}

void getJsonDataFromFile(const char *fileName, char *outData) {
	getFileData(fileName, outData, 0, 1024);
}

void importUnit(struct json_object_s *object) {
	void *ent = ECSGetNewEntity();
	unsigned int healthID = ECSGetComponentTypeFromName("health");
	unsigned int speedID = ECSGetComponentTypeFromName("speed");
	struct json_object_element_s *healthVar = jsonGetVariable(object, "health");
	struct json_object_element_s *speedVar = jsonGetVariable(object, "speed");
	if (healthVar) {
		char *healthStr = ((struct json_number_s*)healthVar->value->payload)->number;
		unsigned int health = atoi(healthStr);
		ECSAddComponentToEntity(ent, health, healthID);
	}
	if (speedVar) {
		char *speedStr = ((struct json_number_s*)speedVar->value->payload)->number;
		unsigned int speed = atoi(speedStr);
		ECSAddComponentToEntity(ent, speed, speedID);
	}
}

void loadLevel() {
	/*unsigned int textureID = ECSRegisterComponent("texture", sizeof(struct Texture));
	unsigned int positionID = ECSRegisterComponent("position", sizeof(struct Point2DI));
	for (unsigned int i = 0; i < 10; i++) {
		void *newEnt = ECSGetNewEntity();
		struct Point2DI pos = { 0 + i * 64, 0 };
		struct Texture tex;
		getTexture("test.png", &tex);
		ECSAddComponentToEntity(newEnt, &pos, positionID);
		ECSAddComponentToEntity(newEnt, &tex, textureID);
	}
	void *ent = ECSGetParentEntity(textureID, 3);
	ECSDestroyEntity(ent);*/
	for (unsigned int i = 0; i < 10; i++) {
		char json[256 * 8] = { 0 };
		getJsonDataFromFile("data/Units/exampleUnit2.json", json);
		struct json_value_s *root = json_parse(json, strlen(json));
		struct json_object_s *jsonObject = (struct json_object_s*)root->payload;
		struct json_object_element_s *type = jsonGetVariable(jsonObject, "type");
		if (type) {
			const char *typeName = type->name->string;
			if (strcmp(typeName, "unit") == 0) {
				importUnit(jsonObject);
			}
		}
	}
}