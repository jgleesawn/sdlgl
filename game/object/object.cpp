#include "object.h"

Object::Object(glm::vec4 pos_in) : position(pos_in) {}

Orientable::Orientable(glm::vec4 pos_in, glm::vec3 or_in) : Object(pos_in), orientation(or_in), verticle(glm::vec3(0.0f, 1.0f, 0.0f)) {
	rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
}

void Orientable::rotParallel(float rad) {
//	verticle.w = glm::cos(rad/2.0f);
	glm::quat q;
	q.x = verticle.x*glm::sin(rad/2.0f);
	q.y = verticle.y*glm::sin(rad/2.0f);
	q.z = verticle.z*glm::sin(rad/2.0f);
	q.w = glm::cos(rad/2.0f);

	orientation = glm::rotate(q, orientation);
//	orientation = q*orientation;
	std::cout << "Orientation: ";
	for( int i=0; i<3; i++ )
		std::cout << orientation[i] << " ";
	std::cout << std::endl;
//	orientation = glm::rotate(v, orientation);
//	orientation[1] += rad;

}
void printv(const glm::vec3 & v) {
	for( int i=0; i<3; i++ )
		std::cout << v[i] << " ";
	std::cout << std::endl;
}
void printq(const glm::quat & q) {
	for( int i=0; i<4; i++ )
		std::cout << q[i] << " ";
	std::cout << std::endl;
}
void printm( const glm::mat4 & m) {
	for( int i=0; i<4; i++ ) {
		for( int j=0; j<4; j++ )
			std::cout << m[i][j] << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
void Orientable::rotPerpendicular(float rad) {
	glm::vec3 v = verticle;
	glm::vec3 ov = orientation;
	glm::vec3 c = glm::cross(v, ov);
/*
	std::cout << "Cross1: ";
	printv(c);	
	printv(ov);
	if( glm::length(c) < 0.3 ) {
		return;
//		v = ov;
//		v.y = 0.0f;
//		v = glm::normalize(v);
//		c = glm::cross(v, ov);
	}
	std::cout << "Cross2: ";
	printv(c);
	c = glm::normalize(c);

	std::cout << "Cross Norm: ";
	printv(c);

	std::cout << "Orientation: ";
	for( int i=0; i<3; i++ )
		std::cout << orientation[i] << " ";
	std::cout << std::endl;
*/
	c = glm::normalize(c);
	glm::quat q = glm::quat(glm::cos(rad/2.0f), c.x*glm::sin(rad/2.0f), c.y*glm::sin(rad/2.0f), c.z*glm::sin(rad/2.0f));;
//	q.x = c.x*glm::sin(rad/2.0f);
//	q.y = c.y*glm::sin(rad/2.0f);
//	q.z = c.z*glm::sin(rad/2.0f);
//	q.w = glm::cos(rad/2.0f);

/*
	v.x = 1;
	v.y = 0;
	v.z = 0;

	q.x = v.x*glm::sin(rad/2.0f);
	q.y = v.y*glm::sin(rad/2.0f);
	q.z = v.z*glm::sin(rad/2.0f);
	q.w = glm::cos(rad/2.0f);
*/
	orientation = glm::rotate(q, orientation);

//	float s = glm::sin(orientation[1]);
//	float c = glm::cos(orientation[1]);

//	orientation[2] += c*rad;
//	orientation[0] += s*rad;
}
