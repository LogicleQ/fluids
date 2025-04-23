#include <chrono>
#include <cstdlib>
#include <vector>

#include "fluids.hpp"
#include "parse.hpp"

float randFloat ()
{
	return rand() / (float) RAND_MAX;
}

int main ()
{

	FluidOptions options
	{
		.winWidth = 800,
		.winHeight = 800,

		.ptclVisualRadius = 4, //in pixels
		.ptclSides = 10,

		.logEnergy = true,

		.simSpeed = 0.2,

		.ptclPhysicalRadius = 4,

		.ptclFarForceConstant = -120,
		.ptclFarForceAsymp = 10,
		.ptclNearForceConstant = 100,
		.ptclForceLimit = 30,

		.wallElasticity = 0.85,
		.frictionForceConstant = 0.01,
		.gravityForceConstant = 0.1,

		.ambientForceCenter = 0, //0 is center of window; -1 and 1 are left/right walls
		.ambientForceRadius = 0.1, //1 means the radius is half of winWidth
		.ambientForceHeight = 0.1, //1 is winHeight
		.ambientForceConstant = -0.4
	};

	parseOptions(options);


	FluidSim fs(options);


	std::vector<Particle> ptcls;

	//populate with random positions
	srand(time(0));

	for (int i = 0; i < 1400; ++i)
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
