#include "attractorEnsemble.h"
#include "ofMain.h"

//------------------------------------------------------------------
attractorEnsemble::attractorEnsemble(int n) {

	numberOfAttractors = n;
	attractPointsPosition.assign(n, glm::vec3(0, 0, 0));
	attractorVector.assign(n, attractor());
    displayGaussians = true;
    
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

void attractorEnsemble::setRadialPositions(bool randomizeSigmas, bool randomizeAmplitudes, bool randomizeMajorMinorAxis, bool randomizeInitialParticleRadii, bool multipleColors) {
    
    float centerX, centerY, centerZ, theta, thetaStep, maxLength;
    float xpos, ypos, zpos, sigma, amplitude, initialParticleRadii;
    ofColor color1, color2;

    centerX = ofGetWidth()/2;
    centerY = ofGetHeight()/2;
    centerZ = 0.0;
    maxLength = min(centerX,centerY);
    
    vectorLength = ofRandom(0.0, maxLength-100);  // set the vector Lengths
//    vectorLength = 142.5;

//    color1 = ofColor::teal;
    color1 = ofColor::floralWhite;
//    color2 = ofColor::steelBlue;

    sigma = ofRandom(60,120);
//    sigma = 85.5;
    amplitude = ofRandom(20000,80000);

    /*
    if(positionsOnALine){
        
    }
    */
    
    for (int i = 0; i < numberOfAttractors; i++) {
        attractorVector[i].set_placement(vectorLength); // set the vectorLength
        attractorVector[i].set_color(color1);           // set the color
        attractorVector[i].set_sigma(sigma);
        attractorVector[i].set_amplitude(amplitude);
    }
    
    if(multipleColors){
        if (numberOfAttractors > 2 && numberOfAttractors % 2 == 0) { // even number of attractors which is greater than 2
            attractorVector[0].set_color(color2);
            attractorVector[numberOfAttractors/2].set_color(color2);
        }
    }
    
    if(randomizeMajorMinorAxis){
        vectorLength = ofRandom(0.0, maxLength-100);
        if (numberOfAttractors > 2 && numberOfAttractors % 2 == 0) { // even number of attractors which is greater than 2
            attractorVector[0].set_placement(vectorLength);
            attractorVector[numberOfAttractors/2].set_placement(vectorLength);
        }
    }
    
    if(randomizeAmplitudes){
        amplitude = ofRandom(30000,70000);
        if(numberOfAttractors > 2 && numberOfAttractors % 2 == 0){
            attractorVector[0].set_amplitude(amplitude);
            attractorVector[numberOfAttractors/2].set_amplitude(amplitude);
        }
    }
    
    // assign randomized sigmas to the attractors, one random sigma along major axis, one along the minor
    if(randomizeSigmas){
        sigma = ofRandom(20,100);
        if (numberOfAttractors > 2 && numberOfAttractors % 2 == 0) { // even number of attractors which is greater than 2
            attractorVector[0].set_sigma(sigma);
            attractorVector[numberOfAttractors/2].set_sigma(sigma);
        }
    }

    // set the initialParticleRadii to be identical to sigma for each attractor
    for (int i = 0; i < numberOfAttractors; i++) {
        attractorVector[i].set_initialParticleRadii(attractorVector[i].get_sigma());
    }
        
    if(randomizeInitialParticleRadii){
        initialParticleRadii = ofRandom(0.5*attractorVector[0].get_sigma(), 1.5*attractorVector[0].get_sigma());
        if(numberOfAttractors > 2){
            for (int i=1; i < numberOfAttractors; i++){
                attractorVector[i].set_initialParticleRadii(initialParticleRadii);
            }
            if(numberOfAttractors % 2 == 0){
                attractorVector[numberOfAttractors/2].set_initialParticleRadii(attractorVector[0].get_initialParticleRadii());
            }
        }
    }

    thetaStep = 2.0*PI/numberOfAttractors;
    theta = PI/-2.0;

    for (int i = 0; i < numberOfAttractors; i++) {
        xpos = centerX + attractorVector[i].get_placement() * cos(theta);
        ypos = centerY + attractorVector[i].get_placement() * sin(theta);
        zpos = 0;
		glm::vec3 originPoints = glm::vec3(xpos, ypos, zpos);
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

    if(ofGetKeyPressed('d') && !displayGaussians){
        displayGaussians = true;
    }
    else if(ofGetKeyPressed('d') && displayGaussians){
        displayGaussians = false;
    }

    if (displayGaussians){
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
        
}
