#pragma once

#include "Vertex.h"

class Texture2DVertex : public Vertex {
	public:
		Texture2DVertex ( const glm::vec3& position, const glm::vec2& texCoord )
			: Vertex( position ) {
			this->texCoord = texCoord;
		}
		inline glm::vec2 GetTexCoord () { return texCoord; }
	private:
		glm::vec2 texCoord;
};