#include "common.h"
#include "space/planet.h"
#include "space/moon.h"
#include "space/sun.h"
#include "engine/camera.h"
#include "engine/initializers.h"

#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

const sf::Input *g_Input;

void TestPoint(int X, int Y)
{
	Vector2<double> spos(X, Y);
	Vector2<double> fpos;
	fpos=gCamera::PixelsToPoint(spos);
}


//This function zooms towards the mouse or out (from center)
//Not sure where this should go so I'll leave it here for now.
void TestZoom(int Delta)
{
	gCamera::AddCameraZoom(Delta*0.2);
	if(Delta<0) return;
	Vector2<double> mpoint;
	{
		int mx, my;
		mx=g_Input->GetMouseX();
		my=g_Input->GetMouseY();
		mpoint=gCamera::PixelsToPoint(Vector2<double>(mx, my));
	}
	Vector2<double> cpoint=gCamera::GetCameraPosition();
	Vector2<double> dpoint=(mpoint-cpoint)*0.2;
	gCamera::SetCameraPosition(cpoint+dpoint);
}

int main(int argc, char** argv)
{
	Engine::g_Initializers->Add("Initializing Planets...", &Planets_Initialize);
	Engine::g_Initializers->Add("Initializing Moons...", &Moons_Initialize);
	Engine::g_Initializers->Initialize();

	gCamera::SetWindowSize(800, 600);
	gCamera::SetCameraPosition(Vector2<double>(0, 0));
	
	sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Planets");
	App.SetFramerateLimit(60);
	
	//Planet TestPlanet(PlanetType_Habbitable, Vector2<double>(0, 0));
	Sun TestSun(SunType_MainSequence, Vector2<double>(0,0), NULL);
	g_Input=&App.GetInput();
	
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
			if (Event.Type == sf::Event::MouseWheelMoved)
				TestZoom(Event.MouseWheel.Delta);
        }
        
        App.Clear();
        
        // TODO: Draw and update stuff
		TestSun.Update(1.0f);
		TestSun.Draw(App);

        App.Display();
    }

    return 0;
}

