#pragma once

#include "..\Common\Types.h"
#include "..\Common\Graphics\Vertex\Vertex.h"
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <vector>

class VAO {
	public:
		virtual void Draw () = 0;
	protected:
		GLuint				vao;
		GLuint				*vbo;
		std::vector<u_int>	indices;
		u_int				drawCount;
};