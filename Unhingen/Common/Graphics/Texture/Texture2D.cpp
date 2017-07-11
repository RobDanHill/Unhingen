#include "Texture2D.h"

#include <cassert>
#include <SDL2\SDL_image.h>
#include "..\System\Error.h"

tuTex2D::tuTex2D ( const std::string& fileName ) {
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

void tuTex2D::Bind () {
	/*assert( unit >= 0 && unit <= 31 );
	glActiveTexture( GL_TEXTURE0 + unit );*/
	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, textureHandle );
}

void tuTex2D::Unbind () {
	glBindTexture( GL_TEXTURE_2D, 0 );
}

tuTex2D::~tuTex2D () {
	glDeleteTextures( 1, &textureHandle );
}