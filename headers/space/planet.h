#ifndef INCLUDES_SPACE_PLANET_H
#define INCLUDES_SPACE_PLANET_H

#include "common.h"
#include "space/body.h"

#include <SFML/Graphics.hpp>

enum PlanetType
{
	PlanetType_Habbitable = 0,
	PlanetType_Gaseous,
	PlanetType_Frozen,
	PlanetType_Superheated,
	PlanetType_Max,
};

class Planet : public Body
{
	public:
		Planet(const PlanetType Type, const Vector2<double>& Position, Body* Parent = 0);
		~Planet();

		void Update(const Timestep Delta);
		void Draw(sf::RenderTarget& Target);
		
	protected:
		PlanetType m_Type;
		sf::Sprite m_Sprite;
};

extern bool Planets_Initialize( void );

#endif /* INCLUDES_SSYTEM_H */

