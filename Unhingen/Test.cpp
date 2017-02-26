#include "Common\Types.h"

#include <SDL2\SDL.h>
#include <string>

#include "Display\Display.h"
#include "Common\Graphics\Mesh.h"
#include "Common\Graphics\VAO\BasicVAO.h"
#include "Common\Graphics\VAO\Texture2DVAO.h"
#include "Common\Graphics\Vertex\Texture2DVertex.h"
#include "Common\Graphics\Shader\Shader.h"
#include "Common\Graphics\Texture\Texture2D.h"
#include "Common\Graphics\Camera\OrthographicCamera.h"
#include "Common\Graphics\Camera\PerspectiveCamera.h"
#include "Map.h"
#include "Utils\IO.h"

/*
 * "Unhingen" is a TEAM UNHINGED project
 *
 * Team Unhinged is:
 * Cory Sabol & Daniel Hill
 *
 * Daniel Hill - Lead Engine Programmer
 * Cory Sabol  - Engine Programmer & Designer
 */

#define WINDOW_WIDTH 1280//800
#define WINDOW_HEIGHT 720//600

#define ASPECT ( float ) WINDOW_WIDTH / ( float ) WINDOW_HEIGHT

typedef struct Player_t {
	glm::vec2 map;
	glm::vec2 screen;
	glm::vec2 tile;
	glm::vec2 size;
} Player;

int main ( int argc, char *argv[] ) {
	u_int startTime = SDL_GetTicks();

	tuDisplay win( WINDOW_WIDTH, WINDOW_HEIGHT, "Test Window" );
	tuShader texShader( "./Res/Shaders/Texture" );
	tuShader colorShader( "./Res/Shaders/Test" );

	tuTex2DVertex vertices[] = {
		tuTex2DVertex( glm::vec3( -0.5f, -0.5f, 0.0f ), glm::vec2( 0.15f, 1.0f ) ),
		tuTex2DVertex( glm::vec3( 0.0f, 0.5f, 0.0f ), glm::vec2( 0.5f, 0.0f ) ),
		tuTex2DVertex( glm::vec3( 0.5f, -0.5f, 0.0f ), glm::vec2( 0.85f, 1.0f ) )
	};

	tuTex2DVertex orthoVertices[] = {
		tuTex2DVertex( glm::vec3( 0.0f, 1.0f, 0.0f ), glm::vec2( 0.15f, 1.0f ) ),
		tuTex2DVertex( glm::vec3( 0.5f, 0.0f, 0.0f ), glm::vec2( 0.5f, 0.0f ) ),
		tuTex2DVertex( glm::vec3( 1.0f, 1.0f, 0.0f ), glm::vec2( 0.85f, 1.0f ) )
	};

	tuTex2DVertex quad[] = {
		tuTex2DVertex( glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec2( 0.0f, 0.0f ) ),
		tuTex2DVertex( glm::vec3( 1.0f, 0.0f, 0.0f ), glm::vec2( 1.0f, 0.0f ) ),
		tuTex2DVertex( glm::vec3( 1.0f, 1.0f, 0.0f ), glm::vec2( 1.0f, 1.0f ) ),
		tuTex2DVertex( glm::vec3( 0.0f, 1.0f, 0.0f ), glm::vec2( 0.0f, 1.0f ) )
	};
	
	u_int quadIndices[] = { 3, 1, 0, 3, 2, 1 };

	u_int indices[] = { 0, 1, 2 };

	std::vector<tuTex2DVertex> v = utils::ToExplicitVector( quad, sizeof( quad ) / sizeof( quad[0] ) );
	std::vector<u_int> i = utils::ToExplicitVector( quadIndices, sizeof( quadIndices ) / sizeof( quadIndices[0] ) );
	tuTex2DVAO vao( v, i );

	tuTex2D texture( "./Res/Images/BasicBrickedTile.png" );
	tuTex2D texture2( "./Res/Images/DukeNukem3D.png" );
	tuTex2D playertex( "./Res/Images/alucardIdle1.png" );

	tuOrthographicCamera orthocam( glm::vec3( 0.0f, 0.0f, 0.0f ), 0.0f, ( float ) WINDOW_WIDTH, ( float ) WINDOW_HEIGHT, 0.0f, -1.0f, 1.0f );
	tuPerspectiveCamera perspcam( glm::vec3( 0.0f, 0.0f, 3.0f ), 70.0f, ASPECT, 0.01f, 1000.0f );

	// 24x24 map; This will be used to test horizontal and vertical scrolling...
	u_byte mapWidth = 24; u_byte mapHeight = 24;
	u_int world[] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	};

	Map map( mapWidth, mapHeight, world );

	float counter = 0.0f;

	/* Init player */
	Player player;
	player.tile.x = 5; player.tile.y = 7;
	player.size.x = map.GetTileWidth(); player.size.y = map.GetTileHeight();
	player.map.x = player.tile.x*map.GetTileWidth() + map.GetTileWidth() / 2;
	player.map.y = player.tile.y*map.GetTileHeight() + map.GetTileHeight() / 2;
	player.screen.x = player.map.x; player.screen.y = player.map.y;

	auto DrawShape = [&]( tuTex2D& texture, u_short x, u_short y, u_short width, u_short height, float angle ) -> void {
		texShader.Bind();
		texture.Bind();

		/* Modify model transform values here */
		vao.GetTransform().SetPosition( glm::vec3( x - 0.5f * width, y - 0.5f * height, vao.GetTransform().GetPosition().z ) );
		//vao.GetTransform().SetPosition( glm::vec3( x, y, vao.GetTransform().GetPosition().z ) );
		vao.GetTransform().SetRotation( glm::vec3( vao.GetTransform().GetRotation().x, vao.GetTransform().GetRotation().y, angle ) );
		vao.GetTransform().SetScale( glm::vec3( width, height, vao.GetTransform().GetScale().z ) );
		texShader.Update( vao.GetTransform().GetTransformedModel(), orthocam.GetProjection() );

		vao.Render();
		texture.Unbind();
		texShader.Unbind();
	};

	auto DrawMap = [&]( float angle ) -> void {
		/* Background drawing routine - Draw one quad that takes up the screen dimensions */
		DrawShape( texture2, win.GetWidth() / 2, win.GetHeight() / 2, win.GetWidth(), win.GetHeight(), 0.0f );

		/* Foreground drawing routine */
		for ( u_int y = 0; y < map.GetHeight(); y++ ) {
			for ( u_int x = 0; x < map.GetWidth(); x++ ) {
				u_short spx = map.GetTileWidth()/2 + map.GetTileWidth()*x;
				u_short spy = map.GetTileHeight()/2 + map.GetTileHeight()*y;
				if ( map.GetTile( x, y ) ) DrawShape( texture, spx, spy, map.GetTileWidth(), map.GetTileHeight(), angle );
			}
		}
	};

	u_int deltaTime, oldTime = deltaTime = 0;

	while ( win.IsRunning() ) {
		oldTime = startTime;
		startTime = SDL_GetTicks();

		player.tile.x = player.map.x / map.GetTileWidth();
		player.tile.y = player.map.y / map.GetTileHeight();
		//player.map.x = player.tile.x*map.GetTileWidth() + map.GetTileWidth() / 2;
		//player.map.y = player.tile.y*map.GetTileHeight() + map.GetTileHeight() / 2;
		player.screen.x = player.map.x; player.screen.y = player.map.y;

		win.Clear();

		//DrawShape( win.GetWidth() / 2 - cosf( counter ) * win.GetWidth() / 2, win.GetHeight() / 2 + sinf( counter ) * win.GetHeight() / 2, 500, 400, counter );
		//DrawShape( win.GetWidth() / 2 + sinf( counter ) * win.GetWidth() / 2, win.GetHeight() / 2, 80, 80, 0.0f );

		DrawMap( 0.0f );
		DrawShape( playertex, player.screen.x, player.screen.y, player.size.x, player.size.y, 0.0f );

		win.Update();

		for ( SDL_Event e; SDL_PollEvent( &e ); ) {
			switch ( e.type ) {
				case SDL_QUIT:	win.Close(); break;
				case SDL_KEYDOWN:
					switch ( e.key.keysym.sym ) {
						case SDLK_ESCAPE:	win.Close(); break;
						case SDLK_RIGHT:	player.map.x += ( float ) deltaTime / 1000.0f; break;
						case SDLK_LEFT:		player.map.x -= ( float ) deltaTime / 1000.0f; break;
					}
					break;
			}
		}

		counter += 0.01f;

		deltaTime = startTime - oldTime;
	}

	return 0;
}