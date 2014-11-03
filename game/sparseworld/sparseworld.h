#ifndef SPARSEWORLD_H
#define SPARSEWORLD_H

#include <vector>
#include <algorithm>
#include <utility>
#include <stack>

#include <stdlib.h>

#include "object/object.h"

enum Dim {
	X,
	Y,
	Z
};

class SparseWorld {
	std::vector<Object *> sortedObj[3];

	void sort_indices(Dim);
public:
	
	void addVertex(Object *);
	void remVertex(Object *);

	void sort();
};


#endif
