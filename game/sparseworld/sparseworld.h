#ifndef SPARSEWORLD_H
#define SPARSEWORLD_H

#include <list>
#include <cstdlib>

#include "sparsenode.h"

class SparseWorld {
	std::list<SparseNode *> All;
	SparseNode * faces[6];
public:
	SparseWorld();
	~SparseWorld();

	void update();
	SparseNode * addNode(vec4<float>);
	SparseNode * addNode(vec4<float>, SparseNode *);

	void test();
	
};

void SparseWorld_Test();

#endif
