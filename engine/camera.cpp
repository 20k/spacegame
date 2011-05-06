#include "engine/camera.h"
#include <math.h>

namespace gCamera{

	Vector2<double> g_camPos(0, 0);
	double g_WAspect, g_WScale;
	double g_camScale=0.5;
	
	void SetCameraPosition(Vector2<double> pos)
	{
		g_camPos=pos;
	}

	void SetWindowSize(int w, int h)
	{
		g_WAspect=(double)h/(double)w;
		g_WScale=w;
	}

	void SetCameraScale(double scale)
	{
		g_camScale=scale;
	}

	double PointToSize(double size)
	{
		size*=floor(g_camScale*g_WScale);
		return size;
	}

	Vector2<double> PointToPixels(Vector2<double> pos)
	{
		pos.X-=g_camPos.X;
		pos.X*=g_camScale;
		pos.X*=g_WScale;
		pos.X+=g_WScale*0.5;

		pos.Y-=g_camPos.Y;
		pos.Y*=g_camScale;
		//pos.Y*=g_WScale*g_WAspect*-1;
		//pos.Y+=g_WScale*g_WAspect*0.5;

		pos.Y*=g_WScale*-1;
		pos.Y+=g_WScale*0.5;

		pos.X=floor(pos.X);
		pos.Y=floor(pos.Y);
		return pos;
	}

	Vector2<double> PixelsToPoint(Vector2<double> pos)
	{
		pos.X-=g_WScale*0.5;
		pos.X/=g_WScale*g_camScale;
		pos.X+=g_camPos.X;

		//pos.Y-=g_WScale*g_WAspect*0.5;
		//pos.Y/=g_WScale*g_WAspect*-1*g_camScale;

		pos.Y-=g_WScale*0.5;
		pos.Y/=g_WScale*-1*g_camScale;
		pos.Y+=g_camPos.Y;
		return pos;
	}

};