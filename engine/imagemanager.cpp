#include "engine/imagemanager.h"

namespace Engine
{
	ImageManager* g_ImageManager = new ImageManager();
	
	bool ImageManager::UnderlyingLoad( Resource* Resource )
	{
		std::string Fullpath = Resource->Path;
		Fullpath.append("/");
		Fullpath.append(Resource->Filename);
		
		// sf::Image overloads the = operator, we need something like this:
		sf::Image* Image = new sf::Image;
		bool Success = Image->LoadFromFile(Fullpath);
		Resource->Underlying = Image;
		
		return Success;
	}
	
	void ImageManager::UnderlyingUnload( Resource* Resource )
	{
		delete ((sf::Image*)Resource->Underlying);
	}
}

