#pragma once

#include <glm\glm.hpp>

class tuVertex {
	public:
		tuVertex ( const glm::vec3& position ) {
			this->position = position;
		}
		inline glm::vec3 GetPosition () const { return position; }
	protected:
		glm::vec3	position;
};