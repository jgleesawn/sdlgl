#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include "maptile.h"

class MapManager() {
	MapTile * Buffer[4][4];
	void loadSurrounding();
public:
	void ShiftLeft();
	void ShiftRight();
	void ShiftUp();
	void ShiftDown();
};

#endif
