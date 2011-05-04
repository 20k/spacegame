#ifndef INCLUDES_SPACE_MOON_H
#define INCLUDES_SPACE_MOON_H

#include "common.h"
#include "space/body.h"

#include <SFML/Graphics.hpp>


class Moon : public Body
{
	public:
		Moon( Body* Parent );

		void Update(const Timestep Delta);
		void Draw(sf::RenderTarget& Target);
		
	protected:
		sf::Sprite m_Sprite;
		double m_OrbitalRadius;
		double m_OrbitalStep;
};

extern bool Moons_Initialize( void );

#endif /* INCLUDES_MOON_H */

