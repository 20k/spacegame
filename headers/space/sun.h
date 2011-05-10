#ifndef INCLUDES_SPACE_SUN_H
#define INCLUDES_SPACE_SUN_H

#include "common.h"
#include "space/body.h"
#include "space/component.h"

#include <SFML/Graphics.hpp>

enum SunType {
	SunType_MainSequence =0,
	SunType_RedGiant,
	SunType_WhiteDwarf
};

class Sun : public Body
{
	public:
		Sun(const SunType type, const Vector2<double>& Position, Component* Parent = 0);
		~Sun();

		void Update(const Timestep Delta);
		void Draw(sf::RenderTarget& Target);

		void UpdateTexture();
		
	protected:
		double flamestep;
		SunType m_Type;
		sf::Sprite m_Sprite;
		sf::Image m_Image;
};

#endif /* INCLUDES_SUN_H */

