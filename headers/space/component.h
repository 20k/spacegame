#ifndef INCLUDES_SPACE_COMPONENT_H
#define INCLUDES_SPACE_COMPONENT_H

#include "common.h"
#include "math/vector2.h"

#include <list>

#include <SFML/Graphics.hpp>

// The base class for everything that is in space.
class Component
{
	public:
		Component(const Vector2<double>& Position, Component* Parent = 0)
			: m_Position(Position), m_Parent(Parent)
		{
		}
		
		virtual ~Component() { }

		virtual Vector2<double> GetRelativePosition( void ) = 0;
		virtual Vector2<double> GetAbsolutePosition( void ) = 0;
		virtual void Update(const Timestep Delta) = 0;
		virtual void Draw(sf::RenderTarget& Target) = 0;
	
	protected:
		Vector2<double> m_Position;
		
		Component* m_Parent;
		std::list<Component*> m_Children;
		
		friend class Body;
		friend class Entity;
};

#endif /* INCLUDES_SPACE_COMPONENT_H */

