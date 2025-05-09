#include "fluids.hpp"

#include <vector>
#include <cmath>

void FluidSim::render ()
{
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_renderer);

	for (size_t i = 0; i < m_ptcls.size(); ++i)
	{
		Particle &ptcl = m_ptcls[i];

		double speed = sqrt(ptcl.velX * ptcl.velX + ptcl.velY * ptcl.velY);


		float r = 0.04 * speed;
		float g = 0.4 + 0.1 * speed - 0.002 * speed * speed;
		float b = 1 - 0.02 * speed;

		drawParticle(ptcl, {r, g, b, 1});
	}

	SDL_RenderPresent(m_renderer);
}



#define PI (3.14159265358979)

void FluidSim::drawParticle (Particle ptcl, SDL_FColor color)
{
	std::vector<SDL_Vertex> vertices;
	std::vector<int> indices;

	SDL_Vertex center
	{
		.position = {ptcl.posX, ptcl.posY},
		.color = color
	};

	vertices.push_back(center);


	for (int i = 0; i < m_options.ptclSides; ++i)
	{
		float theta = 2 * PI * i / m_options.ptclSides;

		float tempX = ptcl.posX + m_options.ptclVisualRadius * cos(theta);
		float tempY = ptcl.posY + m_options.ptclVisualRadius * sin(theta);

		SDL_Vertex vertex
		{
			.position = {tempX, tempY},
			.color = color
		};

		vertices.push_back(vertex);

	}


	SDL_RenderGeometry (m_renderer, NULL, &vertices[0], vertices.size(), &m_indices[0], m_indices.size());

}



