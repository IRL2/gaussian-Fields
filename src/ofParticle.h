#pragma once
#include "ofMain.h"
#include "attractor.h"

class ofParticle{

	public:
		ofParticle();
		~ofParticle();
		
		float getx() {return pos.x;};
		float gety() {return pos.y;};
		float getz() {return pos.z;};
	    
		void setx(float x) { pos.x = x; };
		void sety(float y) { pos.y = y; };
		void setz(float z) { pos.z = z; };

		float getLast_x() { return last_pos.x; };
		float getLast_y() { return last_pos.y; };
		float getLast_z() { return last_pos.z; };

		void setLast_x(float x) { last_pos.x = x; };
		void setLast_y(float y) { last_pos.y = y; };
		void setLast_z(float z) { last_pos.z = z; };

		float getvx() { return vel.x; };
		float getvy() { return vel.y; };
		float getvz() { return vel.z; };

		void setvx(float vx) { vel.x = vx; };
		void setvy(float vy) { vel.y = vy; };
		void setvz(float vz) { vel.z = vz; };

		float getfx() { return frc.x; };
		float getfy() { return frc.y; };
		float getfz() { return frc.z; };

		void setfx(float fx) { frc.x = fx; };
		void setfy(float fy) { frc.y = fy; };
		void setfz(float fz) { frc.z = fz; };

		float getLast_fx() { return last_frc.x; };
		float getLast_fy() { return last_frc.y; };
		float getLast_fz() { return last_frc.z; };

		void setLast_fx(float x) { last_frc.x = x; };
		void setLast_fy(float y) { last_frc.y = y; };
		void setLast_fz(float z) { last_frc.z = z; };

		float get_drag() { return drag; };
		void set_drag(float val) { drag = val; };

		float get_scale() { return scale; };
		void set_scale(float val) { scale = val; };

		float get_uniqueVal() { return uniqueVal; };
		void set_uniqueVal(float val) { uniqueVal = val; };

		float get_mass() { return mass;};
		void set_mass(float val) {mass = val;};

		float get_kineticEnergy() { return kineticEnergy; };
		void set_kineticEnergy(float val) { kineticEnergy = val; };

		glm::vec3 get_pos() { return pos; };
		void set_pos(glm::vec3 positions) { pos = positions; };

		glm::vec3 get_vel() { return vel; };
		void set_vel(glm::vec3 velocities) { vel = velocities; };

		glm::vec3 get_frc() { return frc; };
		void set_frc(glm::vec3 forces) { frc = forces; };
 
        glm::vec3 calculateQuadraticForce(attractor attractorObject);
        glm::vec3 calculateGaussianForce(attractor attractorObject);

		float exp256(float x) {
			x = 1.0 + x / 256.0;
			x *= x; x *= x; x *= x; x *= x;
			x *= x; x *= x; x *= x; x *= x;
			return x;
		}
    
        void setColor(ofColor colorVal){particleColor = colorVal;};
        ofColor getColor(){return particleColor;}

    private:
		glm::vec3 pos;
		glm::vec3 vel;
		glm::vec3 frc;
		
		glm::vec3 last_pos;
		glm::vec3 last_vel;
		glm::vec3 last_frc;

		float drag; 
		float uniqueVal;
		float scale;
		float mass;
		float kineticEnergy;
		
        ofColor particleColor;
};
