#include "shader_util.h"

std::string getFile(const char * filename) {
	std::ifstream t(filename);
	std::string str;

	t.seekg(0, std::ios::end);
	str.reserve(t.tellg());
	t.seekg(0, std::ios::beg);

	str.assign((std::istreambuf_iterator<char>(t)),
			std::istreambuf_iterator<char>());

	return str;
}
