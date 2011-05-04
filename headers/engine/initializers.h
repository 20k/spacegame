#ifndef INCLUDES_ENGINE_INITIALIZERS_H
#define INCLUDES_ENGINE_INITIALIZERS_H

#include "common.h"

#include <list>
#include <string>

namespace Engine
{
	class Initializer
	{
		public:
			std::string Message;
			bool (*Function)( void );
	};
	
	class Initializers
	{
		public:
			void Add(const std::string& Message, bool (*Function)( void ));
			bool Initialize( void );
		
		protected:
			std::list<Initializer*> m_Initializers;
	};
	
	extern Initializers* g_Initializers;
}

#endif /* INCLUDES_ENGINE_IMAGEMANAGER_H */

