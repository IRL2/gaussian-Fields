#include "attractor.h"

//------------------------------------------------------------------
attractor::attractor() {
    amplitude = 50000.0;
    sigma = 100.0;
    exp_denominator = -2.0 * sigma * sigma;
    coefficient = amplitude / (sigma * sigma);
}

attractor::~attractor() {}

//------------------------------------------------------------------

void attractor::recomputeSigmaAmplitudeDerivedValues(){
    exp_denominator = -2.0 * sigma * sigma;
    coefficient = amplitude / (sigma * sigma);
}

glm::vec3 attractor::calculateForces (std::string label) {
	glm::vec3 forces;

	forces.x = 0.0;
	forces.y = 0.0;
	forces.z = 0.0;

	return forces;
}

