#pragma once
#include "ofMain.h"
#include "ofParticle.h"
#include "attractor.h"

class ofParticle;

class ofParticleEnsemble{

    public:
		ofParticleEnsemble(int n, float dt, float temp);
		~ofParticleEnsemble();
		void setRandomPositionsAndVelocities(int n);
		void setRadialPositionsAndVelocities(vector <attractor> attractorVec);
		void of_propagatePositionsVelocities(vector <glm::vec3> attractPoints);
		void vv_propagatePositionsVelocities(vector <attractor> attractorVec);
		void BerendsenVelocityRescaling();
		void CalculateKineticEnergiesAndTemperature();

        float getTotalKineticEnergy() { return TotalKineticEnergy; }
		int get_numberOfParticles() {return numberOfParticles;};
        int getStepCount(){return stepNumber;};
    
        void resetStepCount(){stepNumber = 0;}

		void ZeroXForces() { for (int i = 0; i < numberOfParticles; ++i) { particleVector[i].setfx(0.0); } }
		void ZeroYForces() { for (int i = 0; i < numberOfParticles; ++i) { particleVector[i].setfy(0.0); } }
		void ZeroZForces() { for (int i = 0; i < numberOfParticles; ++i) { particleVector[i].setfz(0.0); } }

		void SetPotentialEnergy(float PE) { TotalPotentialEnergy = PE; };

        float gentlyReverseTime();
        float gentlyReverseTimeWithCos();
    
		void draw();
    
        void set_timeReversalInProgress(bool flag){timeReversalInProgress = flag;};
        bool get_timeReversalInProgress(){return timeReversalInProgress;};

        void set_Tequilibrium(float temp){Tequilibrium = temp;}
    
	private:
		vector <ofParticle> particleVector;
		int	    numberOfParticles;
		int	    stepNumber;
        int     stepIncrement;
		float   kb, BerendsenCoupling, Tequilibrium;
		float   temperature, scaleFactor, InitialKE;
		bool    BerendsenThermostat;
		float	TotalKineticEnergy;
		float	TotalPotentialEnergy;
		float	averageKineticEnergy;
		float	SDKineticEnergy;
		float	timestep;
        float   last_timeStep;
		float	mass;
        bool    timeReversalInProgress;
        int     timeReversalStepCounter;
        int     nTimeReversalSteps;
        int     nTimeReversalCalls;
        float   timeStepReduction;
};
