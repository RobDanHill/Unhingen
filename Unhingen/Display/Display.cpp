#include "Display.h"

#include "..\System\Error.h"
#include <GL\glew.h>

Display::Display ( const u_short width, const u_short height, const std::string& title ) {
	running = true;
	InitSDL();
	window = SDL_CreateWindow(
		title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_OPENGL
	);
	glContext = SDL_GL_CreateContext( window );
	if ( glContext == null ) {
		err::SDL_ErrMsg( "SDL could not create an OpenGL context for the associated window!" );
	}
	InitGLEW();
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );
}

/*
 * Initialize SDL and all buffer sizes
 */
void Display::InitSDL () {
	if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
		err::SDL_ErrMsg( "SDL failed to initialize!" );
		running = false;
	}
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_BUFFER_SIZE, 32 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
}

void Display::InitGLEW () {
	const GLenum result = glewInit();
	if ( result != GLEW_OK ) {
		err::GLEW_ErrMsg( "GLEW failed to initialize!", result );
		running = false;
	}
}

/*
 * Clears the screen with the specified color
 */
void Display::Clear ( float r, float g, float b, float a ) {
	glClearColor( r, g, b, a );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void Display::Update () {
	SDL_GL_SwapWindow( window );
}

Display::~Display () {
	SDL_GL_DeleteContext( glContext );
	SDL_DestroyWindow( window );
	SDL_Quit();
}