#ifndef INCLUDES_SPACE_ENTITY_H
#define INCLUDES_SPACE_ENTITY_H

#include "common.h"
#include "math/vector2.h"
#include "space/component.h"

#include <list>

#include <SFML/Graphics.hpp>

class Body;

// The base class for everything that is in space that's alive, like spaceships
class Entity : public Component
{
	public:
		Entity(const Vector2<double>& Position, Component* Parent = 0);
		virtual ~Entity() { }
		
		// Relative to its parents.
		Vector2<double> GetRelativePosition( void );
		
		// Gets the position, compared to space
		// For example, This + Galaxy + Space
		virtual Vector2<double> GetAbsolutePosition( void );
		
		// Sub-classes should implement this and use Delta to update position,
		// and call the base function to update all children
		virtual void Update(const Timestep Delta);
		
		// Sub-classes should implement this and call the base function,
		// to draw all children
		virtual void Draw(sf::RenderTarget& Target);
};

#endif /* INCLUDES_SPACE_ENTITY_H */

