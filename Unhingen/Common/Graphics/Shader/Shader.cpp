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
	glBindAttribLocation( program, 1, "texCoord" );
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
	//glBindAttribLocation( program, 1, "texCoord" );
	/* Going to need to bind the attrib locations of the texCoords and normals too */
	glLinkProgram( program );
	utils::ShaderError( program, GL_LINK_STATUS, true, "Program failed linking!" );
	glValidateProgram( program );
	utils::ShaderError( program, GL_VALIDATE_STATUS, true, "Program is invalid!" );
	/* Going to need to get the uniform location for transform at some point */
}

GLint Shader::GetGLUniform ( const std::string& varName ) {
	return glGetUniformLocation( program, varName.c_str() );
}

void Shader::SetGLUniform3f ( const std::string& varName, const glm::vec3& data ) {
	glUniform3f( GetGLUniform( varName ), data.x, data.y, data.z );
}

void Shader::SetGLUniform3f ( const std::string& varName, float x, float y, float z ) {
	glUniform3f( GetGLUniform( varName ), x, y, z );
}

void Shader::Bind () {
	glUseProgram( program );
}
void Shader::Unbind () {
	glUseProgram( 0 );
}

Shader::~Shader () {
	glDetachShader( program, vertexShader );
	glDeleteShader( vertexShader );
	glDetachShader( program, fragmentShader );
	glDeleteShader( fragmentShader );
	glDeleteProgram( program );
}