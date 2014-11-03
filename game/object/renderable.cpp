#include "renderable.h"

Renderable::Renderable(glm::vec4 pos_in, gfxObj_t go, glm::mat4 rot_in ) : gfxObj(go), rotationMatrix(rot_in), Object(pos_in) { }
