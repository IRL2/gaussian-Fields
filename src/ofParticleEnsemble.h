#pragma once
#include "ofMain.h"
#include "ofParticle.h"
#include "attractor.h"

class ofParticle;

class ofParticleEnsemble{

    public:
		ofParticleEnsemble(int n);
		~ofParticleEnsemble();
		void setRandomPositionsAndVelocities(int n);
		void setNonRandomPositionsAndVelocities(vector <attractor> attractorVec);
		void of_propagatePositionsVelocities(vector <glm::vec3> attractPoints);
		void vv_propagatePositionsVelocities(vector <attractor> attractorVec);
		void BerendsenVelocityRescaling();
		void CalculateKineticEnergiesAndTemperature();
		float getTotalKineticEnergy() { return TotalKineticEnergy; }
		int get_numberOfParticles() {return numberOfParticles;};

		void ZeroXForces() { for (int i = 0; i < numberOfParticles; ++i) { particleVector[i].setfx(0.0); } }
		void ZeroYForces() { for (int i = 0; i < numberOfParticles; ++i) { particleVector[i].setfy(0.0); } }
		void ZeroZForces() { for (int i = 0; i < numberOfParticles; ++i) { particleVector[i].setfz(0.0); } }

		void SetPotentialEnergy(float PE) { TotalPotentialEnergy = PE; };

        void invertVelocities();
    
		void draw();

	private:
		vector <ofParticle> particleVector;
		int	    numberOfParticles;
		int	    step;
		float  kb, BerendsenCoupling, Tequilibrium;
		float  temperature, scaleFactor, InitialKE;
		bool    BerendsenThermostat;
		float	TotalKineticEnergy;
		float	TotalPotentialEnergy;
		float	averageKineticEnergy;
		float	SDKineticEnergy;
		float	timestep;
		float	mass;

};
