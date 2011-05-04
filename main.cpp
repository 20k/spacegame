#include "common.h"
#include "space/planet.h"
#include "space/moon.h"
#include "engine/initializers.h"

#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

int main(int argc, char** argv)
{
	Engine::g_Initializers->Add("Initializing Planets...", &Planets_Initialize);
	Engine::g_Initializers->Add("Initializing Moons...", &Moons_Initialize);
	Engine::g_Initializers->Initialize();
	
	sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Planets");
	App.SetFramerateLimit(60);
	
	Planet TestPlanet(PlanetType_Habbitable, Vector2<double>(400 - 256 * 0.5, 300 - 256 * 0.5));
	
    while (App.IsOpened())
    {
        // Process events
        sf::Event Event;
        while (App.GetEvent(Event))
        {
            if (Event.Type == sf::Event::Closed)
                App.Close();
        }
        
        App.Clear();
        
        // TODO: Draw and update stuff
		TestPlanet.Update(1.0f);
		TestPlanet.Draw(App);

        App.Display();
    }

    return 0;
}

