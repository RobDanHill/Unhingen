#pragma once

#include <GL\glew.h>
#include <string>

class Shader {
	public:
		Shader ( const std::string& fileName );
		Shader ( const std::string& vertex, const std::string& fragment );
		void Enable ();
		virtual ~Shader ();
	private:
		GLuint		program;
		GLuint		vertexShader, fragmentShader;
};