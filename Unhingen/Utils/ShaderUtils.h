#pragma once

#include "..\Common\Types.h"
#include <GL\glew.h>
#include <string>
#include "..\System\Error.h"

namespace utils {

	/* Declare these here to avoid "identifier not found" errors */
	static void ShaderError ( GLuint shader, GLenum flag, boolean isProgram, const std::string& msg );
	static void CheckShaderCompilation( GLuint shader );

	static GLuint CreateShaderProgram ( const std::string& shaderSource, GLenum type ) {
		GLuint newShader = glCreateShader( type );
		if ( newShader == 0 ) {
			err::GLEW_ErrMsg( "An error occurred creating the shader object!", glGetError() );
		}
		const GLchar *sourceStrings[] = { shaderSource.c_str() };
		GLint sourceStringsLengths[] = { ( GLint ) shaderSource.length() };
		glShaderSource( newShader, 1, sourceStrings, sourceStringsLengths );
		glCompileShader( newShader );
		CheckShaderCompilation( newShader );
		return newShader;
	}

	static void CheckShaderCompilation ( GLuint shader ) {
		ShaderError( shader, GL_COMPILE_STATUS, false, "Shader compilation failed:" );
	}

	static void ShaderError ( GLuint shader, GLenum flag, boolean isProgram, const std::string& msg ) {
		GLint success = 0;
		GLchar errorString[1024] = { 0 };
		if ( isProgram ) glGetProgramiv( shader, flag, &success );
		else glGetShaderiv( shader, flag, &success );
		if ( success == GL_FALSE ) {
			if ( isProgram ) glGetProgramInfoLog( shader, sizeof( errorString ), null, errorString );
			else glGetShaderInfoLog( shader, sizeof( errorString ), null, errorString );
			err::GLEW_ErrMsg( msg + " '" + errorString + "'", glGetError() );
		}
	}

}