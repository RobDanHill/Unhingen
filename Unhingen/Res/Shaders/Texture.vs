#version 120

attribute vec3 position;
attribute vec2 texCoord;

uniform mat4 transform;

/* varying vars can be accessed within the fragment shader */
varying vec2 vTexCoord;

void main () {
	gl_Position = transform * vec4( position, 1.0 );
	vTexCoord = texCoord;
}