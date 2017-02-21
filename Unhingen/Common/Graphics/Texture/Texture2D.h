#pragma once

#include "..\Common\Types.h"
#include <GL\glew.h>
#include <string>

class tuTex2D {
	public:
		tuTex2D ( const std::string& fileName );
		void Bind ();
		void Unbind ();
		inline u_int GetWidth () { return width; }
		inline u_int GetHeight () { return height; }
		virtual ~tuTex2D ();
	private:
		GLuint	textureHandle;
		u_int	width;
		u_int	height;
};