#include "engine/resmanager.h"

namespace Engine
{
	/*bool ResourceManager<sf::Image>::UnderlyingLoad(Resource<sf::Image>* Resource)
	{
		std::string Fullpath = Resource->Path;
		Fullpath.append("/");
		Fullpath.append(Resource->Filename);

		return Resource->Underlying->LoadFromFile(Fullpath);
	}*/
	
	ResourceManager::~ResourceManager()
	{
		for(std::list<Resource*>::iterator i = m_Resources.begin(); i != m_Resources.end(); ++i)
			Unload((*i));
	}
	
	Resource* ResourceManager::Load( const std::string& Path, const std::string& Filename )
	{
		for(std::list<Resource*>::iterator i = m_Resources.begin(); i != m_Resources.end(); ++i)
			if((*i)->Path.compare(Path) == 0)
				if((*i)->Filename.compare(Filename) == 0)
					return (*i);
		
		Resource* NewRes = new Resource(Path, Filename, this);
		
		if(!UnderlyingLoad(NewRes))
		{
			delete NewRes;
			return 0;
		}
		
		m_Resources.push_back(NewRes);
		return NewRes;
	}
	
	void ResourceManager::Unload( Resource* Resource )
	{
		m_Resources.remove(Resource);
		UnderlyingLoad(Resource);
		delete Resource;
	}
}

