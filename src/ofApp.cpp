#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetVerticalSync(true);
	ofSetFrameRate(60);

//	particleMode = "OF_PARTICLES";
	particleMode = "HF_PARTICLES";
    playPauseMode = "PLAY";
    forBackMode = "FORWARD";
	nattractors = 4;    // 2;
	nparticles = 8000;  // 2000;
    
	pParticleEnsemble = new ofParticleEnsemble(nparticles);
	pAttractorEnsemble = new attractorEnsemble(nattractors);

	pAttractorEnsemble->setAttractorTypes("gaussian"); // options are "gaussian" or "quadratic"
//	pAttractorEnsemble->setAttractorTypes("quadratic"); // options are "gaussian" or "quadratic"

    pAttractorEnsemble->setPositionsOnALine();
    pParticleEnsemble->setNonRandomPositionsAndVelocities(pAttractorEnsemble->getAttractorVector());

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
            pParticleEnsemble->vv_propagatePositionsVelocities(pAttractorEnsemble->getAttractorVector());
        }
    }
	framesPerSecond = 1.0/ofGetLastFrameTime();
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackgroundGradient(ofColor(60, 60, 60), ofColor(10, 10, 10));

	pParticleEnsemble->draw();

	if (particleMode == "OF_PARTICLES") {
		pAttractorEnsemble->drawPositions();
	}
	else if (particleMode == "HF_PARTICLES") {
		pAttractorEnsemble->drawPositions();
	}

	float KE = pParticleEnsemble->getTotalKineticEnergy();
    float vL = pAttractorEnsemble->get_vectorLength();

    ofSetColor(230);
    writePosition = 10;
	ofDrawBitmapString("'r' resets attractor positions. Holding 'z' zeros out the forces. 'Space' pauses the sim.", 10, 20);
	ofDrawBitmapString("FPS: " + ofToString(int(framesPerSecond)), writePosition, 40);
    writePosition += 80;
    ofDrawBitmapString("Play/Pause: " + ofToString(playPauseMode), writePosition, 40);
    writePosition += 150;
    ofDrawBitmapString("For/Back: " + ofToString(forBackMode), writePosition, 40);
    
    writePosition = 10;
    ofDrawBitmapString("total KE: " + ofToString(KE), writePosition, 60);
    writePosition += 200;
    ofDrawBitmapString("natoms: " + ofToString(nparticles), writePosition, 60);
    writePosition += 140;
    ofDrawBitmapString("vecLength: " + ofToString(vL), writePosition, 60);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	
    if((key == ' ') && playPauseMode == "PLAY"){playPauseMode = "PAUSE";}
    else if((key == ' ') && playPauseMode == "PAUSE"){playPauseMode = "PLAY";}

    if((key == 'f') && forBackMode == "FORWARD"){
        forBackMode = "BACKWARD";
        pParticleEnsemble->invertVelocities();
    }
    else if((key == 'f') && forBackMode == "BACKWARD"){
        forBackMode = "FORWARD";
        pParticleEnsemble->invertVelocities();
    }
    
    if (playPauseMode == "PLAY"){
        if ((key == 'r') && (particleMode == "OF_PARTICLES")) {
            pAttractorEnsemble->setRadialPositions();
            pParticleEnsemble->setRandomPositionsAndVelocities(nparticles);
        }
        
        if ((key == 'r') && (particleMode == "HF_PARTICLES")) {
            pAttractorEnsemble->setRadialPositions();
            pParticleEnsemble->setNonRandomPositionsAndVelocities(pAttractorEnsemble->getAttractorVector());
        }
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
