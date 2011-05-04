#include "engine/initializers.h"

#include <iostream>

namespace Engine
{
	Initializers* g_Initializers = new Initializers();
	
	void Initializers::Add(const std::string& Message, bool (*Function)( void ))
	{
		m_Initializers.push_back(new Initializer(Message, Function));
	}
	
	bool Initializers::Initialize( void )
	{
		for(std::list<Initializer*>::iterator i = m_Initializers.begin(); i != m_Initializers.end(); ++i)
		{
			std::cout << (*i)->Message << std::endl;
			if(!(*i)->Function())
				return false;
		}
				
		return true;
	}
}

