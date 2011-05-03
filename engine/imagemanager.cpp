#include "engine/imagemanager.h"

// TODO: Error handling

namespace Engine
{
	sf::Image ImageManager::Load(const std::string& Fullpath)
	{
		sf::Image Image;
		
		if(!Image.LoadFromFile(Fullpath))
		{
		}
		
		return Image;
	}
}

