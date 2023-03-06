#include "ofParticle.h"
#include "math.h"

//------------------------------------------------------------------
ofParticle::ofParticle() {
	mass = 1;
}

ofParticle::~ofParticle() {}


glm::vec3 ofParticle::calculateQuadraticForce(glm::vec3 attractXYZ) {

	float ax, ay, az, dx, dy, dz, scaleFactor(10.0);
	glm::vec3 forceVector;

	ax = attractXYZ.x;
	ay = attractXYZ.y;
	az = attractXYZ.z;

	dx = getx() - ax;
	dy = gety() - ay;
	dz = getz() - az;

//	dist = sqrt(dx * dx + dy * dy + dz * dz);

	forceVector.x = -2.0 * scaleFactor * dx;
	forceVector.y = -2.0 * scaleFactor * dy;
	forceVector.z = -2.0 * scaleFactor * dz;

	return forceVector;

};

glm::vec3 ofParticle::calculateGaussianForce(glm::vec3 attractXYZ) {

	float ax, ay, az, dx, dy, dz;
	float amplitude(50000.0), sigma(100.0), prefactor, argnum, argden;
	glm::vec3 forceVector;

	ax = attractXYZ.x;
	ay = attractXYZ.y;
	az = attractXYZ.z;

	dx = getx() - ax;
	dy = gety() - ay;
	dz = getz() - az;

	argnum = dx * dx + dy * dy + dz * dz;

	argden = -2.0 * sigma * sigma;
	prefactor = (amplitude / (sigma * sigma)) * exp(argnum / argden);

	forceVector.x = -1.0 * prefactor * dx;
	forceVector.y = -1.0 * prefactor * dy;
	forceVector.z = -1.0 * prefactor * dz;

	return forceVector;

};


//------------------------------------------------------------------
//void ofParticle::resetPositionsAndVelocities() {
//	//the unique val allows us to set properties slightly differently for each particle
//	uniqueVal = ofRandom(-10000, 10000);
//
//	pos.x = ofRandomWidth();
//	pos.y = ofRandomHeight();
//	pos.z = 0;
//
//	vel.x = ofRandom(-3.9, 3.9);
//	vel.y = ofRandom(-3.9, 3.9);
//	vel.z = 0;
//
//	frc = glm::vec3(0, 0, 0);
//	scale = ofRandom(0.5, 1.0);
//    drag = ofRandom(0.95, 0.998);
//}
//
////------------------------------------------------------------------
//void ofParticle::propagatePositionsAndVelocities(vector <glm::vec3> attractPoints) {
//
//	if (attractPoints.size() > 0) {
//
//		//1 - find closest attractPoint 
//		glm::vec3 closestPt;
//		int closest = -1;
//		float closestDist = 9999999;
//
//		for (unsigned int i = 0; i < attractPoints.size(); i++) {
//			float lenSq = glm::length2(attractPoints.at(i) - pos);
//			if (lenSq < closestDist) {
//				closestDist = lenSq;
//				closest = i;
//			}
//		}
//
//		//2 - if we have a closest point - lets calcuate the force towards it
//		if (closest != -1) {
//			closestPt = attractPoints.at(closest);
//			float dist = sqrt(closestDist);
//
//			//in this case we don't normalize as we want to have the force proportional to distance 
//			frc = closestPt - pos;
//
//			vel *= drag;
//
//			//lets also limit our attraction to a certain distance and don't apply if 'f' key is pressed
//			if (dist < 300 && dist > 40 && !ofGetKeyPressed('f')) {
//				vel += frc * 0.003;
//			}
//			else {
//				//if the particles are not close to us, lets add a little bit of random movement using noise. this is where uniqueVal comes in handy. 			
//
//				frc.x = ofSignedNoise(uniqueVal, pos.y * 0.01, ofGetElapsedTimef() * 0.2);
//				frc.y = ofSignedNoise(uniqueVal, pos.x * 0.01, ofGetElapsedTimef() * 0.2);
//				vel += frc * 0.4;
//			}
//		}
//	}
//
//	//2 - UPDATE OUR POSITION
//	pos += vel;
//
//	//3 - (optional) LIMIT THE PARTICLES TO STAY ON SCREEN 
//	//we could also pass in bounds to check - or alternatively do this at the ofApp level
//	if (pos.x > ofGetWidth()) {
//		pos.x = ofGetWidth();
//		vel.x *= -1.0;
//	}
//	else if (pos.x < 0) {
//		pos.x = 0;
//		vel.x *= -1.0;
//	}
//	if (pos.y > ofGetHeight()) {
//		pos.y = ofGetHeight();
//		vel.y *= -1.0;
//	}
//	else if (pos.y < 0) {
//		pos.y = 0;
//		vel.y *= -1.0;
//	}
//
//}

////------------------------------------------------------------------
//void ofParticle::draw() {
//
//	ofSetColor(103, 160, 237);
//	ofDrawCircle(pos.x, pos.y, scale * 4.0);
//
//}

