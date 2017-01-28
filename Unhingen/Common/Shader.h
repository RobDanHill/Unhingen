#pragma once

#include <GL\glew.h>
#include <string>

class Shader {
	public:
		Shader ( const std::string& fileName );
		Shader ( const std::string& vertFileName, const std::string& fragFileName );
		void Enable ();
		virtual ~Shader ();
	private:
		GLuint		program;
		GLuint		vertexShader, fragmentShader;
};