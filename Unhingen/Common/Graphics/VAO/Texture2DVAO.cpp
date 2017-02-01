#include "Texture2DVAO.h"

#include "..\System\Out.h"
#include <stdio.h>

Texture2DVAO::Texture2DVAO ( const std::vector<Texture2DVertex>& vertices ) {
	drawCount = vertices.size();
	this->vertices = vertices;

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;
	for ( size_t i = 0; i < vertices.size(); i++ ) {
		positions.push_back( this->vertices[i].GetPosition() );
		texCoords.push_back( this->vertices[i].GetTexCoord() );
		printf( "Pos: %.1f %.1f %.1f\tTexCoord: %.1f %.1f\n", positions[i].x, positions[i].y, positions[i].z, texCoords[i].x, texCoords[i].y );
	}

	vbo = new GLuint[NUM_BUF];

	glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao ); //---------------------------------------------------

	glGenBuffers( NUM_BUF, vbo );

	/* Specify buffer data */
	glBindBuffer( GL_TEXTURE_2D, vbo[POSITION_BUF] );
	glBufferData( GL_TEXTURE_2D, positions.size() * sizeof( positions.front() ), &positions.front(), GL_STATIC_DRAW );

	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );

	glBindBuffer( GL_TEXTURE_2D, vbo[TEXCOORD_BUF] );
	glBufferData( GL_TEXTURE_2D, texCoords.size() * sizeof( texCoords.front() ), &texCoords.front(), GL_STATIC_DRAW );

	glEnableVertexAttribArray( 1 );
	glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, 0 );

	glBindVertexArray( 0 ); //-----------------------------------------------------
}

Texture2DVAO::Texture2DVAO ( Texture2DVertex *vertices, u_int numVertices ) {
	drawCount = numVertices;
	//this->vertices = vertices;

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;
	for ( size_t i = 0; i < numVertices; i++ ) {
		positions.push_back( vertices[i].GetPosition() );
		texCoords.push_back( vertices[i].GetTexCoord() );
		printf( "Pos: %.1f %.1f %.1f\tTexCoord: %.1f %.1f\n", positions[i].x, positions[i].y, positions[i].z, texCoords[i].x, texCoords[i].y );
	}

	vbo = new GLuint[NUM_BUF];

	glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao ); //---------------------------------------------------

	glGenBuffers( NUM_BUF, vbo );

	/* Specify buffer data */
	glBindBuffer( GL_TEXTURE_2D, vbo[POSITION_BUF] );
	glBufferData( GL_TEXTURE_2D, positions.size() * sizeof( positions.front() ), &positions.front(), GL_STATIC_DRAW );

	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );

	glBindBuffer( GL_TEXTURE_2D, vbo[TEXCOORD_BUF] );
	glBufferData( GL_TEXTURE_2D, texCoords.size() * sizeof( texCoords.front() ), &texCoords.front(), GL_STATIC_DRAW );

	glEnableVertexAttribArray( 1 );
	glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, 0 );

	glBindVertexArray( 0 ); //-----------------------------------------------------
}

Texture2DVAO::Texture2DVAO ( const std::vector<Texture2DVertex>& vertices, const std::vector<u_int>& indices ) {
	drawCount = vertices.size();
	this->vertices = vertices;
	this->indices = indices;

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;
	for ( size_t i = 0; i < this->vertices.size(); i++ ) {
		positions.push_back( this->vertices[i].GetPosition() );
		texCoords.push_back( this->vertices[i].GetTexCoord() );
		printf( "Pos: %.1f %.1f %.1f\tTexCoord: %.1f %.1f\n", positions[i].x, positions[i].y, positions[i].z, texCoords[i].x, texCoords[i].y );
	}

	vbo = new GLuint[NUM_BUF];

	glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao ); //---------------------------------------------------

	glGenBuffers( NUM_BUF, vbo );

	/* Specify buffer data */
	glBindBuffer( GL_TEXTURE_2D, vbo[POSITION_BUF] );
	glBufferData( GL_TEXTURE_2D, positions.size() * sizeof( positions.front() ), &positions.front(), GL_STATIC_DRAW );

	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );

	glBindBuffer( GL_TEXTURE_2D, vbo[TEXCOORD_BUF] );
	glBufferData( GL_TEXTURE_2D, texCoords.size() * sizeof( texCoords.front() ), &texCoords.front(), GL_STATIC_DRAW );

	glEnableVertexAttribArray( 1 );
	glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, 0 );

	glBindVertexArray( 0 ); //-----------------------------------------------------
}

void Texture2DVAO::Draw () {
	glBindVertexArray( vao );
	glDrawArrays( GL_TRIANGLES, 0, drawCount );
	glBindVertexArray( 0 );
}

Texture2DVAO::~Texture2DVAO () {
	delete[] vbo;
	glDeleteVertexArrays( 1, &vao );
}