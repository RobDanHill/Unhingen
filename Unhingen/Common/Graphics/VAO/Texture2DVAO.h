#pragma once

#include "VAO.h"
#include "..\Common\Graphics\Vertex\Texture2DVertex.h"
#include <vector>

class Texture2DVAO : public VAO {
	public:
		Texture2DVAO ( const std::vector<Texture2DVertex>& vertices );
		Texture2DVAO ( Texture2DVertex *vertices, u_int numVertices );
		Texture2DVAO ( const std::vector<Texture2DVertex>& vertices, const std::vector<u_int>& indices );
		void Draw () const override;
		void Render () const override;
		virtual ~Texture2DVAO ();
	private:
		enum { POSITION_BUF, TEXCOORD_BUF, INDEX_BUF, NUM_BUF };
		std::vector<Texture2DVertex> vertices;
};