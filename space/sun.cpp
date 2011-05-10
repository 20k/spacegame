#include <cmath>
#include "space/sun.h"
#include "space/planet.h"
#include "engine/camera.h"
#include "pnoise/simplexnoise1234.h"

/*Protected Members:
		SunType m_Type;
		sf::Sprite m_Sprite;
		sf::Image m_Image;
*/


Sun::Sun(const SunType Type, const Vector2<double>& Position, Component* Parent)
	: Body(Position, 0.5, Parent)
{
	m_Type=Type;
	this->UpdateTexture();

	m_Children.push_back(new Planet(PlanetType_Habbitable, Vector2<double>(5.0, 0.0),this));
	flamestep=0;
}


Sun::~Sun()
{

}

double clamp(double val, double min, double max)
{
	if(val>max) return max;
	if(val<min) return min;
	return val;
}

void Sun::Update(const Timestep Delta)
{
	flamestep+=0.1*Delta;
	int w=m_Image.GetWidth();
	int h=m_Image.GetHeight();

	int centp=floor((float)w/2.0);
	Vector2<double> distv;

	for(int y=0;y<h;y++){
		for(int x=0;x<w;x++){
			distv=Vector2<double>((double)(centp-x)/w, (double)(centp-y)/h);
			float dist=distv.Length();

			double alpha=((dist-0.3)*15);
			alpha=1-alpha;

			if(alpha<0){
				//m_Image.SetPixel(x, y, sf::Color(0,0,0,0));
				continue;
			}
			double val=abs(SimplexNoise1234::noise(((double)(x+flamestep)/w)*100.0, ((double)(y+flamestep)/h)*100.0));
			double val2=SimplexNoise1234::noise(((double)(x+flamestep)/w)*20.0, ((double)(y+flamestep)/h)*20.0);
			sf::Color col;
			col.r=255;
			col.g=clamp((255-(val2*30))*0.7+(val*50)+(alpha*20),0,255);
			//col.b=(val*255)-((val2-1)*20);
			col.b=((val*255)*0.5)+((alpha+0.2)*30);
			alpha=clamp(alpha-(1-(val2*0.2)),0,1);
			col.a=alpha*255;
			//col.a=255;
			m_Image.SetPixel(x, y, col);
		}
	}

	Body::Update(Delta);
}

void Sun::Draw(sf::RenderTarget &target)
{
	Vector2<double> Pos = GetAbsolutePosition();
	double Radius = m_Radius;
	Vector2<double> Size(m_Radius, m_Radius);
	if(gCamera::IsVisible(Pos-(Size*0.5), Size)){
		Pos=gCamera::PointToPixels(Pos);
		int lsize=gCamera::PointToSize(Size.X);
		m_Sprite.SetPosition(Pos.X-lsize*0.5, Pos.Y-lsize*0.5);
		m_Sprite.Resize(lsize, lsize);
		target.Draw(m_Sprite);

	}

	Body::Draw(target);
}

void Sun::UpdateTexture()
{
	double Size = m_Radius*2;
	double lsize=gCamera::PointToSize(Size)*0.25;
	m_Image=sf::Image(lsize, lsize, sf::Color(0, 0, 0, 0));

	m_Sprite.SetImage(m_Image);
}