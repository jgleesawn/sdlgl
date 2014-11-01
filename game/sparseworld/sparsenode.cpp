#include "sparsenode.h"

SparseNode::SparseNode(vec4<float> pos) {
	position = pos;
	for( int i=0; i<6; i++ )
		surrounding[i] = 0;
//	for( int i=0; i<6; i++ )
//		printf("%p is surrounding %i\n",surrounding[i], i);
}
Face::Face(vec4<float> pos) : SparseNode(pos) {}

bool SparseNode::updateD(Dim d) {
	if( surrounding[P+2*d] ) {
	if( get(d) > surrounding[P + 2*d]->get(d) ) {
//		printf("%f > %f\n",get(d), surrounding[P+2*d]->get(d));
		surrounding[P + 2*d]->surrounding[N + 2*d] = surrounding[N + 2*d];
		surrounding[N + 2*d]->surrounding[P + 2*d] = surrounding[P + 2*d];
		surrounding[N + 2*d] = surrounding[P + 2*d];
		surrounding[P + 2*d] = surrounding[N + 2*d]->surrounding[P + 2*d];
		surrounding[N + 2*d]->surrounding[P + 2*d] = this;
		return true;
	} }
	if( surrounding[N+2*d] ) {
	if( get(d) < surrounding[N + 2*d]->get(d) ) {
//		printf("%f < %f\n",get(d), surrounding[P+2*d]->get(d));
		surrounding[N + 2*d]->surrounding[P + 2*d] = surrounding[P + 2*d];
		surrounding[P + 2*d]->surrounding[N + 2*d] = surrounding[N + 2*d];
		surrounding[P + 2*d] = surrounding[N + 2*d];
		surrounding[N + 2*d] = surrounding[P + 2*d]->surrounding[N + 2*d];
		surrounding[P + 2*d]->surrounding[N + 2*d] = this;
		return true;
	} }
	return false;
}
void SparseNode::add(SparseNode * newNode) {
	for( int i=0; i<3; i++ ) {
//		float L,R;
//		L = R = 0;
//		if( surrounding[2*i + N] )
//			L = surrounding[2*i + N]->get((Dim)i);
//		if( surrounding[2*i + P] )
//			R = surrounding[2*i + P]->get((Dim)i);

//		printf("N: %f, P: %f\n",L,R);
//		printf("Current: %f, New: %f\n",get((Dim)i),newNode->get((Dim)i));
		if( newNode->get((Dim)i) < get((Dim)i) ) {
			if( surrounding[2*i + N] )
				surrounding[2*i + N]->surrounding[2*i + P] = newNode;
			newNode->surrounding[2*i + N] = surrounding[2*i + N];
			surrounding[2*i + N] = newNode;
			newNode->surrounding[2*i + P] = this;
		} else if( newNode->get((Dim)i) > get((Dim)i) ) {
			if( surrounding[2*i + P] )
				surrounding[2*i + P]->surrounding[2*i + N] = newNode;
			newNode->surrounding[2*i + P] = surrounding[2*i + P];
			surrounding[2*i + P] = newNode;
			newNode->surrounding[2*i + N] = this;
		} else {
//			newNode->surrounding[2*i + N] = this;
//			newNode->surrounding[2*i + P] = surrounding[2*i + P];
//			surrounding[2*i + P] = newNode;
		}
//		L = R = 0;
//		if( surrounding[2*i + N] )
//			L = surrounding[2*i + N]->get((Dim)i);
//		if( surrounding[2*i + P] )
//			R = surrounding[2*i + P]->get((Dim)i);

//		printf("N: %f, P: %f\n",L,R);
//		printf("Current: %f, New: %f\n",get((Dim)i),newNode->get((Dim)i));
//		printf("\n");
	}
//	printf("\n");
}

void SparseNode::rem() {
	for( int i=0; i<3; i++ ) {
//		printf("%p\n%p\n",surrounding[2*i+P],surrounding[2*i+N]);
//		if( surrounding[2*i + P] )
		surrounding[2*i + P]->surrounding[2*i + N] = surrounding[2*i + N];
//		if( surrounding[2*i + N] )
		surrounding[2*i + N]->surrounding[2*i + P] = surrounding[2*i + P];
	}
}

void Face::rem() {
	for( int i=0; i<3; i++ ) {
		if( surrounding[2*i + P] )
			surrounding[2*i + P]->surrounding[2*i + N] = surrounding[2*i + N];
		if( surrounding[2*i + N] )
			surrounding[2*i + N]->surrounding[2*i + P] = surrounding[2*i + P];
	}
}

void SparseNode::update() {
	for( int i=0; i<3; i++ )
		while( updateD((Dim)i) );
}

float SparseNode::get(Dim d) {
	return position.data[d];
}

void SparseNode::show() {
	for( int i=0; i<4; i++ )
		printf("%f ",position.data[i]);
	printf("\n");
}
int SparseNode::testIsSurrounded() {
	int count = 0;
	for( int i=0; i<6; i++ ) {
//		printf("%p is surrounding %i\n",surrounding[i], i);
		if( surrounding[i] != 0 )
			count++;
	}
	return count;
}


