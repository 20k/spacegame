#ifndef INCLUDES_PNOISE_H
#define INCLUDES_PNOISE_H

#include "common.h"

#include <SFML/Graphics.hpp>

namespace PerlinNoise
{
	extern double **Generate( int Xoffset,int Yoffset, int Width, int Height, int Octaves, int Frequency, double Zoom );
}

#endif /* INCLUDES_PNOISE_H */

