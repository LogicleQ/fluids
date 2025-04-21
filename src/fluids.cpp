#include "fluids.hpp"

bool FluidSim::m_created = false;

FluidSim::FluidSim (FluidOptions options)
	: m_options {options}
{

	if (m_created)
	{
		throw 1;
	}

	m_created = true;

	for (int i = 0; i < options.ptclSides; ++i)
	{
		m_indices.push_back(0);
		m_indices.push_back(i+1);
		m_indices.push_back((i + 1) % options.ptclSides + 1);
	}

	SDL_Init(SDL_INIT_VIDEO);

}


void FluidSim::populate (std::vector<SDL_FPoint> ptcls)
{
	m_ptcls = ptcls;
}


void FluidSim::run ()
{
	m_window = SDL_CreateWindow("Fluids", m_options.winWidth, m_options.winHeight, 0);

	m_renderer = SDL_CreateRenderer(m_window, 0);


	bool running = true;
	while (running)
	{

		render();


		SDL_Event e;
		while(SDL_PollEvent(&e))
		{

			switch(e.type)
			{
				case SDL_EVENT_QUIT:
					running = false;
					break;
			}
		}


	}
}
