#include "sparseworld.h"


void SparseWorld::addVertex(Object * obj) {
	for( int i=0; i<3; i++ )
		sortedObj[i].push_back(obj);
}

void SparseWorld::remVertex(Object * obj) {
	for( int i=0; i<3; i++ )
		sortedObj[i].erase(std::search(sortedObj[i].begin(), sortedObj[i].end(), &obj, &obj+1));
}

void SparseWorld::sort_indices(Dim d) {
	for( int i=0; i<sortedObj[d].size(); i++ ) {
		for( int j=i+1; j<sortedObj[d].size(); j++ ) {
			if( sortedObj[d][i]->position[d] > sortedObj[d][j]->position[d] )
				std::swap(sortedObj[d][i], sortedObj[d][j]);
		}
	}
}

void SparseWorld::sort() {
	for( int i=0; i<3; i++ )
		sort_indices((Dim)i);
}


