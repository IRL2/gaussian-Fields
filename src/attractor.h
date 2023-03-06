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

//	void setRandomPositions(int n);

	std::string getAttractorType() { return attractorType; };
	void setAttractorType(std::string type) { attractorType = type; };

	glm::vec3 calculateForces(std::string label);

//	void displacePositions();
//	void drawDisplaced();
//	void drawOriginal();

private:
	glm::vec3 originalPosition;
 	glm::vec3 displacedPosition;
	std::string attractorType;

};