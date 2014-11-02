#ifndef SPARSEWORLD_H
#define SPARSEWORLD_H

#include <vector>
#include <algorithm>
#include <utility>
#include <stack>

#include <stdlib.h>

#include "util/othertypes.h"

enum Dim {
	X,
	Y,
	Z
};

class SparseWorld {
	std::vector<int> ibo[3];

	std::vector<vec4<float> > vbo;

	std::stack<int> removed_vertex_ind;

	void sort_indices(Dim);
public:
	
	void addVertex(vec4<float>);
	void remVertex(int);

	void sort();
};


#endif
