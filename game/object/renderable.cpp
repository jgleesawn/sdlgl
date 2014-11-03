#include "renderable.h"

Renderable::Renderable(glm::vec4 pos_in, gfxObj_t go, glm::mat4 rot_in = glm::mat4(1.0f)) : gfxObj(go), rotationMatrix(rot_in), Object(pos_in) { }
