#pragma once

#include "Camera.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

class PerspectiveCamera : public Camera {
	public:
		PerspectiveCamera ( const glm::vec3& position, float fov, float aspect, float zNear, float zFar	) :
			Camera( position, glm::vec3( 0.0f, 1.0f, 0.0f ), glm::vec3( 0.0f, 0.0f, -1.0f ) ) {
			perspective = glm::perspective( fov, aspect, zNear, zFar );
		}
		inline glm::mat4 GetProjection () const override {
			return perspective * glm::lookAt( position, position + forward, up );
		}
	private:
		glm::mat4	perspective;
};