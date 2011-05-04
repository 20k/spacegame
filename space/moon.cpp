#include "space/moon.h"
#include "engine/imagemanager.h"
#include "engine/initializers.h"

#include <iostream>
#include <math.h>

Engine::Resource* MoonRes = 0;
sf::Image* MoonImg = 0;

Moon::Moon( Body* Parent )
	: Body( Vector2<double>(0, 0), 32, Parent), m_OrbitalStep(0)
{
	m_Sprite = sf::Sprite (*MoonImg);
	m_OrbitalRadius = m_Parent->GetRadius() * 1.65;
	m_Position = Vector2<double>(m_OrbitalRadius, m_OrbitalRadius);
}

void Moon::Update(const Timestep Delta)
{
	m_OrbitalStep += 0.25 * Delta;
	
	if( m_OrbitalStep >= 360 )
		m_OrbitalStep = 0;
	
	m_Position.X = cos(DEG2RAD(m_OrbitalStep)) * m_OrbitalRadius;
	m_Position.Y = sin(DEG2RAD(m_OrbitalStep)) * m_OrbitalRadius;

	Body::Update(Delta);
}

void Moon::Draw(sf::RenderTarget& Target)
{
	Vector2<double> Pos = GetAbsolutePosition();
	m_Sprite.SetPosition(Pos.X - m_Radius, Pos.Y - m_Radius);
	
	Target.Draw(m_Sprite);
	
	Body::Draw(Target);
}

bool Moons_Initialize( void )
{
	MoonRes = Engine::g_ImageManager->Load("Resources/Images", "moon.png");
	
	if(!MoonRes)
		return false;
	
	MoonImg = (sf::Image*)MoonRes->Underlying;
	MoonImg->SetSmooth(false);
	
	std::cout << "Loaded 'Resources/Images/moon.png'" << std::endl;
	
	return true;
}

