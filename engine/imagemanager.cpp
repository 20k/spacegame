#include "engine/imagemanager.h"

// TODO: Error handling

namespace Engine
{
	ImageManager* g_ImageManager = new ImageManager();
	
	bool ImageManager::Load(Resource<sf::Image>* Resource)
	{
		std::string Fullpath = Resource->Path;
		Fullpath.append("/");
		Fullpath.append(Resource->Filename);

		return Resource->Underlying->LoadFromFile(Fullpath);
	}
}

