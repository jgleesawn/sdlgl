#include "world.h"

#include <iostream>

void printv(const glm::vec4 & v) {
	for( int i=0; i<4; i++ )
		std::cout << v[i] << " ";
	std::cout << std::endl;
}

World::World() : ot(glm::vec4(-200, -200, -200, 0), glm::vec4(200, 200, 200, 0)) {
	printv(ot.LL);
	printv(ot.UR);
	printv(ot.UR-ot.LL);
}

void World::addObject( Object * obj ) {
	obj->worldsInfoPtr = ot.addVector(&obj->position, (void * ) obj);
}
