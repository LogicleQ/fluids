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


#define time_ms() (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count())

void FluidSim::run ()
{

	uint64_t prevLogTime = time_ms();
	uint64_t prevZeroTime = time_ms();

	m_window = SDL_CreateWindow("Fluids", m_options.winWidth, m_options.winHeight, 0);

	m_renderer = SDL_CreateRenderer(m_window, 0);


	bool running = true;
	while (running)
	{

		move();
		accel();

		render();



		const uint64_t newTime = time_ms();


		auto &countdowns = m_options.zeroVelCountdowns;
		if (countdowns.size() > 0 && newTime >= prevZeroTime + (uint64_t) (countdowns.back() * 1000))
		{
			zeroVels();
			prevZeroTime = newTime;

			countdowns.pop_back();
		}


		if (m_options.logEnergy)
		{

			if (newTime >= prevLogTime + 1000)
			{
				std::cout << "Total KE: " << calcTotalKE() << ", Avg KE: " << calcAvgKE() << std::endl;
				prevLogTime = newTime;
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
