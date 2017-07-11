#pragma once

#include "Common\Types.h"
#include <glm\glm.hpp>

class Player {
	private:
		/* 3 member fields for position tracking and drawing calculations */
		glm::vec2 screen;
		glm::vec2 map;
		glm::vec2 tile;

	public:
		Player ( const glm::vec2& tile, u_short tileWidth, u_short tileHeight );
		virtual ~Player ();
		inline glm::vec2& GetScreenCoordinates () { return screen; }
		inline glm::vec2& GetMapCoordinates ()	{ return map; }
		inline glm::vec2& GetTile ()	{ return tile; }
};