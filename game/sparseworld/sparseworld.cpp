#include "sparseworld.h"


void SparseWorld::addVertex(vec4<float> pos) {
	int ind;
	if( removed_vertex_ind.size() ) {
		ind = removed_vertex_ind.back();
		removed_vertex_ind.pop_back();
		vbo.at(ind) = pos;
		for( int i=0; i<3; i++ )
			ibo[i].push_back(ind);
	} else {
		vbo.push_back(pos);
		for( int i=0; i<3; i++ )
			ibo[i].push_back(ibo[i].size());
	}
}

void SparseWorld::remVertex(int ind) {
	for( int i=0; i<3; i++ )
		ibo[i].erase(std::search(ibo[i].begin(), ibo[i].end(), &ind, &ind+1))
	removed_vertex_ind.push_back(ind);
}

void SparseWorld::sort_indices(Dim d) {
	for( int i=0; i<ibo[d].size(); i++ ) {
		for( int j=i+1; j<ibo[d].size(); j++ ) {
			if( vbo[ibo[d][i]].data[d] > vbo[ibo[d][j]].data[d] )
				std::swap(ibo[d][i], ibo[d][j]);
		}
	}
}

void SparseWorld::sort() {
	for( int i=0; i<3; i++ )
		sort_indices((Dim)i);
}


