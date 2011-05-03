#ifndef INCLUDES_ENGINE_IMAGEMANAGER_H
#define INCLUDES_ENGINE_IMAGEMANAGER_H

#include "common.h"
#include "engine/resmanager.h"

#include <SFML/Graphics.hpp>

namespace Engine
{
	class ImageManager : public ResourceManager<sf::Image>
	{
		protected:
			sf::Image Load(const std::string& Fullpath);
	};
}

#endif /* INCLUDES_ENGINE_IMAGEMANAGER_H */

