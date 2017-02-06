#pragma once

#include "Camera.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

class OrthographicCamera : public Camera {
	public:
		OrthographicCamera ( const glm::vec3& position, float left, float right, float bottom, float top, float zNear, float zFar ) :
			Camera( position, glm::vec3( 0.0f, 1.0f, 0.0f ), glm::vec3( 0.0f, 0.0f, -1.0f ) ) {
			orthographic = glm::ortho( left, right, bottom, top, zNear, zFar );
		}
		inline glm::mat4 GetProjection () const override {
			return orthographic * glm::lookAt( position, position + forward, up );
		}
	private:
		glm::mat4	orthographic;
};