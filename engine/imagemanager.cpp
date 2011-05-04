#include "engine/imagemanager.h"

namespace Engine
{
	ImageManager g_ImageManager = ImageManager ();
	
	bool ImageManager::UnderlyingLoad( Resource* Resource )
	{
		std::string Fullpath = Resource->Path;
		Fullpath.append("/");
		Fullpath.append(Resource->Filename);
		
		return ((sf::Image*)Resource->Underlying)->LoadFromFile(Fullpath);
	}
	
	void ImageManager::UnderlyingUnload( Resource* Resource )
	{
		delete ((sf::Image*)Resource->Underlying);
	}
}

