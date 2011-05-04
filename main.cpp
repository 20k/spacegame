#include <SFML/System.hpp>
#include <iostream>

#include "common.h"
#include "space/planet.h"
#include "engine/initializers.h"

int main(int argc, char** argv)
{
	Engine::g_Initializers.Add("Initializing Planets...", Planets_Initialize);
	
	#ifdef PLATFORM_WINDOWS
		std::cout << "Hello, Windows." << std::endl;
	#else
		#ifdef PLATFORM_LINUX
			std::cout << "Hello, Linux." << std::endl;
		#endif
	#endif
	
	Engine::g_Initializers.Initialize();

	#ifdef PLATFORM_WINDOWS
		std::cout << "Press enter to continue" << std::endl;
		std::cin.ignore(1000, '\n');
	#endif

    return 0;
}

