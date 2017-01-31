#pragma once

#include "..\Common\Types.h"
#include <GL\glew.h>
#include <string>

class Texture2D {
	public:
		Texture2D ( const std::string& fileName );
		void Bind ( u_int unit );
		inline u_int GetWidth () { return width; }
		inline u_int GetHeight () { return height; }
		virtual ~Texture2D ();
	private:
		GLuint	textureHandle;
		u_int	width;
		u_int	height;
};