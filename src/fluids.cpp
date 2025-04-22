#include "fluids.hpp"

#include <chrono>
#include <iostream>


bool FluidSim::m_created = false;

FluidSim::FluidSim (FluidOptions options)
	: m_options {options},
		m_ambientForceActive {false},
		m_trueSpeed {options.simSpeed}
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


void FluidSim::populate (std::vector<Particle> ptcls)
{
	m_ptcls = ptcls;
}



void FluidSim::run ()
{

	auto oldTime = time(0);

	m_window = SDL_CreateWindow("Fluids", m_options.winWidth, m_options.winHeight, 0);

	m_renderer = SDL_CreateRenderer(m_window, 0);


	bool running = true;
	while (running)
	{

		render();


		if (m_options.logEnergy)
		{
			auto newTime = time(0);

			if (newTime > oldTime)
			{
				std::cout << "Total KE: " << calcTotalKE() << ", Avg KE: " << calcAvgKE() << std::endl;
				oldTime = newTime;
			}
		}


		SDL_Event e;
		while (SDL_PollEvent(&e))
		{

			switch (e.type)
			{

				case SDL_EVENT_QUIT:
					running = false;
					break;

			}

			checkKeystrokes (e);

		}


	}
}


void FluidSim::zeroVels ()
{

	for (size_t i = 0; i < m_ptcls.size(); ++i)
	{
		Particle &ptcl = m_ptcls[i];

		ptcl.velX = 0;
		ptcl.velY = 0;
	}

}
