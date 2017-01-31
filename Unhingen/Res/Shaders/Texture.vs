#version 120

attribute vec3 position;
attribute vec2 texCoord;

/* varying vars can be accessed within the fragment shader */
varying vec2 vTexCoord;

void main () {
	gl_Position = vec4( position, 1.0 );
	vTexCoord = texCoord;
}