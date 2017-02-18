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
#include "Utils\IO.h"

#define WINDOW_WIDTH 1280//800
#define WINDOW_HEIGHT 720//600

int main ( int argc, char *argv[] ) {
	Display win( WINDOW_WIDTH, WINDOW_HEIGHT, "Test Window" );
	Shader texShader( "./Res/Shaders/Texture" );
	Shader colorShader( "./Res/Shaders/Test" );

	Texture2DVertex vertices[] = {
		Texture2DVertex( glm::vec3( -0.5f, -0.5f, 0.0f ), glm::vec2( 0.15f, 1.0f ) ),
		Texture2DVertex( glm::vec3( 0.0f, 0.5f, 0.0f ), glm::vec2( 0.5f, 0.0f ) ),
		Texture2DVertex( glm::vec3( 0.5f, -0.5f, 0.0f ), glm::vec2( 0.85f, 1.0f ) )
	};

	u_int indices[] = { 0, 1, 2 };

	std::vector<Texture2DVertex> v = utils::ToExplicitVector( vertices, sizeof( vertices ) / sizeof( vertices[0] ) );
	std::vector<u_int> i = utils::ToExplicitVector( indices, sizeof( indices ) / sizeof( indices[0] ) );
	Texture2DVAO vao( v, i );

	Texture2D texture( "./Res/Images/DukeNukem3D.png" );

	OrthographicCamera orthocam( glm::vec3( 0.0f, 0.0f, 0.0f ), 0.0f, ( float ) WINDOW_WIDTH, ( float ) WINDOW_HEIGHT, 0.0f, -1.0f, 1.0f );
	PerspectiveCamera perspcam( glm::vec3( 0.0f, 0.0f, 1.0f ), 70.0f, ( float ) WINDOW_WIDTH / ( float ) WINDOW_HEIGHT, 0.01f, 1000.0f );

	float counter = 0.0f;

	//win.SetClearColor( 0xff000000 );

	while ( win.IsRunning() ) {
		//win.Clear( 0.0f, 0.15f, 0.3f, 1.0f );	// Clear the window with light-blue
		win.Clear();

		texShader.Bind();
		texture.Bind();

		/* Modify model transform values here */
		vao.GetTransform().SetPosition( glm::vec3( WINDOW_WIDTH/2 + sinf( counter ), WINDOW_HEIGHT/2 + vao.GetTransform().GetPosition().y, vao.GetTransform().GetPosition().z ) );
		vao.GetTransform().SetRotation( glm::vec3( counter, counter, vao.GetTransform().GetRotation().z ) );
		//vao.GetTransform().SetScale( glm::vec3( 100.0f, 100.0f, vao.GetTransform().GetScale().z ) );
		texShader.Update( vao.GetTransform().GetTransformedModel(), orthocam.GetProjection() );

		vao.Render();
		texture.Unbind();
		texShader.Unbind();

		win.Update();

		for ( SDL_Event e; SDL_PollEvent( &e ); ) {
			switch ( e.type ) {
				case SDL_QUIT: win.Close(); break;
				case SDL_KEYUP:
					switch ( e.key.keysym.sym ) {
						case SDLK_ESCAPE: win.Close(); break;
					}
					break;
			}
		}

		counter += 0.01f;
	}

	return 0;
}