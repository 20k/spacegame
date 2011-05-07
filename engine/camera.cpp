#include "engine/camera.h"
#include <cmath>

namespace gCamera{

	Vector2<double> g_camPos(0, 0);
	double g_WSW, g_WSH;
	double g_camScale=0.5;
	
	void SetCameraPosition(Vector2<double> pos)
	{
		g_camPos=pos;
	}

	Vector2<double> GetCameraPosition()
	{
		return g_camPos;
	}

	void SetWindowSize(int w, int h)
	{
		//g_WAspect=(double)h/(double)w;
		g_WSW=w;
		g_WSH=h;
	}

	void SetCameraScale(double scale)
	{
		g_camScale=scale;
	}

	double GetCameraScale()
	{
		return g_camScale;
	}

	void SetCameraZoom(double zoom)
	{
		g_camScale=exp(zoom);
	}

	void AddCameraZoom(double ozoom)
	{
		//Not sure about this function, I don't want to save and sync zoom, so. Should be fine anyway
		double zoom=log(g_camScale);
		g_camScale=exp(zoom+ozoom);
	}

	double PointToSize(double size)
	{
		size*=floor(g_camScale*g_WSW);
		return size;
	}

	Vector2<double> PointToPixels(Vector2<double> pos)
	{
		pos.X-=g_camPos.X;
		pos.X*=g_camScale;
		pos.X*=g_WSW;
		pos.X+=g_WSW*0.5;

		pos.Y-=g_camPos.Y;
		pos.Y*=g_camScale;
		//pos.Y*=g_WScale*g_WAspect*-1;
		//pos.Y+=g_WScale*g_WAspect*0.5;

		pos.Y*=g_WSW*-1;
		pos.Y+=g_WSW*0.5;

		pos.X=floor(pos.X);
		pos.Y=floor(pos.Y);
		return pos;
	}

	Vector2<double> PixelsToPoint(Vector2<double> pos)
	{
		pos.X-=g_WSW*0.5;
		pos.X/=g_WSW*g_camScale;
		pos.X+=g_camPos.X;

		//pos.Y-=g_WScale*g_WAspect*0.5;
		//pos.Y/=g_WScale*g_WAspect*-1*g_camScale;

		pos.Y-=g_WSW*0.5;
		pos.Y/=g_WSW*-1*g_camScale;
		pos.Y+=g_camPos.Y;
		return pos;
	}

	bool IsVisible(Vector2<double> pos)
	{
		pos=PointToPixels(pos);
		return !(pos.X<0 || pos.X>g_WSW || pos.Y<0 || pos.Y>g_WSH);
	}

	bool IsVisible(Vector2<double> pos, Vector2<double> size)
	{
		if(IsVisible(pos)) return true;
		pos=size+pos; //Sifn't overload +=, hehe.
		if(IsVisible(pos)) return true;
		return false;
	}

};