#include "space/entity.h"
#include "space/body.h"

Entity::Entity(const Vector2<double>& Position, Component* Parent)
	: Component(Position, Parent)
{
}

Vector2<double> Entity::GetRelativePosition( void )
{
	return m_Position;
}

Vector2<double> Entity::GetAbsolutePosition( void )
{
	Vector2<double> Result = Vector2<double> (m_Position.X, m_Position.Y);
	Component* Current = this->m_Parent;
	
	while( Current )
	{
		Result = Result + Current->m_Position;
		Current = Current->m_Parent;
	}
	
	return Result;
}

void Entity::Update(const Timestep Delta)
{
	for( std::list<Component*>::iterator i = m_Children.begin(); i != m_Children.end(); ++i )
		(*i)->Update(Delta);
}

void Entity::Draw(sf::RenderTarget& Target)
{
	for( std::list<Component*>::iterator i = m_Children.begin(); i != m_Children.end(); ++i )
		(*i)->Draw(Target);
}

