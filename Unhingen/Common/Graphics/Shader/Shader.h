#pragma once

#include "..\Common\Graphics\VAO\ModelTransform.h"
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <string>

class Shader {
	public:
		Shader ( const std::string& fileName );
		Shader ( const std::string& vertFileName, const std::string& fragFileName );
		void Bind ();
		void Unbind ();
		GLint GetUniform ( const std::string& varName );
		void SetUniform3f ( const std::string& varName, const glm::vec3& data );
		void SetUniform3f ( const std::string& varName, float x, float y, float z );
		void SetUniformMat4f ( const std::string& varName, const glm::mat4& data );
		void Update ( const glm::mat4& transform, const glm::mat4& projection );
		void Update ( const glm::mat4& transform );
		virtual ~Shader ();
	private:
		GLuint		program;
		GLuint		vertexShader, fragmentShader;
};