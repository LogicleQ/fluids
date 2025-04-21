#ifndef FLUIDS_HPP
#define FLUIDS_HPP

#include <cstdint>
#include <vector>

#include <SDL3/SDL.h>

struct FluidOptions
{
	//particle rendering properties
	float ptclRadius = 10;
	uint16_t ptclSides = 3;
};

class FluidSim
{
	public:
		FluidSim (uint32_t width, uint32_t height, FluidOptions options);

		void run ();

	private:
		void render ();
		void drawParticle (float x, float y, SDL_FColor color);

		static bool m_created;

		uint32_t m_width;
		uint32_t m_height;

		FluidOptions m_options;

		SDL_Window* m_window;
		SDL_Renderer* m_renderer;

		std::vector<int> m_indices;
};


#endif
