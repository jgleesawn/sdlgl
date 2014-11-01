#ifndef SPARSENODE_H
#define SPARSENODE_H

#include <stdio.h>

#include "util/othertypes.h"

enum Dim {
	X,
	Y,
	Z
};
enum Dir {
	N,
	P
};

class SparseNode {
protected:
	vec4<float> position;
//returns true while its updating;
//returns false when finished;
	bool updateD(Dim);

public:
	SparseNode * surrounding[6];
	SparseNode(vec4<float>);

	void add(SparseNode *);
	void rem();

	void update();
	float get(Dim);

	int testIsSurrounded();
	void show();
};

class Face : public SparseNode {
public:
	Face(vec4<float>);
	void rem();
};


#endif


