#include "Player.h"



Player::Player ( const glm::vec2& tile, u_short tileWidth, u_short tileHeight ) {
	this->tile = tile;
	map.x = tileWidth*tile.x + tileWidth/2;
	map.y = tileHeight*tile.y + tileHeight/2;
	/* Calculate screen coordinates here... */
}


Player::~Player () {
}
