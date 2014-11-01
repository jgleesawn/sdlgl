#include "sparseworld.h"

//Corresponds with order N,P
SparseWorld::SparseWorld() {
	vec4<float> pos = {0, 0, 0, 0};
	float inf = 1.0/0.0;
	for( int i=0; i<6; i++ ) {
		for( int j=0; j<3; j++ )
			pos.data[j] = (((float)rand())/RAND_MAX);
		if( i%2 == N )
			pos.data[i/2] = inf * -1;
		if( i%2 == P )
			pos.data[i/2] = inf;
//		pos.data[i/2] = inf * ((i%2)*2 - 1);
		faces[i] = new Face(pos);
	}
	for( int i=0; i<6; i++ ) {
		for( int j=0; j<6; j++ ) {
			if( i != j )
				faces[i]->surrounding[j] = faces[j];
		}
	}
}

//Corners are at the back of the list.
//Must Pop front first to avoid SEGFAULT
SparseWorld::~SparseWorld() {
	while( All.size() ) {
		All.front()->rem();
		delete All.front();
		All.pop_front();
	}
	for( int i=0; i<6; i++ )
		delete faces[i];
}

void SparseWorld::update() {
	std::list<SparseNode *>::iterator it;
	for( it = All.begin(); it != All.end(); it++ )
		(*it)->update();
}

SparseNode * SparseWorld::addNode(vec4<float> pos) {
	All.push_front(new SparseNode(pos));
	faces[0]->add(All.front());
//	All.front()->update();
	return All.front();
}

SparseNode * SparseWorld::addNode(vec4<float> pos, SparseNode * neighbor) {
	All.push_front(new SparseNode(pos));
	neighbor->add(All.front());
	All.front()->update();
	return All.front();
}

void SparseWorld::test() {
	int count = 0;
	int conn = 0;
	for( int i=0; i<6; i++,count++ )
		if( faces[i]->testIsSurrounded() != 5 ) {
			conn = faces[i]->testIsSurrounded();
			fprintf(stderr, "%i is not a corner, has %i conns.\n", count, conn);
			faces[i]->show();
			for( int i=0; i<6; i++ )
				if( faces[i]->surrounding[i] )
				faces[i]->surrounding[i]->show();
		}
	count = 0;
	std::list<SparseNode *>::iterator its;
	for( its = All.begin(); its != All.end(); its++,count++ )
		if( (*its)->testIsSurrounded() != 6 ) {
			conn = (*its)->testIsSurrounded();
			fprintf(stderr, "%i is not fully surrounded, has %i conns.\n", count, conn);
			(*its)->show();
			for( int i=0; i<6; i++ )
				if( (*its)->surrounding[i] )
				(*its)->surrounding[i]->show();
		}
}


void SparseWorld_Test() {
	SparseWorld sw;
	sw.test();
	for( int i=0; i<1000; i++ ) {
		vec4<float> pos = {(float)rand()/RAND_MAX, (float)rand()/RAND_MAX, (float)rand()/RAND_MAX, 0};
		if( sw.addNode(pos)->testIsSurrounded() != 6 )
			printf("%i is not surrounded.\n",i);
		sw.update();
	}
	sw.test();
}
