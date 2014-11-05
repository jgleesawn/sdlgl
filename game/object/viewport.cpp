#include "viewport.h"

Viewport::Viewport(glm::vec4 pos_in, glm::vec3 or_in, glm::mat4 perspec_in) : Orientable(pos_in, or_in) {
	perspectiveMatrix = perspec_in;
	for( int i=0; i<4; i++ )
		for( int j=0; j<4; j++ )
			std::cout << perspectiveMatrix[i][j] << " ";
	std::cout << std::endl;
}

void Viewport::Move(glm::vec4 offset) {
	position -= glm::rotate(rotation, offset);
}

void Viewport::rotParallel(float rad) {
	rad *= -1;
	glm::quat q;
	q.x = verticle.x*glm::sin(rad/2.0f);
	q.y = verticle.y*glm::sin(rad/2.0f);
	q.z = verticle.z*glm::sin(rad/2.0f);
	q.w = glm::cos(rad/2.0f);
	
	printv(glm::rotate(rotation, orientation));

	rotation *= q;
//	orientation = glm::rotate(q, orientation);
//	printv(orientation);
	printq(rotation);
}

void Viewport::rotPerpendicular(float rad) {
	rad *= -1;

	glm::vec3 v = verticle;
	glm::vec3 ov = glm::rotate(rotation, orientation);
	glm::vec3 c = glm::cross(v, ov);
	printv(glm::rotate(rotation, orientation));

/*	if( glm::length(c) < 0.001 ) {
		v = ov;
		v.y = 0.0f;
		v = glm::normalize(v);
		c = glm::cross(v, ov);
	}
*/
	c = glm::normalize(c);

	glm::quat q = glm::quat(glm::cos(rad/2.0f), c.x*glm::sin(rad/2.0f), c.y*glm::sin(rad/2.0f), c.z*glm::sin(rad/2.0f));

	rotation *= q;
	printq(rotation);
}




