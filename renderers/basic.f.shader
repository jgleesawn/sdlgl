#version 330 

//out vec4 outputColor;

const vec4 firstColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
const vec4 secondColor = vec4(0.0f, 1.0f, 1.0f, 1.0f);


void main()
{
//	float currTime = mod(time, fragLoopDuration);
//	float currLerp = currTime / fragLoopDuration;

//	outputColor = firstColor; //mix(firstColor, secondColor, currLerp);
	gl_FragColor = firstColor;
}
