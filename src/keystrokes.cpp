#include "fluids.hpp"

void FluidSim::checkKeystrokes (SDL_Event &e)
{

	if (e.type == SDL_EVENT_KEY_DOWN)
	{
		switch (e.key.key)
		{

			case SDLK_A:
				m_ambientForceActive = !m_ambientForceActive;
				break;

			case SDLK_Z:
				zeroVels();
				break;

			case SDLK_SPACE:
				m_trueSpeed = 2 * m_options.simSpeed;
				break;

		}
	}

	else if (e.type == SDL_EVENT_KEY_UP)
	{
		switch (e.key.key)
		{
			case SDLK_SPACE:
				m_trueSpeed = m_options.simSpeed;
				break;
		}
	}

}
