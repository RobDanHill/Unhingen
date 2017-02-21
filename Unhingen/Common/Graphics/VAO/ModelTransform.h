#pragma once

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

class tuModelTransform {
	public:
		tuModelTransform () {
			this->position = glm::vec3();
			this->rotation = glm::vec3();
			this->scale = glm::vec3( 1.0f, 1.0f, 1.0f );
		}

		tuModelTransform ( const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale ) {
			this->position = position;
			this->rotation = rotation;
			this->scale = scale;
		}

		inline glm::mat4 GetTransformedModel () {
			glm::mat4 rotationMatrix =
				glm::rotate( rotation.z, glm::vec3( 0, 0, 1 ) ) *
				glm::rotate( rotation.y, glm::vec3( 0, 1, 0 ) ) *
				glm::rotate( rotation.x, glm::vec3( 1, 0, 0 ) );

			return glm::translate( position ) * rotationMatrix * glm::scale( scale );
		}

		inline glm::vec3 GetPosition () { return position; }
		inline glm::vec3 GetRotation () { return rotation; }
		inline glm::vec3 GetScale ()	{ return scale; }

		inline void SetPosition ( const glm::vec3& position )	{ this->position = position; }
		inline void SetRotation ( const glm::vec3& rotation )	{ this->rotation = rotation; } 
		inline void SetScale ( const glm::vec3& scale )			{ this->scale = scale; }
	private:
		glm::vec3	position;
		glm::vec3	rotation;
		glm::vec3	scale;
};