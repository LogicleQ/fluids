#include "fluids.hpp"

#include <cmath>

float FluidSim::calcTotalKE ()
{

	float totalKE = 0;

	for (int i = 0; i < m_ptcls.size(); ++i)
	{
		Particle &ptcl = m_ptcls[i];

		float speed = sqrt(ptcl.velX * ptcl.velX + ptcl.velY * ptcl.velY);
		float KE = 0.5 * speed * speed;

		totalKE += KE;
	}

	return totalKE;

}

float FluidSim::calcAvgKE ()
{
	return calcTotalKE() / m_ptcls.size();
}
