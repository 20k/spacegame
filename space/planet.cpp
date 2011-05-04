#include "space/planet.h"
#include "space/moon.h"
#include "engine/imagemanager.h"
#include "engine/initializers.h"

#include <iostream>

Engine::Resource* HabbitablePlanetRes = 0;
sf::Image* HabbitablePlanetImg = 0;

Planet::Planet(const PlanetType Type, const Vector2<double>& Position, Body* Parent)
	: Body(Position, 128, Parent), m_Type(Type)
{
	switch(m_Type)
	{
		case PlanetType_Habbitable: m_Sprite = sf::Sprite (*HabbitablePlanetImg); break;
	}
	
	m_Position.X += m_Radius;
	m_Position.Y += m_Radius;
	
	m_Children.push_back(new Moon(this));
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
	Vector2<double> Pos = GetAbsolutePosition();
	m_Sprite.SetPosition(Pos.X - m_Radius, Pos.Y - m_Radius);
	
	Target.Draw(m_Sprite);
	
	Body::Draw(Target);
}

bool Planets_Initialize( void )
{
	HabbitablePlanetRes = Engine::g_ImageManager->Load("Resources/Images", "habbitable_planet.png");
	
	if(!HabbitablePlanetRes)
		return false;
	
	HabbitablePlanetImg = (sf::Image*)HabbitablePlanetRes->Underlying;
	HabbitablePlanetImg->SetSmooth(false);
	
	std::cout << "Loaded 'Resources/Images/habbitable_planet.png'" << std::endl;
	
	return true;
}

