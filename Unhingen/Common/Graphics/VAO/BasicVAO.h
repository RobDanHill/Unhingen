#pragma once

#include "VAO.h"
#include "..\Common\Graphics\Vertex\Vertex.h"

class tuBasicVAO : public tuVAO_a {
	public:
		tuBasicVAO ( tuVertex *vertices, u_int numVertices );
		void Draw () const override;
		void Render () const override;
		virtual ~tuBasicVAO ();
	private:
		enum { POSITION_BUF, NUM_BUF };
		std::vector<tuVertex> vertices;
};