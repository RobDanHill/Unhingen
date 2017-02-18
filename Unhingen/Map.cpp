#include "Map.h"

Map::Map ( u_byte width, u_byte height, u_int *map ) {
	this->width = width; this->height = height;
	this->map = new u_int[width*height];
	for ( u_int y = 0; y < height; y++ ) {
		for ( u_int x = 0; x < width; x++ ) {
			this->map[y*width+x] = map[y*width+x];
		}
	}
	tileWidth = WINDOW_WIDTH/MAX_X_TILES_ACROSS;	// Tile width in pixels
	tileHeight = WINDOW_HEIGHT/MAX_Y_TILES_ACROSS;	// Tile height in pixels
}

Map::~Map () {
	delete[] map;
}