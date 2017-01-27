#include "Common\Types.h"

#include <SDL2\SDL.h>
#include <string>

#include "Display\Display.h"
#include "Utils\IO.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main ( int argc, char *argv[] ) {
	std::string fileContents = utils::LoadFile( "./Res/Hello.txt" );
	Display win( WINDOW_WIDTH, WINDOW_HEIGHT, "Test Window" );
	while ( win.IsRunning() ) {
		win.Clear( 0.0f, 0.0f, 0.0f, 1.0f );	// Clear the window with red
		win.Update();
		for ( SDL_Event e; SDL_PollEvent( &e ); ) {
			switch ( e.type ) {
				case SDL_QUIT: win.SetRunning( false );
				case SDL_KEYUP:
					switch ( e.key.keysym.sym ) {
						case SDLK_ESCAPE: win.SetRunning( false );
					}
			}
		}
	}
	return 0;
}