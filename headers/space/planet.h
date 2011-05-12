#ifndef INCLUDES_SPACE_PLANET_H
#define INCLUDES_SPACE_PLANET_H

#include "common.h"
#include "space/body.h"
#include "space/component.h"

#include <SFML/Graphics.hpp>

enum PlanetType
{
	PlanetType_Habitable = 0,
	PlanetType_Gaseous,
	PlanetType_Frozen,
	PlanetType_Superheated,
	PlanetType_Max,
};

class Planet : public Body
{
	public:
		Planet(const PlanetType Type, const Vector2<double>& Position, Component* Parent = 0);
		~Planet();

		void Update(const Timestep Delta);
		void Draw(sf::RenderTarget& Target);
		static int XYOffset;
		const static int OffsetMul=1000;

	protected:
		PlanetType m_Type;
		sf::Sprite m_Sprite;

		double m_OrbitalRadius;
		double m_OrbitalStep;
};

extern bool Planets_Initialize( void );



#endif /* INCLUDES_SSYTEM_H */


