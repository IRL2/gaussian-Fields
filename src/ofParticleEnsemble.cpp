#include "ofParticleEnsemble.h"
#include "ofMain.h"


//------------------------------------------------------------------
ofParticleEnsemble::ofParticleEnsemble(int n, float dt) {
	kb = 8.314;
	scaleFactor = 1.0;
	numberOfParticles = n;
	particleVector.assign(n, ofParticle());
	stepNumber = 0;
	BerendsenThermostat = false;
	timestep = dt;
	mass = 1.0;
    stepIncrement = 1;
}

ofParticleEnsemble::~ofParticleEnsemble() {}

void ofParticleEnsemble::setRandomPositionsAndVelocities(int n) {

	for (unsigned int i = 0; i < particleVector.size(); i++) {

		particleVector[i].set_uniqueVal(ofRandom(-10000, 10000));

		particleVector[i].setx(ofRandom(10, ofGetWidth() - 10));
		particleVector[i].sety(ofRandom(10, ofGetHeight() - 10));
		particleVector[i].setz(0);

		particleVector[i].setvx(ofRandom(-3.9, 3.9));
		particleVector[i].setvy(ofRandom(-3.9, 3.9));
		particleVector[i].setvz(0);

		particleVector[i].setfx(0);
		particleVector[i].setfy(0);
		particleVector[i].setfz(0);

		particleVector[i].set_scale(ofRandom(0.5, 1.0));
		particleVector[i].set_drag(ofRandom(0.95, 0.998));
	}

}

void ofParticleEnsemble::setNonRandomPositionsAndVelocities(vector <attractor> attractorVec) {

	float ax, ay, az, d1, d2, d;
	float distFromEdge(20.0), fraction(3.0);
	float height, width, theta, xpolar, ypolar;
	int anyLeftovers, nAttractors, loopSize, particleIndex(0);
	glm::vec3 attractor_position;
	vector <int> loopSizeVector;

	width = ofGetWidth();
	height = ofGetHeight();

	particleIndex = 0;
	nAttractors = int(attractorVec.size());
	loopSize = numberOfParticles/nAttractors;

	loopSizeVector.assign(nAttractors, loopSize);

	// the lines below handle cases where there is an even number of attractors & odd number of particles. or vice-versa
	anyLeftovers = numberOfParticles - ( nAttractors * loopSize); 
	if (anyLeftovers > 0) {
		loopSizeVector[nAttractors - 1] = loopSize + anyLeftovers;
	}

	for (int kk = 0; kk < nAttractors; kk++) {

		attractor_position = attractorVec[kk].get_originalPosition();
		ax = attractor_position.x;
		ay = attractor_position.y;
		az = attractor_position.z;

		d1 = min(ax / fraction, (width - ax) / fraction);
		d2 = min(ay / fraction, (height - ay) / fraction);
		d = min(d1, d2);

		for (int i = 0; i < loopSizeVector[kk]; i++) {

			particleVector[particleIndex].set_uniqueVal(ofRandom(-10000, 10000));

			theta = float(i)*2*PI/loopSizeVector[kk];
			xpolar = cos(theta);
			ypolar = sin(theta);

			particleVector[particleIndex].setx(ax + d*xpolar);
			particleVector[particleIndex].sety(ay + d*ypolar);
			particleVector[particleIndex].setz(0);

			particleVector[particleIndex].setvx(0);
			particleVector[particleIndex].setvy(0);
			particleVector[particleIndex].setvz(0);

			particleVector[particleIndex].setfx(0);
			particleVector[particleIndex].setfy(0);
			particleVector[particleIndex].setfz(0);

			particleVector[particleIndex].set_scale(ofRandom(0.70, 0.80));
			particleVector[particleIndex].set_drag(ofRandom(0.95, 0.998));

			++particleIndex;
		}
	}
}

//------------------------------------------------------------------
void ofParticleEnsemble::of_propagatePositionsVelocities(vector <glm::vec3> attractPoints) {

	for (unsigned int i = 0; i < particleVector.size(); i++) {

		glm::vec3 pos;
		glm::vec3 frc;
		glm::vec3 vel;
		float drag;
		float uniqueVal;

		if (attractPoints.size() > 0) {

			pos = particleVector[i].get_pos();
			vel = particleVector[i].get_vel();
			drag = particleVector[i].get_drag();
			uniqueVal = particleVector[i].get_uniqueVal();

			//1 - find closest attractPoint 
			glm::vec3 closestPt;
			int closest = -1;
			float closestDist = 9999999;

			for (unsigned int i = 0; i < attractPoints.size(); i++) {
				float lenSq = glm::length2(attractPoints.at(i) - pos);
				if (lenSq < closestDist) {
					closestDist = lenSq;
					closest = i;
				}
			}

			//2 - if we have a closest point - lets calcuate the force towards it
			if (closest != -1) {
				closestPt = attractPoints.at(closest);
				float dist = sqrt(closestDist);

				//in this case we don't normalize as we want to have the force proportional to distance 
				frc = closestPt - pos;

				vel *= drag;

				//lets also limit our attraction to a certain distance and don't apply if 'f' key is pressed
				if (dist < 300 && dist > 40 && !ofGetKeyPressed('z')) {
					vel += frc * 0.003;
				}
				else {
					//if the particles are not close to us, lets add a little bit of random movement using noise. this is where uniqueVal comes in handy. 			
					frc.x = ofSignedNoise(uniqueVal, pos.y * 0.01, ofGetElapsedTimef() * 0.2);
					frc.y = ofSignedNoise(uniqueVal, pos.x * 0.01, ofGetElapsedTimef() * 0.2);
					vel += frc * 0.4;
				}
			}
		}

		//2 - UPDATE OUR POSITION
		pos += vel;

		//3 - (optional) LIMIT THE PARTICLES TO STAY ON SCREEN 
		//we could also pass in bounds to check - or alternatively do this at the ofApp level
		if (pos.x > ofGetWidth()) {
			pos.x = ofGetWidth();
			vel.x *= -1.0;
		}
		else if (pos.x < 0) {
			pos.x = 0;
			vel.x *= -1.0;
		}
		if (pos.y > ofGetHeight()) {
			pos.y = ofGetHeight();
			vel.y *= -1.0;
		}
		else if (pos.y < 0) {
			pos.y = 0;
			vel.y *= -1.0;
		}

		particleVector[i].set_pos(pos);
		particleVector[i].set_vel(vel);
		particleVector[i].set_frc(frc);

	}

}

void ofParticleEnsemble::invertVelocities(){
    for (int i = 0; i < particleVector.size(); ++i){
        particleVector[i].setvx(-1.0*particleVector[i].getvx());
        particleVector[i].setvy(-1.0*particleVector[i].getvy());
        particleVector[i].setvz(-1.0*particleVector[i].getvz());
    }
    stepIncrement *= -1;
}

void ofParticleEnsemble::vv_propagatePositionsVelocities(vector <attractor> attractorVec) {

	int i, kk, nAttractors, nForceFieldObjects;
	float V(0.0), T(0.0), dt, pxnew, pynew, pznew, factor;

	float BoxWidth = ofGetWidth();
	float BoxHeight = ofGetHeight();

	float fx, fy, fz;
	glm::vec3 forces;

	//	if (EnsembleReinitializationFlag) {					// this flag permits on-the-fly particle reinitialization
	//		InitializeParticles();
	//		EnsembleReinitializationFlag = false;
	//	}

	//	if (NumberOfParticlesChangedFlag) {
	//		NumberOfParticlesChangedFlag = false;
	//	}

	nAttractors = int(attractorVec.size());
	dt = timestep;

	if (BerendsenThermostat) {                //  Berendsen Thermostat
		BerendsenVelocityRescaling();
	}

	CalculateKineticEnergiesAndTemperature();
	T=getTotalKineticEnergy();
	//  V=GetPotentialEnergy();                // get the potential energy - useless when  external field is time dependent
	//  TotalEnergy=T+V;                       // but helps testing that new forceFields conserve energy

	//this loop uses verlet scheme (VV) to propagate the positions forward one step
	for (i = 0; i < particleVector.size(); ++i) {
		particleVector[i].setLast_x(particleVector[i].getx());
		particleVector[i].setLast_y(particleVector[i].gety()); 
		particleVector[i].setLast_z(particleVector[i].getz());

		factor = 0.5 * dt * dt / mass;
		pxnew = particleVector[i].getx() + dt * particleVector[i].getvx() + factor * particleVector[i].getfx();
		pynew = particleVector[i].gety() + dt * particleVector[i].getvy() + factor * particleVector[i].getfy();
		pznew = particleVector[i].getz() + dt * particleVector[i].getvz() + factor * particleVector[i].getfz();

		if (pxnew > 0 && pxnew < ofGetWidth()) {  // this the standard VV code here
			particleVector[i].setx(pxnew);
		}
		else {  // this is to reflect off the walls; added by DRG to improve real time stability... not part of a standard VV
			particleVector[i].setx(particleVector[i].getLast_x());
			particleVector[i].setvx(-1.0 * particleVector[i].getvx());
		}
		if (pynew > 0 && pynew < ofGetHeight()) {
			particleVector[i].sety(pynew);
		}
		else {
			particleVector[i].sety(particleVector[i].getLast_y()); 
			particleVector[i].setvy(-1.0 * particleVector[i].getvy());
		}
		if (pznew > 0 && pznew < 3000) {
			particleVector[i].sety(pznew);
		}
		else {
			particleVector[i].setz(particleVector[i].getLast_z());
			particleVector[i].setvz(-1.0 * particleVector[i].getvz());
		}
	}

	for (i = 0; i < numberOfParticles; ++i) { // save the present forces to t-1 vectors
		particleVector[i].setLast_fx(particleVector[i].getfx()); 
		particleVector[i].setLast_fy(particleVector[i].getfy()); 
		particleVector[i].setLast_fz(particleVector[i].getfz());
	}

	ZeroXForces();			// zero out the force vectors & potential energy
	ZeroYForces();
	ZeroZForces();

	SetPotentialEnergy(0.0);

	/*
	for (kk = 0; kk < GetNumberOfForceFieldObjects(); ++kk) {				// calculate & set the forces at the new positions
		GetForceFieldObject(kk)->calculateForceField(this);
	}
	*/

	for (i = 0; i < particleVector.size(); ++i) {
		// zero out the forces for each particle
		fx = 0.0;
		fy = 0.0;
		fz = 0.0;

		for (kk = 0; kk < nAttractors; ++kk) {
			if (!ofGetKeyPressed('z')) {
				if (attractorVec[kk].getAttractorType() == "quadratic") {
                    forces = particleVector[i].calculateQuadraticForce(attractorVec[kk]);
				}
				else if (attractorVec[kk].getAttractorType() == "gaussian") {
                    forces = particleVector[i].calculateGaussianForce(attractorVec[kk]);
				}
			}
			else {
				forces = particleVector[i].get_frc();
			}
			fx = fx + forces.x;
			fy = fy + forces.y;
			fz = fz + forces.z;
		}
		particleVector[i].setfx(fx);
		particleVector[i].setfy(fy);
		particleVector[i].setfz(fz);
	}

	for (i = 0; i < particleVector.size(); ++i) {        // use Velocity Verlet scheme to propagate the velocities forward
		factor = dt * 0.5 / mass;
		particleVector[i].setvx(particleVector[i].getvx() + (particleVector[i].getfx() + particleVector[i].getLast_fx()) * factor);
		particleVector[i].setvy(particleVector[i].getvy() + (particleVector[i].getfy() + particleVector[i].getLast_fy()) * factor);
		particleVector[i].setvz(particleVector[i].getvz() + (particleVector[i].getfz() + particleVector[i].getLast_fz()) * factor);
	}

	stepNumber += stepIncrement;
}

// this function is for the simple Berendsen Thermostat
void ofParticleEnsemble::BerendsenVelocityRescaling() {

	float scaleFactor;
	int i;

	// this is an extra velocity rescaling measure to improve real-time stability... not part of Berendsen!!!!
	//    be sure that no single particle has a KE which differs from the average by 3 standard deviations (sigmas) 
	CalculateKineticEnergiesAndTemperature();
	float sigma(2.0);
	for (i = 0; i < numberOfParticles; ++i) {
		if ((particleVector[i].get_kineticEnergy() - averageKineticEnergy) > (sigma * SDKineticEnergy)) { // if ((GetParticleKineticEnergy(i) - AverageKineticEnergy) > (sigma * SDKineticEnergy)) {
			scaleFactor = (sigma * SDKineticEnergy) / (particleVector[i].get_kineticEnergy() - averageKineticEnergy); // (sigma * SDKineticEnergy) / (GetParticleKineticEnergy(i) - AverageKineticEnergy);
			particleVector[i].setvx(scaleFactor * particleVector[i].getvx()); // SetXParticleVelocity(i, scaleFactor * GetXParticleVelocity(i));
			particleVector[i].setvy(scaleFactor * particleVector[i].getvy()); //SetYParticleVelocity(i, scaleFactor * GetYParticleVelocity(i));
			particleVector[i].setvz(scaleFactor * particleVector[i].getvz());
		}
	}


	/* DRG - commenting out for now this stabilty measure 3 Jun 2022
	// again, a real-time stability measure... not part of Berendsen!!!!
	// re-initialize the system if the temperature gets crazy
	if (temperature > 1.0e8) {
		cout << " T = " << temperature << " scaleFactor " << scaleFactor << endl;
		EliminateParticleOverlap(BoxHeight, BoxWidth);    // adjust particle positions to eliminate overlap - this can cause the sim to freeze
		for (i = 0; i < GetNumberOfParticles(); ++i) {           //  then we zero out the forces and velocities 
			SetXParticleForce(i, 0.0);
			SetYParticleForce(i, 0.0);
			SetLastXParticlePosition(i, GetXParticlePosition(i));
			SetLastYParticlePosition(i, GetYParticlePosition(i));
		}
		CalculateKineticEnergiesAndTemperature();
	}
	*/

	// this code here is the bona fide Berendsen thermostat !!!!
	
	scaleFactor = sqrt(Tequilibrium / (BerendsenCoupling * temperature));
	if (scaleFactor != 1.0) {
		for (int i = 0; i < numberOfParticles; ++i) { //for (int i = 0; i < GetNumberOfParticles(); ++i) {						//rescale the velocities
			particleVector[i].setvx(scaleFactor * particleVector[i].getvx()); // SetXParticleVelocity(i, scaleFactor * GetXParticleVelocity(i));
			particleVector[i].setvy(scaleFactor * particleVector[i].getvy()); // SetYParticleVelocity(i, scaleFactor * GetYParticleVelocity(i));
			particleVector[i].setvz(scaleFactor * particleVector[i].getvz());
		}
	}
}

void ofParticleEnsemble::CalculateKineticEnergiesAndTemperature() {   // calculate the total, avg, & standard deviation of the kinetic energy

	float sum(0.0), KE(0.0);
	TotalKineticEnergy = 0.0;
	averageKineticEnergy = 0.0;
	SDKineticEnergy = 0.0;

	for (int i = 0; i < particleVector.size(); ++i) {
		float KE = 0.5 * particleVector[i].get_mass() * (pow(particleVector[i].getvx(), 2.0) + pow(particleVector[i].getvy(), 2.0) + pow(particleVector[i].getvz(), 2.0)); 
		particleVector[i].set_kineticEnergy(KE); 
		TotalKineticEnergy += KE;
	}

	averageKineticEnergy = TotalKineticEnergy / numberOfParticles;
	temperature = TotalKineticEnergy / (numberOfParticles * kb);
	for (int i = 0; i < numberOfParticles; ++i) { sum += pow((particleVector[i].get_kineticEnergy() - averageKineticEnergy), 2.0); }
	SDKineticEnergy = sqrt(sum / numberOfParticles);
 
}


void ofParticleEnsemble::draw() {

	glm::vec3 pos;
	float scale;

	for (unsigned int i = 0; i < particleVector.size(); i++) {
		pos = particleVector[i].get_pos();
		scale = particleVector[i].get_scale();
		if (!ofGetKeyPressed('z')){ ofSetColor(103, 160, 237); }
		else {ofSetColor(103,120,200);}
		ofDrawCircle(pos.x, pos.y, scale * 4.0);
	}
}
