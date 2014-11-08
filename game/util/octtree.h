#ifndef OCTTREE_H
#define OCTTREE_H


/* FIX MEMORY LEAK THAT OCCURS FROM NOT PRUNING THE TREE WHEN A NODE MOVES. */

#include <glm/glm.hpp>
#include <iostream>

enum octCorner {
	LLB, LLF, LUB, LUF,
	RLB, RLF, RUB, RUF
};
//	000, 001, 010, 011,
//	100, 101, 110, 111


//Returns box's relative position to v
//Combine result with adjacenty information from vecAdj
bool vecBound( glm::vec4 LL, glm::vec4 UR, glm::vec4 v);

//Returns dimensions that bound v
//Can be used for "adjacency" through bounding in less than all dimensions
int vecAdj( glm::vec4 LL, glm::vec4 UR, glm::vec4 v );

class OctNode;
class Branch;
class Leaf;

class OctNode {
protected:
//public:
	Branch * parent;
	glm::vec4 LL, UR;
	int pos;
public:
	virtual void addLeaf(Leaf *) = 0;
};

class Branch : public OctNode {
protected:
//public:
	OctNode * Nodes[8];
	int ncount;
	Branch() {}	//Is a hack so Root can use in constructor
public:
	Branch(Branch *);
	Branch(Branch *, Leaf *);
	~Branch();
	virtual void addLeaf(Leaf *);

	friend class Leaf;
	friend class Empty;
};

class Root : public Branch {
public:
	Root(glm::vec4, glm::vec4);
	virtual void addLeaf(Leaf *);
};

//Leaf Constructor grabs bounding box from parent.
class Leaf : public OctNode {
protected:
	glm::vec4 * v;
public:
	Leaf(Branch *, glm::vec4 *);
	virtual void addLeaf(Leaf *);
	virtual void update();

	friend class Branch;
	friend class Root;
};


class Empty : public Leaf {
public:
	Empty(Branch *, int);//, glm::vec4 LL_in, glm::vec4 UR_in);
	virtual void addLeaf(Leaf *);
};

class OctTree : public Root {
public:
	OctTree(glm::vec4, glm::vec4);
	OctNode * addVector(glm::vec4 *);
};

#endif
