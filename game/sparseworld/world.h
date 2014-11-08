#ifndef WORLD_H
#define WORLD_H

#include "util/octtree.h"
#include "object/object.h"

class World {
public:
	OctTree ot;

public:
	World();
	void addObject( Object * );
	
};


#endif
