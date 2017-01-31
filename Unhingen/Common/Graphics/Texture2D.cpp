#include "Texture2D.h"

#include <cassert>
#include <SDL2\SDL_image.h>
#include "..\System\Error.h"

Texture2D::Texture2D ( const std::string& fileName ) {
	SDL_Surface *image = IMG_Load( fileName.c_str() );
	if ( image == null ) {
		err::SDL_image_ErrMsg( "Error occurred loading \"" + fileName + "\"!" );
	}
	width = image->w; height = image->h;
	glGenTextures( 1, &textureHandle );
	glBindTexture( GL_TEXTURE_2D, textureHandle );

	/* Configure texture settings here */
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels );

	glBindTexture( GL_TEXTURE_2D, 0 );
	SDL_FreeSurface( image );
}

void Texture2D::Bind ( u_int unit ) {
	assert( unit >= 0 && unit <= 31 );
	glActiveTexture( GL_TEXTURE0 + unit );
	glBindTexture( GL_TEXTURE_2D, textureHandle );
}

Texture2D::~Texture2D () {
	glDeleteTextures( 1, &textureHandle );
}