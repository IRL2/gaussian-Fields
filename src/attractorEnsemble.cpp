#include "attractorEnsemble.h"
#include "ofMain.h"

//------------------------------------------------------------------
attractorEnsemble::attractorEnsemble(int n) {

	numberOfAttractors = n;
	attractPointsPosition.assign(n, glm::vec3(0, 0, 0));
	attractorVector.assign(n, attractor());

}

attractorEnsemble::~attractorEnsemble() {}

void attractorEnsemble::setNonRandomPositions(){
	for (int i = 0; i < numberOfAttractors; i++) {
		glm::vec3 originPoints = glm::vec3((i + 1) * ofGetWidth() / (numberOfAttractors + 1), ofGetHeight() / 2, 0);
 		attractPointsPosition[i] = originPoints;
		attractorVector[i].set_originalPosition(originPoints);
	}
}

void attractorEnsemble::setRandomPositions() {
	for (int i = 0; i < numberOfAttractors; i++) {
		glm::vec3 originPoints = glm::vec3(ofRandom(100, ofGetWidth() - 100), ofRandom(100, ofGetHeight() - 100), 0);
		attractPointsPosition[i] = originPoints;
		attractorVector[i].set_originalPosition(originPoints);
	}
}

void attractorEnsemble::displacePositions() {
	// Displace the attractors from their position by some noise
	for (unsigned int i = 0; i < attractPointsPosition.size(); i++) {
		attractPointsPosition[i].x = attractPointsPosition[i].x + ofSignedNoise(i *  1, ofGetElapsedTimef() * 0.7) * 0.5;
		attractPointsPosition[i].y = attractPointsPosition[i].y + ofSignedNoise(i * -1, ofGetElapsedTimef() * 0.7) * 0.5;
		attractPointsPosition[i].z = attractPointsPosition[i].z + ofSignedNoise(i * -1, ofGetElapsedTimef() * 0.7) * 0.5;
	}
}


void attractorEnsemble::setAttractorTypes(string label) {
	
	if (label == "gaussian") {
		for (int i = 0; i < numberOfAttractors; i++) {
			attractorVector[i].setAttractorType("gaussian");
		}
	}
	else if (label == "quadratic") {
		for (int i = 0; i < numberOfAttractors; i++) {
			attractorVector[i].setAttractorType("quadratic");
		}
	}
}

void attractorEnsemble::drawPositions() {

	ofSetColor(190);

	for (unsigned int i = 0; i < attractPointsPosition.size(); i++) {
		ofNoFill();
		ofDrawCircle(attractPointsPosition[i], 10);
		ofFill();
		ofDrawCircle(attractPointsPosition[i], 4);
	}
}