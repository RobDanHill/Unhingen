#pragma once

#include "Common\Types.h"

/* 16:9 aspect ratio */
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

class Map {
	private:
		/* The tileWidth and tileHeight should be 
		 * calculated to be 80 given the current window width and height 
		 */
		u_short	tileWidth, tileHeight;
		u_byte	width, height;
		u_int	*map;

	public:
		Map ( u_byte width, u_byte height, u_int *map );
		~Map ();

		const u_byte MAX_X_TILES_ACROSS = 16;
		const u_byte MAX_Y_TILES_ACROSS = 9;

		inline u_int GetTile ( u_int x, u_int y ) { return map[y*width+x]; }

		inline u_byte GetWidth () { return width; }
		inline u_byte GetHeight () { return height; }

		inline u_short GetTileWidth () { return tileWidth; }
		inline u_short GetTileHeight () { return tileHeight; }
};