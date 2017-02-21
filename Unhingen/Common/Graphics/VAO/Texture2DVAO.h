#pragma once

#include "VAO.h"
#include "..\Common\Graphics\Vertex\Texture2DVertex.h"
#include <vector>

class tuTex2DVAO : public tuVAO_a {
	public:
		tuTex2DVAO ( const std::vector<tuTex2DVertex>& vertices );
		tuTex2DVAO ( tuTex2DVertex *vertices, u_int numVertices );
		tuTex2DVAO ( const std::vector<tuTex2DVertex>& vertices, const std::vector<u_int>& indices );
		void Draw () const override;
		void Render () const override;
		virtual ~tuTex2DVAO ();
	private:
		enum { POSITION_BUF, TEXCOORD_BUF, INDEX_BUF, NUM_BUF };
		std::vector<tuTex2DVertex> vertices;
};