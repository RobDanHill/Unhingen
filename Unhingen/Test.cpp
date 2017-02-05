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
#include "Utils\IO.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main ( int argc, char *argv[] ) {
	Display win( WINDOW_WIDTH, WINDOW_HEIGHT, "Test Window" );
	Shader texShader( "./Res/Shaders/Texture" );
	Shader colorShader( "./Res/Shaders/Test" );

	Texture2DVertex vertices[] = {
		Texture2DVertex( glm::vec3( -0.5f, -0.5f, 0.0f ), glm::vec2( 0.15f, 1.0f ) ),
		Texture2DVertex( glm::vec3( 0.0f, 0.5f, 0.0f ), glm::vec2( 0.5f, 0.0f ) ),
		Texture2DVertex( glm::vec3( 0.5f, -0.5f, 0.0f ), glm::vec2( 0.85f, 1.0f ) )
	};

	/*Vertex verts[] = {
		Vertex( glm::vec3( -0.5f, -0.5f, 0.0f ) ),
		Vertex( glm::vec3( 0.0f, 0.5f, 0.0f ) ),
		Vertex( glm::vec3( 0.5f, -0.5f, 0.0f ) )
	};

	BasicVAO colorvao( verts, sizeof( verts ) / sizeof( verts[0] ) );*/

	u_int indices[] = { 0, 1, 2 };

	std::vector<Texture2DVertex> v = utils::ToExplicitVector( vertices, sizeof( vertices ) / sizeof( vertices[0] ) );
	std::vector<u_int> i = utils::ToExplicitVector( indices, sizeof( indices ) / sizeof( indices[0] ) );
	Texture2DVAO vao( v, i );

	Texture2D texture( "./Res/Images/DukeNukem3D.png" );

	while ( win.IsRunning() ) {
		//win.Clear( 0.0f, 0.15f, 0.3f, 1.0f );	// Clear the window with light-blue
		win.Clear( 0xff0000ff );

		texShader.Bind();
		texture.Bind();
		vao.Render();
		texture.Unbind();
		texShader.Unbind();

		win.Update();

		for ( SDL_Event e; SDL_PollEvent( &e ); ) {
			switch ( e.type ) {
				case SDL_QUIT: win.SetRunning( false ); break;
				case SDL_KEYUP:
					switch ( e.key.keysym.sym ) {
						case SDLK_ESCAPE: win.SetRunning( false );
					}
					break;
			}
		}
	}

	return 0;
}