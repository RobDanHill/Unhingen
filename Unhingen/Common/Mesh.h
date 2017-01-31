#pragma once

#include "Types.h"
#include <GL\glew.h>
#include <vector>
#include "Vertex.h"

class Mesh {
	public:
		Mesh ( const std::vector<Vertex>& vertices );
		Mesh ( Vertex *vertices, u_int numVertices );
		void Draw ();
		virtual ~Mesh ();
	private:
		enum { POSITION, TEXCOORD, NUM_BUFFERS };
		GLuint	vao;
		GLuint	vbo[NUM_BUFFERS];
		u_int	drawCount;
};