#include "Display.h"

#include "..\System\Error.h"
#include <GL\glew.h>

tuDisplay::tuDisplay ( const u_short width, const u_short height, const std::string& title ) {
	running = true;
	this->width = width; this->height = height;
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
	glViewport( 0, 0, width, height );
	glEnable( GL_TEXTURE_2D );
	glEnable( GL_ALPHA_TEST );
	SetClearColor( 0x00000000 ); // Default clear color is black
}

/*
 * Initialize SDL, SDL_image, and all buffer sizes
 */
void tuDisplay::InitSDL () {
	if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
		err::SDL_ErrMsg( "SDL failed to initialize!" );
		running = false;
	}
	if ( IMG_Init( IMG_INIT_PNG ) < 0 ) {
		err::SDL_image_ErrMsg( "SDL_image failed to initialize!" );
	}
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_BUFFER_SIZE, 32 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
}

void tuDisplay::InitGLEW () {
	const GLenum result = glewInit();
	if ( result != GLEW_OK ) {
		err::GLEW_ErrMsg( "GLEW failed to initialize!", result );
		running = false;
	}
}

/*
 * Clears the screen with the specified color
 */
void tuDisplay::SetClearColor ( float r, float g, float b, float a ) {
	glClearColor( r, g, b, a );
}

void tuDisplay::SetClearColor ( u_int color ) {
	float r, g, b, a;
	r = ( float ) ( ( color >> 24 ) & 0xff );
	g = ( float ) ( ( color >> 16 ) & 0x00ff );
	b = ( float ) ( ( color >> 8 ) & 0x0000ff );
	a = ( float ) ( ( color >> 0 ) & 0x000000ff );
	glClearColor( r / 0xff, g / 0xff, b / 0xff, a / 0xff );
}

void tuDisplay::Clear() {
	glClear( GL_COLOR_BUFFER_BIT );
}

void tuDisplay::Update () {
	SDL_GL_SwapWindow( window );
}

tuDisplay::~tuDisplay () {
	SDL_GL_DeleteContext( glContext );
	SDL_DestroyWindow( window );
	IMG_Quit();
	SDL_Quit();
}