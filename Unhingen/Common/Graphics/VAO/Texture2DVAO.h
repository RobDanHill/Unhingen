#pragma once

#include "VAO.h"
#include "..\Common\Graphics\Vertex\Texture2DVertex.h"
#include <vector>

class Texture2DVAO : public VAO {
	public:
		Texture2DVAO ( const std::vector<Texture2DVertex>& vertices );
		Texture2DVAO ( Texture2DVertex *vertices, u_int numVertices );
		Texture2DVAO ( const std::vector<Texture2DVertex>& vertices, const std::vector<u_int>& indices );
		void Draw();
		virtual ~Texture2DVAO ();
	private:
		enum { POSITION_BUF, TEXCOORD_BUF, NUM_BUF };
		//GLuint	vao;
		//GLuint	vbo[NUM_BUF];
		std::vector<Texture2DVertex> vertices;
};