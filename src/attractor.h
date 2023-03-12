#pragma once

#include "ofMain.h"

class attractor {

public:
	attractor();
	~attractor();

	void set_originalPosition(glm::vec3 pos) { originalPosition = pos; };
	glm::vec3 get_originalPosition() { return originalPosition; };

	void set_displacedPosition(glm::vec3 pos) { displacedPosition = pos; };
	glm::vec3 get_displacedPosition() { return displacedPosition; };

	std::string getAttractorType() { return attractorType; };
	void setAttractorType(std::string type) { attractorType = type; };

	glm::vec3 calculateForces(std::string label);
    
    float get_coefficient(){return coefficient;};
    float get_exp_denominator(){return exp_denominator;};
    float get_sigma(){return sigma;};

private:
	glm::vec3 originalPosition;
 	glm::vec3 displacedPosition;
	std::string attractorType;
    
    float sigma;
    float amplitude;
    float coefficient;
    float exp_denominator;
    
    // the form of the exponential attractor potential energy is:
    // V(r) = [amplitude/(sigma)**2] * exp[-1/2 * ((r-r0)/sigma)**2)]

};
