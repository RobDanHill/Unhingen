#pragma once

#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <GL\glew.h>
#include <string>
#include <iostream>

namespace err {

	static void SDL_ErrMsg ( const std::string& msg ) {
		std::cerr << msg << " - SDL Error: " << SDL_GetError() << std::endl;
	}

	static void SDL_image_ErrMsg ( const std::string& msg ) {
		std::cerr << msg << " - SDL_image Error: " << IMG_GetError() << std::endl;
	}

	static void GLEW_ErrMsg ( const std::string& msg, const GLenum& error ) {
		std::cerr << msg << " - GLEW Error: " << glewGetErrorString( error ) << std::endl;
	}

	static void ErrMsg ( const std::string& msg ) {
		std::cerr << msg << std::endl;
	}

}