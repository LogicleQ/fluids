#include "fluids.hpp"

#include <vector>
#include <cmath>

void FluidSim::render ()
{
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_renderer);

	for (size_t i = 0; i < m_ptcls.size(); ++i)
	{
		drawParticle(m_ptcls[i].x, m_ptcls[i].y, {0, 0.4, 1, 1});
	}

	SDL_RenderPresent(m_renderer);
}





#define PI (3.14159265358979)

void FluidSim::drawParticle (float x, float y, SDL_FColor color)
{
	std::vector<SDL_Vertex> vertices;
	std::vector<int> indices;

	SDL_Vertex center
	{
		.position = {x, y},
		.color = color
	};

	vertices.push_back(center);


	for (int i = 0; i < m_options.ptclSides; ++i)
	{
		float theta = 2 * PI * i / m_options.ptclSides;

		float tempX = x + m_options.ptclRadius * cos(theta);
		float tempY = y + m_options.ptclRadius * sin(theta);

		SDL_Vertex vertex
		{
			.position = {tempX, tempY},
			.color = color
		};

		vertices.push_back(vertex);

	}


	SDL_RenderGeometry (m_renderer, NULL, &vertices[0], vertices.size(), &m_indices[0], m_indices.size());

}
