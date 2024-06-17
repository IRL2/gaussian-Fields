#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetVerticalSync(true);
	ofSetFrameRate(60);

//	particleMode = "OF_PARTICLES";
	particleMode = "HF_PARTICLES";     
    playPauseMode = "PLAY";
    forBackMode = "FORWARD";

//  whether sigma defining the attractor radii are identical or not
    randomizeSigmas = false;
//  whether the gaussian amplitudes are identical or not
    randomizeAmplitudes = false;
//  whether the attractor centroids are equidistant from the center
    randomizeMajorMinorAxis = true;
//  whether the initial particle positions can have any radii (need not be constrained to start at sigma)
    randomizeParticleRadii = false;
//  whether the particles corresponding to a given attractor need have the same color or not
    manyColors = false;

//  whether to thermostat the dynamics - setting to "0" is no thermostat
    thermostatTemp = 0;
    
    nattractors = 4;    // 2;
	nparticles = 16000;  // 2000;
    simulationTimestep = 0.005;
    nSimulationStepsPerRenderStep = 1;
    
	pParticleEnsemble = new ofParticleEnsemble(nparticles,simulationTimestep,thermostatTemp);
	pAttractorEnsemble = new attractorEnsemble(nattractors);

	pAttractorEnsemble->setAttractorTypes("gaussian"); // options are "gaussian" or "quadratic"
//	pAttractorEnsemble->setAttractorTypes("quadratic"); // options are "gaussian" or "quadratic"

    pAttractorEnsemble->setPositionsOnALine();
    pParticleEnsemble->setRadialPositionsAndVelocities(pAttractorEnsemble->getAttractorVector());

}

//--------------------------------------------------------------
void ofApp::update() {

    if (playPauseMode == "PLAY"){
        if (particleMode == "OF_PARTICLES") {
            //		add movement to the attractors
            pAttractorEnsemble->displacePositions();
            vector <glm::vec3> attractorPositions = pAttractorEnsemble->getPositions();
            pParticleEnsemble->of_propagatePositionsVelocities(attractorPositions);
        }
        else if (particleMode == "HF_PARTICLES") {
            for (int jj = 0; jj < nSimulationStepsPerRenderStep; jj++){
                pParticleEnsemble->vv_propagatePositionsVelocities(pAttractorEnsemble->getAttractorVector());
            }
        }
    }
	framesPerSecond = 1.0/ofGetLastFrameTime();
}

//--------------------------------------------------------------
void ofApp::draw() {
//	ofBackgroundGradient(ofColor(60, 60, 60), ofColor(10, 10, 10));
//    ofBackgroundGradient(ofColor(0, 0, 0), ofColor(0, 0, 0));

//    bgColor = ofColor::orangeRed;
    bgColor = ofColor::black;
    
    ofBackgroundGradient(bgColor, bgColor);
    
	pParticleEnsemble->draw();

	if (particleMode == "OF_PARTICLES") {
		pAttractorEnsemble->drawPositions();
	}
	else if (particleMode == "HF_PARTICLES") {
		pAttractorEnsemble->drawPositions();
	}

	float KE = pParticleEnsemble->getTotalKineticEnergy();
    float vL = pAttractorEnsemble->get_vectorLength();
    int stepCount = pParticleEnsemble->getStepCount();

    ofSetColor(230);

    writePosition = 10;
    

    ofDrawBitmapString("'r' resets attractor positions. 'z' assigns zero to the forces.", writePosition, 20);

    ofDrawBitmapString("natoms: " + ofToString(nparticles), writePosition, 40);
    writePosition += 140;
    ofDrawBitmapString("Play/Pause (Spacebar): " + ofToString(playPauseMode), writePosition, 40);
    writePosition += 250;
    ofDrawBitmapString("Forward/Backward ('b'): " + ofToString(forBackMode), writePosition, 40);
    
    writePosition = 10;
    ofDrawBitmapString("FPS: " + ofToString(int(framesPerSecond)), writePosition, 60);
    writePosition += 80;
    ofDrawBitmapString("stepCount: " + ofToString(stepCount), writePosition, 60);
    writePosition += 180;
    ofDrawBitmapString("vecLength: " + ofToString(vL), writePosition, 60);


//    option to write out the total kinetic energy if you want
    writePosition += 180;
    ofDrawBitmapString("total KE: " + ofToString(KE), writePosition, 60);
    
    writePosition += 180;
    if (thermostatTemp == 0){
        ofDrawBitmapString("Thermostat OFF", writePosition, 60);
    }
    else {
        ofDrawBitmapString("temp(+/-): " + ofToString(thermostatTemp), writePosition, 60);
    }
    
    // draw center
    ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, 2.0);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	
    if((key == ' ') && playPauseMode == "PLAY"){playPauseMode = "PAUSE";}
    else if((key == ' ') && playPauseMode == "PAUSE"){playPauseMode = "PLAY";}

    if(pParticleEnsemble->get_timeReversalInProgress()==false){  //only allow time reversal if one is not in progress
        if((key == 'b') && forBackMode == "FORWARD"){
            forBackMode = "BACKWARD";
            pParticleEnsemble->set_timeReversalInProgress(true);
        }
        else if((key == 'b') && forBackMode == "BACKWARD"){
            forBackMode = "FORWARD";
            pParticleEnsemble->set_timeReversalInProgress(true);
        }
    }
    
    if (playPauseMode == "PLAY"){
        if ((key == 'r') && (particleMode == "OF_PARTICLES")) {
            pAttractorEnsemble->setRadialPositions(randomizeSigmas, randomizeAmplitudes, randomizeMajorMinorAxis, randomizeParticleRadii, manyColors);
            pParticleEnsemble->setRandomPositionsAndVelocities(nparticles);
        }
        
        if ((key == 'r') && (particleMode == "HF_PARTICLES")) {
            pAttractorEnsemble->setRadialPositions(randomizeSigmas, randomizeAmplitudes, randomizeMajorMinorAxis, randomizeParticleRadii, manyColors);
            pParticleEnsemble->resetStepCount();
            pParticleEnsemble->setRadialPositionsAndVelocities(pAttractorEnsemble->getAttractorVector());
        }
    }
    
    float tempStep = 20;
    if (key == '='){
        thermostatTemp += tempStep;
        pParticleEnsemble->set_Tequilibrium(thermostatTemp);
    }
    if (key == '-' && thermostatTemp >= tempStep){
        thermostatTemp -= tempStep;
        pParticleEnsemble->set_Tequilibrium(thermostatTemp);
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
