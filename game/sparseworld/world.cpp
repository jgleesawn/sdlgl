#include "world.h"

World::World() : ot(glm::vec4(-200, -200, -200, 0), glm::vec4(200, 200, 200, 0)) {
}

void World::addObject( Object * obj ) {
	obj->worldsInfoPtr = ot.addVector(&obj->position);
}
