#include "parse.hpp"

#include <iostream>
#include <vector>


std::vector<std::string> split (std::string str)
{

	const std::string delimiter = " ";

	std::vector<std::string> tokens;

	while (true)
	{
		size_t delInd = str.find(delimiter);

		if (delInd == std::string::npos)
		{
			tokens.push_back(str);
			break;
		}

		std::string token = str.substr(0, delInd);
		tokens.push_back(token);

		str = str.erase(0, delInd + delimiter.size());
	}

	return tokens;

}



void parseOptions (FluidOptions &options)
{
	std::string line;
	while (std::getline(std::cin, line))
	{
		auto tokens = split(line);


		if (tokens.size() < 1) continue;
		std::string cmd = tokens.at(0);


		if (cmd.substr(0, 2) == "//") continue;
		if (cmd == "") continue;


		std::string arg = "";
		if (tokens.size() >= 2)
		{
			arg = tokens.at(1);
		}




		if (cmd == "end")
		{
			break;
		}
		else if (cmd == "window_width")
		{
			options.winWidth = std::stoi(arg);
		}
		else if (cmd == "window_height")
		{
			options.winHeight = std::stoi(arg);
		}
		else if (cmd == "particle_visual_radius")
		{
			options.ptclVisualRadius = std::stof(arg);
		}
		else if (cmd == "particle_sides")
		{
			options.ptclSides = std::stoi(arg);
		}
		else if (cmd == "log_energy")
		{
			if (arg == "yes" || arg == "true")
			{
				options.logEnergy = true;
			}
			else if (arg == "no" || arg == "false")
			{
				options.logEnergy = false;
			}
		}
		else if (cmd == "zero_velocity_countdowns")
		{
			size_t num = tokens.size() - 1;


			for (int i = num; i > 0; --i)
			{
				options.zeroVelCountdowns.push_back( stof(tokens.at(i)) );
			}

		}
		else if (cmd == "simulation_speed")
		{
			options.simSpeed = stof(arg);
		}
		else if (cmd == "particle_physical_radius")
		{
			options.ptclPhysicalRadius = stof(arg);
		}
		else if (cmd == "particle_far_force_constant")
		{
			options.ptclFarForceConstant = stof(arg);
		}
		else if (cmd == "particle_far_force_asymptote")
		{
			options.ptclFarForceAsymp = stof(arg);
		}
		else if (cmd == "particle_near_force_constant")
		{
			options.ptclNearForceConstant = stof(arg);
		}
		else if (cmd == "particle_force_limit")
		{
			options.ptclForceLimit = stof(arg);
		}
		else if (cmd == "wall_elasticity")
		{
			options.wallElasticity = stof(arg);
		}
		else if (cmd == "friction_force_constant")
		{
			options.frictionForceConstant = stof(arg);
		} 
		else if (cmd == "gravity_force_constant")
		{
			options.gravityForceConstant = stof(arg);
		}
		else if (cmd == "ambient_force_center")
		{
			options.ambientForceCenter = stof(arg);
		}
		else if (cmd == "ambient_force_radius")
		{
			options.ambientForceRadius = stof(arg);
		}
		else if (cmd == "ambient_force_height")
		{
			options.ambientForceHeight = stof(arg);
		}
		else if (cmd == "ambient_force_constant")
		{
			options.ambientForceConstant = stof(arg);
		}
		else 
		{
			std::cout << "Unknown option: '" << cmd << "'" << std::endl;
		}



	}
}
