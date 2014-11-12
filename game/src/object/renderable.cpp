#include "renderable.h"

Renderable::Renderable(glm::vec4 pos_in, gfxObj_t go, glm::quat or_in ) : gfxObj(go), Object(pos_in, or_in) { }
