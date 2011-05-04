#include "engine/initializers.h"

#include <iostream>

namespace Engine
{
	Initializers* g_Initializers = new Initializers();
	
	void Initializers::Add(const std::string& Message, bool (*Function)( void ))
	{
		Initializer* NewInit = new Initializer();
		NewInit->Message = Message;
		NewInit->Function = Function;
		
		m_Initializers.push_back(NewInit);
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

