#ifndef FLUIDS_HPP
#define FLUIDS_HPP

#include <cstdint>
#include <vector>

#include <SDL3/SDL.h>

struct FluidOptions
{
	uint32_t winWidth = 800;
	uint32_t winHeight = 600;

	//particle rendering properties
	float ptclRadius = 10;
	uint16_t ptclSides = 3;
};

class FluidSim
{
	public:
		FluidSim (FluidOptions options);

		void populate (std::vector<SDL_FPoint> ptcls);
		void run ();

	private:
		void render ();
		void drawParticle (float x, float y, SDL_FColor color);

		static bool m_created;

		FluidOptions m_options;

		SDL_Window* m_window;
		SDL_Renderer* m_renderer;

		std::vector<int> m_indices;

		std::vector<SDL_FPoint> m_ptcls;
};


#endif
