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
		.winWidth = 1000,
		.winHeight = 1000,

		.ptclRadius = 4,
		.ptclSides = 10,

		.simSpeed = 0.09,
		.ptclFarForceConstant = -90,
		.farForceAsymp = 10,
		.ptclNearForceConstant = 70,
		.wallForceConstant = 50,
		.frictionConstant = 0.02,
		.gravityConstant = -0.04 
	};


	FluidSim fs(options);



	std::vector<Particle> ptcls;

	//populate with random positions
	srand(time(0));

	for (int i = 0; i < 600; ++i)
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
