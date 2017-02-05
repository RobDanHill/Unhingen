#include "Texture2DVAO.h"

#include "..\Utils\IO.h"
#include "..\System\Out.h"
#include <stdio.h>

Texture2DVAO::Texture2DVAO ( const std::vector<Texture2DVertex>& vertices ) {
	drawCount = vertices.size();
	for ( size_t i = 0; i < vertices.size(); i++ ) {
		this->vertices.push_back( vertices[i] );
	}

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

	glGenBuffers( NUM_BUF-1, vbo );

	/* Specify buffer data */
	glBindBuffer( GL_ARRAY_BUFFER, vbo[POSITION_BUF] );
	glBufferData( GL_ARRAY_BUFFER, positions.size() * sizeof( positions.front() ), &positions.front(), GL_STATIC_DRAW );

	glEnableVertexAttribArray( POSITION_BUF );
	glVertexAttribPointer( POSITION_BUF, 3, GL_FLOAT, GL_FALSE, 0, 0 );

	glBindBuffer( GL_ARRAY_BUFFER, vbo[TEXCOORD_BUF] );
	glBufferData( GL_ARRAY_BUFFER, texCoords.size() * sizeof( texCoords.front() ), &texCoords.front(), GL_STATIC_DRAW );

	glEnableVertexAttribArray( TEXCOORD_BUF );
	glVertexAttribPointer( TEXCOORD_BUF, 2, GL_FLOAT, GL_FALSE, 0, 0 );

	glBindVertexArray( 0 ); //-----------------------------------------------------
}

Texture2DVAO::Texture2DVAO ( Texture2DVertex *vertices, u_int numVertices ) {
	drawCount = numVertices;
	std::vector<Texture2DVertex> temp = utils::ToExplicitVector( vertices, numVertices );
	for ( size_t i = 0; i < numVertices; i++ ) {
		this->vertices.push_back( vertices[i] );
	}

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

	glGenBuffers( NUM_BUF-1, vbo );

	/* Specify buffer data */
	glBindBuffer( GL_ARRAY_BUFFER, vbo[POSITION_BUF] );
	glBufferData( GL_ARRAY_BUFFER, positions.size() * sizeof( positions.front() ), &positions.front(), GL_STATIC_DRAW );

	glEnableVertexAttribArray( POSITION_BUF );
	glVertexAttribPointer( POSITION_BUF, 3, GL_FLOAT, GL_FALSE, 0, 0 );

	glBindBuffer( GL_ARRAY_BUFFER, vbo[TEXCOORD_BUF] );
	glBufferData( GL_ARRAY_BUFFER, texCoords.size() * sizeof( texCoords.front() ), &texCoords.front(), GL_STATIC_DRAW );

	glEnableVertexAttribArray( TEXCOORD_BUF );
	glVertexAttribPointer( TEXCOORD_BUF, 2, GL_FLOAT, GL_FALSE, 0, 0 );

	glBindVertexArray( 0 ); //-----------------------------------------------------
}

Texture2DVAO::Texture2DVAO ( const std::vector<Texture2DVertex>& vertices, const std::vector<u_int>& indices ) {
	drawCount = indices.size();
	/*this->vertices = vertices;
	this->indices = indices;*/
	for ( size_t i = 0; i < vertices.size(); i++ ) {
		this->vertices.push_back( vertices[i] );
	}
	for ( size_t i = 0; i < indices.size(); i++ ) {
		this->indices.push_back( indices[i] );
	}

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
	glBindBuffer( GL_ARRAY_BUFFER, vbo[POSITION_BUF] );
	glBufferData( GL_ARRAY_BUFFER, positions.size() * sizeof( positions.front() ), &positions.front(), GL_STATIC_DRAW );

	glEnableVertexAttribArray( POSITION_BUF );
	glVertexAttribPointer( POSITION_BUF, 3, GL_FLOAT, GL_FALSE, 0, 0 );

	glBindBuffer( GL_ARRAY_BUFFER, vbo[TEXCOORD_BUF] );
	glBufferData( GL_ARRAY_BUFFER, texCoords.size() * sizeof( texCoords.front() ), &texCoords.front(), GL_STATIC_DRAW );

	glEnableVertexAttribArray( TEXCOORD_BUF );
	glVertexAttribPointer( TEXCOORD_BUF, 2, GL_FLOAT, GL_FALSE, 0, 0 );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, vbo[INDEX_BUF] );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof( indices.front() ), &indices.front(), GL_STATIC_DRAW );

	glBindVertexArray( 0 ); //-----------------------------------------------------
}

void Texture2DVAO::Draw () const {
	if ( indices.size() > 0 ) {
		glDrawElements( GL_TRIANGLES, drawCount, GL_UNSIGNED_INT, 0 );
	} else {
		glDrawArrays( GL_TRIANGLES, 0, drawCount );
	}
}

void Texture2DVAO::Render () const {
	Bind();
	Draw();
	Unbind();
}

Texture2DVAO::~Texture2DVAO () {
	delete[] vbo;
	glDeleteVertexArrays( 1, &vao );
}