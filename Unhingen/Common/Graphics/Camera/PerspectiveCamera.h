#pragma once

#include "Camera.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

class tuPerspectiveCamera : public tuCamera_a {
	public:
		tuPerspectiveCamera ( const glm::vec3& position, float fov, float aspect, float zNear, float zFar	) :
			tuCamera_a( position, glm::vec3( 0.0f, 1.0f, 0.0f ), glm::vec3( 0.0f, 0.0f, -1.0f ) ) {
			perspective = glm::perspective( fov, aspect, zNear, zFar );
		}
		inline glm::mat4 GetProjection () const override {
			return perspective * glm::lookAt( position, position + forward, up );
		}
	private:
		glm::mat4	perspective;
};