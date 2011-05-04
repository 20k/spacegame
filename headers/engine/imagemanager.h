#ifndef INCLUDES_ENGINE_IMAGEMANAGER_H
#define INCLUDES_ENGINE_IMAGEMANAGER_H

#include "common.h"
#include "engine/resmanager.h"

namespace Engine
{
	class ImageManager : public ResourceManager
	{
		protected:
			bool UnderlyingLoad( Resource* Resource );
			void UnderlyingUnload( Resource* Resource );
	};
	
	extern ImageManager* g_ImageManager;
}

#endif /* INCLUDES_ENGINE_IMAGEMANAGER_H */

