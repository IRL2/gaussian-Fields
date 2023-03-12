#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetVerticalSync(true);
	ofSetFrameRate(60);

//	currentMode = "OF_PARTICLES";
	currentMode = "HF_PARTICLES";
	nattractors = 4;    // 2;
	nparticles = 10000;  // 2000;

	pParticleEnsemble = new ofParticleEnsemble(nparticles);
	pAttractorEnsemble = new attractorEnsemble(nattractors);

	pAttractorEnsemble->setAttractorTypes("gaussian"); // options are "gaussian" or "quadratic"
//	pAttractorEnsemble->setAttractorTypes("quadratic"); // options are "gaussian" or "quadratic"

    pAttractorEnsemble->setNonRandomPositions();
    pParticleEnsemble->setNonRandomPositionsAndVelocities(pAttractorEnsemble->getAttractorVector());

}

//--------------------------------------------------------------
void ofApp::update() {

	if (currentMode == "OF_PARTICLES") {
//		add movement to the attractors
		pAttractorEnsemble->displacePositions();
		vector <glm::vec3> attractorPositions = pAttractorEnsemble->getPositions();
		pParticleEnsemble->of_propagatePositionsVelocities(attractorPositions);
	}
	else if (currentMode == "HF_PARTICLES") {
		pParticleEnsemble->vv_propagatePositionsVelocities(pAttractorEnsemble->getAttractorVector());
	}

	framesPerSecond = 1.0 /ofGetLastFrameTime();
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackgroundGradient(ofColor(60, 60, 60), ofColor(10, 10, 10));

	pParticleEnsemble->draw();

	if (currentMode == "OF_PARTICLES") {
		pAttractorEnsemble->drawPositions();
	}
	else if (currentMode == "HF_PARTICLES") {
		pAttractorEnsemble->drawPositions();
	}

	float KE = pParticleEnsemble->getTotalKineticEnergy();

	ofSetColor(230);
	ofDrawBitmapString(currentMode + " - holding 'f' zeros out the forces; press Spacebar to reset.", 10, 20);
	ofDrawBitmapString("\nFPS: " + ofToString(framesPerSecond), 10, 40);
	ofDrawBitmapString("\ntotal KE: " + ofToString(KE), 150, 40);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	
	if ((key == ' ') && (currentMode == "OF_PARTICLES")) {
		pAttractorEnsemble->setRandomPositions();
		pParticleEnsemble->setRandomPositionsAndVelocities(nparticles);
	}

	if ((key == ' ') && (currentMode == "HF_PARTICLES")) {
		pAttractorEnsemble->setRandomPositions();
		pParticleEnsemble->setNonRandomPositionsAndVelocities(pAttractorEnsemble->getAttractorVector());
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
