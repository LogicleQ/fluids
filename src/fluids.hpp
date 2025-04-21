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
	uint32_t winHeight = 600;

	//particle rendering properties
	float ptclRadius = 10;
	uint16_t ptclSides = 3;

	//simulation properties
	float simSpeed = 0.01;
	float ptclForceConstant = 10;
	float wallForceConstant = 10;
	float frictionConstant = 0.1;

};

class FluidSim
{
	public:
		FluidSim (FluidOptions options);

		void populate (std::vector<Particle> ptcls);
		void run ();

	private:
		void render ();
		void drawParticle (Particle ptcl, SDL_FColor color);

		void move ();
		void accel ();

		void interParticleForce (Particle &self, Particle &other);
		void wallForce (Particle &self);
		void frictionForce (Particle &self);

		static bool m_created;

		FluidOptions m_options;

		SDL_Window* m_window;
		SDL_Renderer* m_renderer;

		std::vector<int> m_indices;

		std::vector<Particle> m_ptcls;
};


#endif
