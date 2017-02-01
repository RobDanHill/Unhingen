#pragma once

#include "VAO.h"
#include "..\Common\Graphics\Vertex\Vertex.h"

class BasicVAO : public VAO {
	public:
		BasicVAO ( Vertex *vertices, u_int numVertices );
		void Draw () override;
		virtual ~BasicVAO ();
	private:
		enum { POSITION_BUF, NUM_BUF };
		std::vector<Vertex> vertices;
};