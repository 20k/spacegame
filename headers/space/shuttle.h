#ifndef INCLUDES_SPACE_SHUTTLE_H
#define INCLUDES_SPACE_SHUTTLE_H

#include "common.h"
#include "space/entity.h"

class Shuttle : public Entity
{
	public:
		Shuttle(const Vector2<double>& Position, Component* Galaxy = 0);
		~Shuttle();
		
		// Sub-classes should implement this and use Delta to update position,
		// and call the base function to update all children
		virtual void Update(const Timestep Delta);
		
		// Sub-classes should implement this and call the base function,
		// to draw all children
		virtual void Draw(sf::RenderTarget& Target);
};

#endif /* INCLUDES_SPACE_SHUTTLE_H */

