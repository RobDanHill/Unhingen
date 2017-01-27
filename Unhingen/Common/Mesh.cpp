#include "Mesh.h"
#include <vector>

Mesh::Mesh ( Vertex *vertices, u_int numVertices ) {
	drawCount = numVertices;
	std::vector<Vertex> positions;
	for ( u_int i = 0; i < numVertices; i++ ) {
		positions.push_back( vertices[i].GetPosition() );
	}

	glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao );

	/* Now, generate the correct number of vbo's */
	glGenBuffers( NUM_BUFFERS, vbo );

	glBindBuffer( GL_ARRAY_BUFFER, vbo[POSITION] );
	glBufferData( GL_ARRAY_BUFFER, positions.size() * sizeof( positions[0] ), &positions[0], GL_STATIC_DRAW );

	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );

	glBindVertexArray( 0 );
}

void Mesh::Draw () {
	glBindVertexArray( vao );
	glDrawArrays( GL_TRIANGLES, 0, drawCount );
	glBindVertexArray( 0 );
}

Mesh::~Mesh () {
	glDeleteVertexArrays( 1, &vao );
}