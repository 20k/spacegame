#include "common.h"
#include "space/planet.h"
#include "space/moon.h"
#include "engine/camera.h"
#include "engine/initializers.h"

#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

void TestPoint(int X, int Y)
{
	Vector2<double> spos(X, Y);
	Vector2<double> fpos;
	fpos=gCamera::PixelsToPoint(spos);
}

int main(int argc, char** argv)
{
	Engine::g_Initializers->Add("Initializing Planets...", &Planets_Initialize);
	Engine::g_Initializers->Add("Initializing Moons...", &Moons_Initialize);
	Engine::g_Initializers->Initialize();

	gCamera::SetWindowSize(800, 600);
	gCamera::SetCameraPosition(Vector2<double>(0, 0));
	Vector2<double> egpos;
	egpos=gCamera::PointToPixels(Vector2<double>(-1,-1));
	
	sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Planets");
	App.SetFramerateLimit(60);
	
	Planet TestPlanet(PlanetType_Habbitable, Vector2<double>(0, 0));
	
    while (App.IsOpened())
    {
        // Process events
        sf::Event Event;
        while (App.GetEvent(Event))
        {
            if (Event.Type == sf::Event::Closed)
                App.Close();
			if (Event.Type == sf::Event::MouseButtonReleased)
				TestPoint(Event.MouseButton.X, Event.MouseButton.Y);
        }
        
        App.Clear();
        
        // TODO: Draw and update stuff
		TestPlanet.Update(1.0f);
		TestPlanet.Draw(App);

        App.Display();
    }

    return 0;
}

