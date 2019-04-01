#include "engine.h"
#include "IO_API/IO_API.h"
#include "ECS.h"
#include "JSON.h/json.h"
#include "math/math.h"

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

char *getJsonDataFromFile(const char *fileName) {

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

}