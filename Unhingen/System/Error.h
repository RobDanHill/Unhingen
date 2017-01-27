#pragma once

#include <SDL2\SDL.h>
#include <GL\glew.h>
#include <string>
#include <iostream>

namespace err {

	static void SDL_ErrMsg ( const std::string& msg ) {
		std::cerr << msg << "\tSDL Error: " << SDL_GetError() << std::endl;
	}

	static void GLEW_ErrMsg ( const std::string& msg, const GLenum& error ) {
		std::cerr << msg << "\tGLEW Error: " << glewGetErrorString( error ) << std::endl;
	}

	static void ErrMsg ( const std::string& msg ) {
		std::cerr << msg << std::endl;
	}

}