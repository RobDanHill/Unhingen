#include "BasicVAO.h"

#include <glm\glm.hpp>

tuBasicVAO::tuBasicVAO ( tuVertex *vertices, u_int numVertices ) {
	drawCount = numVertices;
	
	std::vector<glm::vec3> positions;
	for ( size_t i = 0; i < numVertices; i++ ) {
		positions.push_back( vertices[i].GetPosition() );
		printf( "Pos: %.1f %.1f %.1f\n", positions[i].x, positions[i].y, positions[i].z );
	}

	vbo = new GLuint[NUM_BUF];

	glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao ); //---------------------------------------------------

	glGenBuffers( NUM_BUF, vbo );

	/* Specify buffer data */
	glBindBuffer( GL_ARRAY_BUFFER, vbo[POSITION_BUF] );
	glBufferData( GL_ARRAY_BUFFER, positions.size() * sizeof( positions.front() ), &positions.front(), GL_STATIC_DRAW );

	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );

	glBindVertexArray( 0 ); //-----------------------------------------------------
}

void tuBasicVAO::Draw () const {
	glDrawArrays( GL_TRIANGLES, 0, drawCount );
}

void tuBasicVAO::Render () const {
	Bind();
	Draw();
	Unbind();
}

tuBasicVAO::~tuBasicVAO () {
	delete[] vbo;
	glDeleteVertexArrays( 1, &vao );
}