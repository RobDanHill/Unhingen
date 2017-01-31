#version 120

uniform vec3 color;
uniform sampler2D tex;

/* Grab the vTexCoord var from the vertex shader */
varying vec2 vTexCoord;

void main () {
	gl_FragColor = texture2D( tex, vTexCoord ); //vec4( color, 1.0 );
}