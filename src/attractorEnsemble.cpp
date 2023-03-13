#include "attractorEnsemble.h"
#include "ofMain.h"

//------------------------------------------------------------------
attractorEnsemble::attractorEnsemble(int n) {

	numberOfAttractors = n;
	attractPointsPosition.assign(n, glm::vec3(0, 0, 0));
	attractorVector.assign(n, attractor());

}

attractorEnsemble::~attractorEnsemble() {}

void attractorEnsemble::setPositionsOnALine(){
	for (int i = 0; i < numberOfAttractors; i++) {
		glm::vec3 originPoints = glm::vec3((i + 1) * ofGetWidth() / (numberOfAttractors + 1), ofGetHeight() / 2, 0);
 		attractPointsPosition[i] = originPoints;
		attractorVector[i].set_originalPosition(originPoints);
	}
    vectorLength = 0;
}

void attractorEnsemble::setRadialPositions(bool randomizeSigmas) {
    float centerX, centerY, centerZ, theta, thetaStep, maxLength;
    float xpos, ypos;

    centerX = ofGetWidth()/2;
    centerY = ofGetHeight()/2;
    centerZ = 0.0;
    maxLength = min(centerX,centerY);
    vectorLength = ofRandom(0.0, maxLength-100);
    
    thetaStep = 2.0*PI/numberOfAttractors;
    theta = PI/-2.0;

    // assign randomized sigmas to the attractors
    if(randomizeSigmas){
        for (int i = 0; i < numberOfAttractors; i++) {
            attractorVector[i].set_sigma(ofRandom(20,100));
            attractorVector[i].recomputeSigmaAmplitudeDerivedValues();
        }
    }
        
    for (int i = 0; i < numberOfAttractors; i++) {
        xpos = centerX + vectorLength * cos(theta);
        ypos = centerY + vectorLength * sin(theta);
		glm::vec3 originPoints = glm::vec3(xpos, ypos, 0);
		attractPointsPosition[i] = originPoints;
		attractorVector[i].set_originalPosition(originPoints);
        theta += thetaStep;
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

    float x, y;
    
	ofSetColor(190);

	for (unsigned int i = 0; i < attractorVector.size(); i++) {
        x = attractorVector[i].get_originalPosition().x;
        y = attractorVector[i].get_originalPosition().y;
        
		ofNoFill();
        ofSetCircleResolution(100);
		ofDrawCircle(x, y, attractorVector[i].get_sigma());

        ofFill();
		ofDrawCircle(x, y, 4);
	}
}
