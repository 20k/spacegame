#ifndef INCLUDES_ENGINE_RESMANAGER_H
#define INCLUDES_ENGINE_RESMANAGER_H

#include "common.h"

#include <list>
#include <string>

#include <SFML/Graphics.hpp>

namespace Engine
{
	class Resource;
	class ResourceManager
	{
		public:
			~ResourceManager();
			
			Resource* Load( const std::string& Path, const std::string& Filename );
			void Unload( Resource* Resource );
			
		protected:
			std::list<Resource*> m_Resources;
		
			virtual bool UnderlyingLoad( Resource* Resource ) = 0;
			virtual void UnderlyingUnload( Resource* Resource) = 0;
	};
	
	class Resource
	{
		public:
			Resource(const std::string& Path, const std::string& Filename, ResourceManager* Manager)
				: Path(Path), Filename(Filename), Underlying(0), m_References(1), m_Manager(Manager)
			{
			}
			
			virtual ~Resource()
			{
			}

			void Reference( void )
			{
				m_References++;
			}
			
			void Dereference( void )
			{
				m_References--;
				
				if(m_References <= 0)
					m_Manager->Unload(this);
			}

		public:
			std::string Path;
			std::string Filename;
			void* Underlying;
			
		protected:
			unsigned int m_References;
			ResourceManager* m_Manager;
	};
}

#endif /* INCLUDES_ENGINE_RESMANAGER_H */

