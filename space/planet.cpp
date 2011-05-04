#include "space/planet.h"
#include "engine/imagemanager.h"
#include "engine/initializers.h"

#include <iostream>

Engine::Resource* HabbitablePlanetImg = 0;

Planet::Planet(const PlanetType Type, const Vector2<double>& Position, const double Radius)
	: Body(Position, Radius), m_Type(Type)
{
	
}

Planet::~Planet()
{
	
}

void Planet::Update(const Timestep Delta)
{
	Body::Update(Delta);	
}

void Planet::Draw(sf::RenderTarget& Target)
{
	Body::Draw(Target);
}

bool Planets_Initialize( void )
{
	HabbitablePlanetImg = Engine::g_ImageManager->Load("Resources/Images", "habbitable_planet.png");
	
	if(!HabbitablePlanetImg)
		return false;
		
	std::cout << "Loaded 'Resources/Images/habbitable_planet.png'" << std::endl;
	
	return true;
}

