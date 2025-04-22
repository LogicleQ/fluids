#include <chrono>
#include <cstdlib>
#include <vector>

#include "fluids.hpp"

float randFloat ()
{
	return rand() / (float) RAND_MAX;
}

int main ()
{

	FluidOptions options
	{
		.winWidth = 700,
		.winHeight = 700,

		.ptclRadius = 4,
		.ptclSides = 10,

		.simSpeed = 0.2,
		.ptclFarForceConstant = -80,
		.farForceAsymp = 10,
		.ptclNearForceConstant = 70,
		.ptclForceLimit = 30,
		.wallElasticity = 0.8,
		.frictionConstant = 0.012,
		.gravityConstant = -0.08
	};


	FluidSim fs(options);



	std::vector<Particle> ptcls;

	//populate with random positions
	srand(time(0));

	for (int i = 0; i < 1000; ++i)
	{
		float x = randFloat() * options.winWidth;
		float y = randFloat() * options.winHeight;

		float vx = randFloat() * 2 - 1;
		float vy = randFloat() * 2 - 1;

		Particle ptcl
		{
			.posX = x,
			.posY = y,

			.velX = 0,
			.velY = 0
		};

		ptcls.push_back(ptcl);
	}



	fs.populate(ptcls);
	fs.run();


}
