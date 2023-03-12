#include "ofParticle.h"
#include "math.h"

//------------------------------------------------------------------
ofParticle::ofParticle() {
	mass = 1;
}

ofParticle::~ofParticle() {}

glm::vec3 ofParticle::calculateQuadraticForce(attractor attractorObject) {

	float ax, ay, az, dx, dy, dz, scaleFactor(10.0);
	glm::vec3 forceVector;

    ax = attractorObject.get_originalPosition().x;
    ay = attractorObject.get_originalPosition().y;
    az = attractorObject.get_originalPosition().z;

	dx = getx() - ax;
	dy = gety() - ay;
	dz = getz() - az;

	forceVector.x = -2.0 * scaleFactor * dx;
	forceVector.y = -2.0 * scaleFactor * dy;
	forceVector.z = -2.0 * scaleFactor * dz;

	return forceVector;

};

glm::vec3 ofParticle::calculateGaussianForce(attractor attractorObject) {
    
	float dx, dy, dz;
	float prefactor, exp_numerator;
	glm::vec3 forceVector;

    dx = pos.x - attractorObject.get_originalPosition().x;
    dy = pos.y - attractorObject.get_originalPosition().y;
    dz = pos.z - attractorObject.get_originalPosition().z;
    
    exp_numerator = dx * dx + dy * dy + dz * dz;
    prefactor = -1.0 * attractorObject.get_coefficient() * exp(exp_numerator / attractorObject.get_exp_denominator());

	forceVector.x = prefactor * dx;
	forceVector.y = prefactor * dy;
	forceVector.z = prefactor * dz;

	return forceVector;

};
