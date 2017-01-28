#pragma once

#include <glm\glm.hpp>

class Vertex {
	public:
		Vertex ( const glm::vec3& position ) {
			this->position = position;
		}
		/*Vertex ( const glm::vec3& position, const glm::vec2& texCoord, const glm::vec3& normal ) {
			this->position = position;
			this->texCoord = texCoord;
			this->normal = normal;
		}*/
		inline glm::vec3 GetPosition () { return position; }
		/*inline glm::vec2 GetTexCoord () { return texCoord; }
		inline glm::vec3 GetNormal () { return normal; }*/
	private:
		glm::vec3	position;
		/*glm::vec2	texCoord;
		glm::vec3	normal;*/
};