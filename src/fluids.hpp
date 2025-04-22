#ifndef FLUIDS_HPP
#define FLUIDS_HPP

#include <cstdint>
#include <vector>

#include <SDL3/SDL.h>


struct Particle
{
	float posX = 0;
	float posY = 0;

	float velX = 0;
	float velY = 0;
};



struct FluidOptions
{
	//window dimensions
	uint32_t winWidth = 800;
	uint32_t winHeight = 800;

	//particle rendering properties
	float ptclRadius = 4; //in pixels
	uint16_t ptclSides = 10;


	//info
	bool logEnergy = true;


	//simulation properties
	float simSpeed = 0.2;

	float ptclFarForceConstant = -120;
	float ptclFarForceAsymp = 10;
	float ptclNearForceConstant = 100;
	float ptclForceLimit = 30;


	float wallElasticity = 0.85;
	float frictionForceConstant = 0.01;
	float gravityForceConstant = 0.1;

	float ambientForceCenter = 0; //0 is center of window; -1 and 1 are left/right walls
	float ambientForceRadius = 0.1; //1 means the radius is half of winWidth
	float ambientForceHeight = 0.1; //1 is winHeight
	float ambientForceConstant = -0.4;

};

class FluidSim
{
	public:
		FluidSim (FluidOptions options);

		void populate (std::vector<Particle> ptcls);
		void run ();

		void zeroVels ();

		float calcTotalKE ();
		float calcAvgKE ();


	private:
		void render ();
		void drawParticle (Particle ptcl, SDL_FColor color);

		void move ();
		void accel ();

		void interParticleForce (Particle &self, Particle &other);
		void wallForce (Particle &self);
		void frictionForce (Particle &self);
		void gravityForce (Particle &self);
		void ambientForce (Particle &self);


		void checkKeystrokes (SDL_Event &e);


		static bool m_created;

		FluidOptions m_options;

		SDL_Window* m_window;
		SDL_Renderer* m_renderer;

		std::vector<int> m_indices;

		std::vector<Particle> m_ptcls;

		float m_trueSpeed;

		bool m_ambientForceActive;
};


#endif
