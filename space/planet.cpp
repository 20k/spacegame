#include "space/planet.h"
#include "engine/resmanager.h"

Engine::Resource<sf::Image>* HabbitablePlanetImg = 0;

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

void Planets_Initalize( void )
{
	Engine::g_ImageManager->Load("Resources/Images", "habbitable_planet.png");
}

