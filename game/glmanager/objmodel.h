#ifndef OBJMODEL_H
#define OBJMODEL_H

#include <vector>
#include <glm/glm.hpp>

struct objModel {
	std::vector<glm::vec4> vertices;
	std::vector<int> indices;
};




#endif
