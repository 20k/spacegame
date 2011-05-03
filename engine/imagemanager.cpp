#include "engine/imagemanager.h"

// TODO: Error handling

namespace Engine
{
	bool Load(Resource<sf::Image>* Resource)
	{
		std::string Fullpath = Resource->Path;
		Fullpath.append("/");
		Fullpath.append(Resource->Filename);

		return Resource->Underlying->LoadFromFile(Fullpath);
	}
}

