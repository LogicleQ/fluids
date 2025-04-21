#include <iostream>

#include "fluids.hpp"

int main ()
{

	FluidOptions options
	{
		.ptclRadius = 7,
		.ptclSides = 10
	};

	FluidSim fs1(1000, 800, options);

	fs1.run();


}
