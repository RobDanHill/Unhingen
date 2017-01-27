#include <SDL2\SDL.h>

int main ( int argc, char *argv[] ) {
	SDL_Init( SDL_INIT_EVERYTHING );

	SDL_Window *window = SDL_CreateWindow(
		"Test",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		800,
		600,
		NULL
	);

	bool running = true;
	while ( running ) {
		for ( SDL_Event e; SDL_PollEvent( &e ); ) {
			switch ( e.type ) {
				case SDL_QUIT: running = false;
				case SDL_KEYUP:
					switch ( e.key.keysym.sym ) {
						case SDLK_ESCAPE: running = false;
					}
			}
		}
	}

	SDL_DestroyWindow( window );
	SDL_Quit();
	return 0;
}