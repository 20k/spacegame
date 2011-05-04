#ifndef INCLUDES_ENGINE_RESMANAGER_H
#define INCLUDES_ENGINE_RESMANAGER_H

#include "common.h"

#include <list>
#include <string>

#include <SFML/Graphics.hpp>

namespace Engine
{
	template <class T>
	class ResourceManager;

	template <class T>
	class Resource
	{
		public:
			Resource(const std::string& Path, const std::string& Filename, ResourceManager<T>* Manager)
				: Path(Path), Filename(Filename), Underlying(0), m_Manager(Manager), m_Refs(1)
			{ }
			
			void Reference( void )
			{
				++m_Refs;
			}
			
			void Free( void )
			{
				--m_Refs;
				
				if(m_Refs <= 0)
					m_Manager->Unload(this);
			}
			
			// Use this to get the underlying type that isn't a pointer
			T& Get( void )
			{
				return *Underlying;
			}
			
			std::string Path;
			std::string Filename;
			T* Underlying;
			
		private:
			ResourceManager<T>* m_Manager;
			unsigned int m_Refs;
	};
	
	template <class T>
	class ResourceManager
	{
		public:
			~ResourceManager();
			
			Resource<T>* Load(const std::string& Path, const std::string& Filename);
			void Unload(Resource<T>* Resource);
		
		protected:
			std::list<Resource<T>*> m_Resources;

			bool UnderlyingLoad(Resource<T>* Resource);
	};

	template <>
	class ResourceManager<sf::Image>
	{
		public:
			~ResourceManager();
		
			Resource<sf::Image>* Load(const std::string& Path, const std::string& Filename);
			void Unload(Resource<sf::Image>* Resource);
		
		protected:
			std::list<Resource<sf::Image>*> m_Resources;

			bool UnderlyingLoad(Resource<sf::Image>* Resource);
	};
	
	extern ResourceManager<sf::Image>* g_ImageManager;
}

#endif /* INCLUDES_ENGINE_RESMANAGER_H */

