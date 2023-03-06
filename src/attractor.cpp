#include "attractor.h"

//------------------------------------------------------------------
attractor::attractor() {}

attractor::~attractor() {}

//------------------------------------------------------------------

glm::vec3 attractor::calculateForces (std::string label) {
	glm::vec3 forces;

	forces.x = 0.0;
	forces.y = 0.0;
	forces.z = 0.0;

	return forces;
}

