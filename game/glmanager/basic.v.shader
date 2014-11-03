#version 330

layout(location = 0) in vec4 vertexCoord;

layout(location = 0) uniform vec4 objPosition;
layout(location = 1) uniform mat4 objRotation;

layout(location = 2) uniform vec4 viewOffset;
layout(location = 3) uniform mat4 viewRotation;

//Cheaper to perform multiplication once in program code.
//Didn't want to do matrix math there.
//Fix this.
layout(location = 4) uniform mat4 Perspective;


void main()
{
	vertexCoord.w = 1.0f;
	vec4 vertexPos = ( vertexCoord * objRotation ) + objPosition;
	gl_Position = ( vertexPos - viewOffset ) * (viewRotation * Perspective);
//	vec4 cameraPos = vec4( uOffset.xyz, 1.0f );
//	cameraPos.xyz += position.xyz;
//	gl_Position = perspectiveMatrix * cameraPos;
	//gl_Position = position; //cameraPos;
}
