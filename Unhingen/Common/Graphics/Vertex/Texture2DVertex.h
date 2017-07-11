#pragma once

#include "Vertex.h"

class tuTex2DVertex : public tuVertex {
	public:
		tuTex2DVertex ( const glm::vec3& position, const glm::vec2& texCoord )
			: tuVertex( position ) {
			this->texCoord = texCoord;
		}
		inline glm::vec2 GetTexCoord () const { return texCoord; }
	private:
		glm::vec2 texCoord;
};