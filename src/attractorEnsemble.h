#pragma once

#include "ofMain.h"
#include "attractor.h"

class attractorEnsemble {

public:
	attractorEnsemble(int);
	~attractorEnsemble();

	void setRadialPositions();
	void setPositionsOnALine();
	void setAttractorTypes(std::string);

	vector <glm::vec3> getPositions() { return attractPointsPosition; };

	int getNumberOfAttractors() { return numberOfAttractors; };

	vector <attractor> getAttractorVector() { return attractorVector; };

	void displacePositions();
	void drawPositions();

private:

	int numberOfAttractors;

	vector<attractor> attractorVector;
	vector <glm::vec3> attractPointsPosition;

};
