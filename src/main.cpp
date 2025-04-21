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
		.winHeight = 800,

		.ptclRadius = 7,
		.ptclSides = 10
	};


	FluidSim fs(options);



	std::vector<SDL_FPoint> ptcls;

	//populate with random positions
	srand(time(0));

	for (int i = 0; i < 20; ++i)
	{
		float x = randFloat() * options.winWidth;
		float y = randFloat() * options.winHeight;

		ptcls.push_back({x, y});
	}



	fs.populate(ptcls);
	fs.run();


}
