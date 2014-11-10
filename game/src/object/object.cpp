#include "object.h"


Object::Object(glm::vec4 pos_in) : position(pos_in) {}

Orientable::Orientable(glm::vec4 pos_in, glm::quat or_in) : Object(pos_in), orientation(or_in) { }

void Orientable::dQuat(const glm::quat & q) {
	orientation *= q;
}
/*
void Orientable::rotParallel(float rad) {
	glm::quat q;
	q.x = verticle.x*glm::sin(rad/2.0f);
	q.y = verticle.y*glm::sin(rad/2.0f);
	q.z = verticle.z*glm::sin(rad/2.0f);
	q.w = glm::cos(rad/2.0f);

	orientation = glm::rotate(q, orientation);
	std::cout << "Orientation: ";
	for( int i=0; i<3; i++ )
		std::cout << orientation[i] << " ";
	std::cout << std::endl;
}
*/
void printv(const glm::vec3 & v) {
	for( int i=0; i<3; i++ )
		std::cout << v[i] << " ";
	std::cout << std::endl;
}
void printv(const glm::vec4 & v) {
	for( int i=0; i<4; i++ )
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
/*
void Orientable::rotPerpendicular(float rad) {
	glm::vec3 v = verticle;
	glm::vec3 ov = orientation;
	glm::vec3 c = glm::cross(v, ov);
	c = glm::normalize(c);
	glm::quat q = glm::quat(glm::cos(rad/2.0f), c.x*glm::sin(rad/2.0f), c.y*glm::sin(rad/2.0f), c.z*glm::sin(rad/2.0f));;

	orientation = glm::rotate(q, orientation);
}
*/
