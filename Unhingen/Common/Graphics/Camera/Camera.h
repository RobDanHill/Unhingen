#pragma once

#include <glm\glm.hpp>

class tuCamera_a {
	public:
		tuCamera_a ( const glm::vec3& position, const glm::vec3& up, const glm::vec3& forward ) {
			this->position = position;
			this->up = up;
			this->forward = forward;
		}
		virtual glm::mat4 GetProjection () const = 0;
		inline glm::vec3 GetPosition () const { return position; }
		inline glm::vec3 GetUpDirection () const { return up; }
		inline glm::vec3 GetForwardDirection () const { return forward; }
	protected:
		glm::vec3	position;
		glm::vec3	up;
		glm::vec3	forward;
};