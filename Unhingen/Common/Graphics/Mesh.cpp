#include "Mesh.h"
#include <vector>

Mesh::Mesh ( Texture2DVertex *vertices, u_int numVertices ) {
	drawCount = numVertices;
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;
	for ( u_int i = 0; i < numVertices; i++ ) {
		positions.push_back( vertices[i].GetPosition() );
		texCoords.push_back( vertices[i].GetTexCoord() );
	}

	glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao );

	/* Now, generate the correct number of vbo's */
	glGenBuffers( 1, vbo );

	glBindBuffer( GL_ARRAY_BUFFER, vbo[POSITION] );
	glBufferData( GL_ARRAY_BUFFER, positions.size() * sizeof( positions.front() ), &positions.front(), GL_STATIC_DRAW );

	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );

	glBindBuffer( GL_ARRAY_BUFFER, vbo[TEXCOORD] );
	glBufferData( GL_ARRAY_BUFFER, texCoords.size() * sizeof( texCoords.front() ), &texCoords.front(), GL_STATIC_DRAW );

	glEnableVertexAttribArray( 1 );
	glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, 0 );

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