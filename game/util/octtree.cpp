#include "octtree.h"

bool vecBound( glm::vec4 LL, glm::vec4 UR, glm::vec4 v) {
	int pos = 0;
	for( int i=0; i<3; i++ ) {
		pos += (LL[i] > v[i]);
		pos <<= 1;
	}
	pos >>= 1;
	return pos;
}

int vecAdj( glm::vec4 LL, glm::vec4 UR, glm::vec4 v ) {
	int adj = 0;
	for( int i=0; i<3; i++ ) {
//		std::cout << adj << " ";
		adj += ((LL[i] <= v[i]) && (UR[i] >= v[i]));
		adj <<= 1;
	}
	adj >>= 1;
//	std::cout << adj << std::endl;
	return adj;
}

Leaf::Leaf(Branch * p, glm::vec4 * v_in) { 
	parent = p;
	v = v_in;
	LL = p->LL;
	UR = p->UR;
}

void Leaf::addLeaf(Leaf * l) {
	parent->Nodes[pos] = new Branch(parent, this);
}

//Finds lowest level Branch with bounding box that contains Leaf
void Leaf::update() {
	Branch * p = parent;
	while( vecAdj(p->LL, p->UR, *v) != 7 && p->parent != NULL ) {
		p->ncount--;
		p = p->parent;
	}
	p->ncount--;	//Will be reincremented when node is added.

	LL=p->LL;
	UR=p->UR;
	parent->Nodes[pos] = new Empty(parent,pos);
	p->addLeaf(this);
}

//Copy Constructor for Branch
Branch::Branch(Branch * b) {
	parent = b->parent;
	LL = b->LL;
	UR = b->UR;
	pos = b->pos;
	ncount = b->ncount;
	for( int i=0; i<8; i++ )
		Nodes[i] = b->Nodes[i];
}

//Creates Branch from Leaf and adds Leaf to it
Branch::Branch(Branch * p, Leaf * l) {
	parent = p;
	LL = l->LL;
	UR = l->UR;
	pos = l->pos;
	ncount = 0;
	for( int i=0; i<8; i++ )
		Nodes[i] = new Empty(this,i);
	addLeaf(l);
}

Branch::~Branch() {
	if( parent )
		parent->Nodes[pos] = new Empty(this,pos);
	for( int i=0; i<8; i++ ) {
		Nodes[i]->parent = NULL;
		delete Nodes[i];
	}
}

//Adds Leaf.  Recurses down a Branch line
//Creates a Branch when reaching a Leaf, or replacing an Empty
void Branch::addLeaf(Leaf * l) {
//	std::cout << "Branch addLeaf" << std::endl;
	ncount += 1;

	glm::vec4 mid = (UR-LL)/2.0f;

	bool cond;
	l->pos = 0;
	for( int i=0; i<3; i++ ) {
		cond = ( (*(l->v) - LL)[i] > mid[i] );

		l->pos += 1*cond;
		l->LL[i] = LL[i] + mid[i]*cond;

		l->pos <<= 1;
	}
	l->pos >>= 1;
	l->UR = l->LL + mid;
//	std::cerr << l->pos << std::endl;
//	std::cerr << Nodes[l->pos]->LL[0] << std::endl;
	Nodes[l->pos]->addLeaf(l);
}

Empty::Empty(Branch * p, int pos_in) : Leaf(p, NULL) { pos = pos_in; } //, LL(LL_in), UR(UR_in) { }

//Replaces Empty with added Leaf
void Empty::addLeaf(Leaf * l) {
	parent->Nodes[pos] = l;
//	std::cout << "Empty::addLeaf" << std::endl;
	delete this;
}

Root::Root(glm::vec4 LL_in, glm::vec4 UR_in) {
//	std::cerr << "Root Constructor" << std::endl;
	parent = NULL;
	LL = LL_in;
	UR = UR_in;
	pos = RUF;
	for( int i=0; i<8; i++ )
		Nodes[i] = new Empty(this,i);
}

void Root::addLeaf(Leaf * l) {
//Adds Leaf to current Bounding Box.
	int adj = vecAdj(LL, UR, *(l->v));
//	std::cerr << adj << std::endl;
	if( adj == 7 ) {
//		std::cout << "if statement" << std::endl;
		Branch::addLeaf(l);
		return;
	}
//Finds Root's relative position to leaf's
	int dpos = vecBound(LL, UR, *(l->v));
	int amask = 7 ^ adj;
	dpos &= amask;
	dpos |= adj;

//Sets Root's variables to create replacement branch for extension.
	parent = this;
	pos = dpos;
	Nodes[pos] = new Branch(this);
	for( int i=0; i<pos; i++ )
		Nodes[i] = new Empty(this,i);
	for( int i=pos+1; i<8; i++ )
		Nodes[i] = new Empty(this,i);

//Expands Root's bounding box.
	glm::vec4 size = UR-LL;
	for( int i=0; i<3; i++ )
		if( (pos>>i)%2 )
			LL[i] -= size[i];
		else
			UR[i] += size[i];

//Recurses for Root extension
	addLeaf(l);
}

OctTree::OctTree(glm::vec4 LL_in, glm::vec4 UR_in) : Root(LL_in, UR_in) { 
//	std::cerr << "OctTree Constructor" << std::endl;
}

OctNode * OctTree::addVector(glm::vec4 * v) {
	Leaf * l = new Leaf(this, v);
	addLeaf(l);
	return l;
}


