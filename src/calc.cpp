#include "fluids.hpp"

#include <cmath>

void FluidSim::move ()
{

	for (size_t i = 0; i < m_ptcls.size(); ++i)
	{
		Particle &self = m_ptcls[i];

		self.posX += self.velX * m_options.simSpeed;
		self.posY += self.velY * m_options.simSpeed;
	}

}


void FluidSim::accel ()
{
	for (size_t i = 0; i < m_ptcls.size(); ++i)
	{
		Particle &self = m_ptcls[i];

		for (size_t j = 0; j < m_ptcls.size(); ++j)
		{
			if (i == j) continue;

			Particle &other = m_ptcls[j];

			interParticleForce(self, other);

		}


		gravityForce(self);

		//these two should be calculated last
		wallForce(self);
		frictionForce(self);

	}
}


void FluidSim::interParticleForce (Particle &self, Particle &other)
{

	float dx = self.posX - other.posX;
	float dy = self.posY - other.posY;

	float dist = sqrt(dx * dx + dy * dy);

	float normDx = dx / dist;
	float normDy = dy / dist;


	float asymp = m_options.farForceAsymp;
	float accelMag = m_options.ptclFarForceConstant / (dist + asymp) / (dist + asymp);
	accelMag += m_options.ptclNearForceConstant / dist / dist;


	if (accelMag > m_options.ptclForceLimit) accelMag = m_options.ptclForceLimit;

	float accelX = accelMag * normDx;
	float accelY = accelMag * normDy;

	self.velX += accelX * m_options.simSpeed;
	self.velY += accelY * m_options.simSpeed;

}

/*
void FluidSim::wallForce (Particle &self)
{

	float distFromLeft = self.posX;
	float distFromRight = m_options.winWidth - self.posX;

	float distFromTop = self.posY;
	float distFromBottom = m_options.winHeight - self.posY;

	float forceConstant = m_options.wallForceConstant;

	auto forceMag = [forceConstant] (float dist) -> float
	{
		if (dist < 0)
		{
			return forceConstant / 5 / 5;
		}
		else
		{
			return forceConstant / (dist + 5) / (dist + 5);
		}
	};

	float accelX = forceMag(distFromLeft) - forceMag(distFromRight);
	float accelY = forceMag(distFromTop) - forceMag(distFromBottom);

	self.velX += accelX * m_options.simSpeed;
	self.velY += accelY * m_options.simSpeed;

}
*/


void FluidSim::wallForce (Particle &self)
{

	float distFromLeft = self.posX;
	float distFromRight = m_options.winWidth - self.posX;

	float distFromTop = self.posY;
	float distFromBottom = m_options.winHeight - self.posY;


	if (distFromLeft < m_options.ptclRadius)
	{
		self.velX = m_options.wallElasticity * fabs(self.velX);
	}
	else if (distFromRight < m_options.ptclRadius)
	{
		self.velX = m_options.wallElasticity * -fabs(self.velX);
	}


	if (distFromTop < m_options.ptclRadius)
	{
		self.velY = m_options.wallElasticity * fabs(self.velY);
	}
	else if (distFromBottom < m_options.ptclRadius)
	{
		self.velY = m_options.wallElasticity * -fabs(self.velY);
	}

}


void FluidSim::frictionForce (Particle &self)
{

	float ptclSpeed = sqrt(self.velX * self.velX + self.velY * self.velY);

	float normVelX = self.velX / ptclSpeed;
	float normVelY = self.velY / ptclSpeed;

	float frictionX = normVelX * -m_options.frictionConstant;
	float frictionY = normVelY * -m_options.frictionConstant;

	if (fabs(self.velX) >= fabs(frictionX * m_options.simSpeed))
	{
		self.velX += frictionX * m_options.simSpeed;
	}

	if (fabs(self.velY) >= fabs(frictionY * m_options.simSpeed))
	{
		self.velY += frictionY * m_options.simSpeed;
	}

}


void FluidSim::gravityForce (Particle &self)
{
	self.velY -= m_options.gravityConstant * m_options.simSpeed;
}
