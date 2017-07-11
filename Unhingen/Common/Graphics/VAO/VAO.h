#pragma once

#include "..\Common\Types.h"
#include "..\Common\Graphics\Vertex\Vertex.h"
#include "ModelTransform.h"
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <vector>

class tuVAO_a {
	public:
		inline void Bind () const { glBindVertexArray( vao ); }
		inline void Unbind () const { glBindVertexArray( 0 ); }
		inline tuModelTransform& GetTransform () { return transform; }
		virtual void Draw () const = 0;
		virtual void Render () const = 0;
	protected:
		GLuint				vao;
		GLuint				*vbo;
		u_int				drawCount;
		std::vector<u_int>	indices;
		tuModelTransform		transform;
};