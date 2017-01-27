#include "Shader.h"

#include "..\System\Error.h"
#include "..\Utils\ShaderUtils.h"
#include "..\Utils\IO.h"

Shader::Shader ( const std::string& fileName ) {
	program = glCreateProgram();
	if ( program == 0 ) {
		err::GLEW_ErrMsg( "An error occurred while creating the program object!", glGetError() );
	}
	vertexShader = utils::CreateShaderProgram( utils::LoadFile( fileName + ".vs" ), GL_VERTEX_SHADER );
	fragmentShader = utils::CreateShaderProgram( utils::LoadFile( fileName + ".fs" ), GL_FRAGMENT_SHADER );
	/* Attach the shaders to the current program */
	glAttachShader( program, vertexShader );
	glAttachShader( program, fragmentShader );
	glBindAttribLocation( program, 0, "position" );
	/* Going to need to bind the attrib locations of the texCoords and normals too */
	glLinkProgram( program );
	utils::ShaderError( program, GL_LINK_STATUS, true, "Program failed linking!" );
	glValidateProgram( program );
	utils::ShaderError( program, GL_VALIDATE_STATUS, true, "Program is invalid!" );
	/* Going to need to get the uniform location for transform at some point */
}

Shader::Shader ( const std::string& vertFileName, const std::string& fragFileName ) {
	program = glCreateProgram();
	if ( program == 0 ) {
		err::GLEW_ErrMsg( "An error occurred while creating the program object!", glGetError() );
	}
	vertexShader = utils::CreateShaderProgram( utils::LoadFile( vertFileName ), GL_VERTEX_SHADER );
	fragmentShader = utils::CreateShaderProgram( utils::LoadFile( fragFileName ), GL_FRAGMENT_SHADER );
	/* Attach the shaders to the current program */
	glAttachShader( program, vertexShader );
	glAttachShader( program, fragmentShader );
	glBindAttribLocation( program, 0, "position" );
	/* Going to need to bind the attrib locations of the texCoords and normals too */
	glLinkProgram( program );
	utils::ShaderError( program, GL_LINK_STATUS, true, "Program failed linking!" );
	glValidateProgram( program );
	utils::ShaderError( program, GL_VALIDATE_STATUS, true, "Program is invalid!" );
	/* Going to need to get the uniform location for transform at some point */
}

void Shader::Enable () {
	glUseProgram( program );
}

Shader::~Shader () {
	glDetachShader( program, vertexShader );
	glDeleteShader( vertexShader );
	glDetachShader( program, fragmentShader );
	glDeleteShader( fragmentShader );
	glDeleteProgram( program );
}