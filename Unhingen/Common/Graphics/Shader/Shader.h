#pragma once

#include "..\Common\Graphics\VAO\ModelTransform.h"
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <string>

class tuShader {
	public:
		tuShader ( const std::string& fileName );
		tuShader ( const std::string& vertFileName, const std::string& fragFileName );
		void Bind ();
		void Unbind ();
		GLint GetUniform ( const std::string& varName );
		void SetUniform3f ( const std::string& varName, const glm::vec3& data );
		void SetUniform3f ( const std::string& varName, float x, float y, float z );
		void SetUniformMat4f ( const std::string& varName, const glm::mat4& data );
		void Update ( const glm::mat4& transform, const glm::mat4& projection );
		void Update ( const glm::mat4& transform );
		virtual ~tuShader ();
	private:
		GLuint		program;
		GLuint		vertexShader, fragmentShader;
};