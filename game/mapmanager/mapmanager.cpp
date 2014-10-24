#include "mapmanager.h"

void MapManager::ShiftLeft() {
	for( int i=0; i<4; i++ )
		delete Buffer[0][i];
	for( int i=0; i<3; i++ ) {
		for( int j=0; j<4; j++ )
			Buffer[i][j] = Buffer[i+1][j];
	}
	for( int i=0; i<4; i++ ) {
		Buffer[3][i] = new MapTile( Buffer[2][i]->Right() );
}

void MapManager::ShiftRight() {
	for( int i=0; i<4; i++ )
		delete Buffer[3][i];
	for( int i=3; i>0; i-- ) {
		for( int j=0; j<4; j++ )
			Buffer[i][j] = Buffer[i-1][j];
	}
}

void MapManager::ShiftUp() {
	for( int i=0; i<4; i++ )
		delete Buffer[i][0];
	for( int i=0; i<4; i++ ) {
		for( int j=0; j<3; j++ )
			Buffer[i][j] = Buffer[i][j+1];
	}
}

void MapManager::ShiftDown() {
	for( int i=0; i<4; i++ )
		delete Buffer[i][3];
	for( int i=0; i<4; i++ ) {
		for( int j=3; j>0; j-- )
			Buffer[i][j] = Buffer[i][j-1];
	}
}


