#ifndef INCLUDES_ENGINE_CAMERA_H
#define INCLUDES_ENGINE_CAMERA_H

#include "math/vector2.h"

namespace gCamera{
	void SetCameraPosition(Vector2<double> pos);
	void SetCameraScale(double scale);
	void SetWindowSize(int w, int h);
	Vector2<double> PointToPixels(Vector2<double> pos);
	Vector2<double> PixelsToPoint(Vector2<double> pos);
	double PointToSize(double size);
}

#endif