#include "viewport.h"

Viewport::Viewport(glm::vec4 pos_in, glm::mat4 rot_in, glm::mat4 perspec_in) {
	pos = pos_in;
	rotationMatrix = rot_in;
	perspectiveMatrix = perspec_in;
	for( int i=0; i<4; i++ )
		for( int j=0; j<4; j++ )
			std::cout << perspectiveMatrix[i][j] << " ";
	std::cout << std::endl;
}
