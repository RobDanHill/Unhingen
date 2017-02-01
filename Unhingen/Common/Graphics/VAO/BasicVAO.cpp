#include "BasicVAO.h"

#include <glm\glm.hpp>

BasicVAO::BasicVAO ( Vertex *vertices, u_int numVertices ) {
	drawCount = numVertices;
	
	std::vector<glm::vec3> positions;
	for ( size_t i = 0; i < numVertices; i++ ) {
		positions.push_back( vertices[i].GetPosition() );
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

	glBindVertexArray( 0 ); //-----------------------------------------------------
}

void BasicVAO::Draw () {
	glBindVertexArray( vao );
	glDrawArrays( GL_TRIANGLES, 0, drawCount );
	glBindVertexArray( 0 );
}

BasicVAO::~BasicVAO () {
	delete[] vbo;
	glDeleteVertexArrays( 1, &vao );
}