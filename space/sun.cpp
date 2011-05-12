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

	m_Children.push_back(new Planet(PlanetType_Habitable, Vector2<double>(5.0, 0.0),this));
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
	//Offset for 'flaming'
	flamestep+=0.003*Delta;
	Body::Update(Delta);

	//Only update texture if the sun is visible (not a fast function)
	Vector2<double> Pos = GetAbsolutePosition();
	double Radius = m_Radius;
	Vector2<double> Size(m_Radius, m_Radius);
	if(!gCamera::IsVisible(Pos-(Size*0.5), Size)){
		return;
	}
	int w=m_Image.GetWidth();
	int h=m_Image.GetHeight();

	//Get center
	int centp=floor((float)w/2.0);
	Vector2<double> distv;
	float dist=0;
	double alpha=0;
	double xst, yst;
	double rpl, thetapl;
	double val, val2;
	for(int y=0;y<h;y++){
		for(int x=0;x<w;x++){
			//Get this pixels distance from center
			distv=Vector2<double>((double)(centp-x)/w, (double)(centp-y)/h);
			dist=distv.Length();

			//Clamp the alpha to have more of a ball effect rather than a simple gradient
			alpha=((dist-0.3)*15);
			alpha=1-alpha;

			if(alpha<0){
				//No point calculating data for a pixel that isn't shown
				continue;
			}
			//X-Step and Y-Step, basically just a system from -1,1
			xst=(double)(x-centp)/(double)w;
			yst=(double)(y-centp)/(double)h;
			//Convert to Polar Co-ordinates (r, theta) so flames appear to go out instead of across.
			rpl=(1/FastInverseSqrt(xst*xst+yst*yst))-flamestep;
			thetapl=atan2(yst,xst)-flamestep;

			//Small noise map
			val=abs(SimplexNoise1234::noise((xst+flamestep)*100.0, yst*100.0));
			//val=0.5;
			//val2=0.5;
			//Large 'flame' noise map
			val2=SimplexNoise1234::noise(rpl*10.0, thetapl*10.0);
			//I made a colour because all this in one line was just way too confusing.
			sf::Color col;

			//For different types of sun.
			switch(m_Type){
			case SunType_MainSequence:
				//It's gotta be red.
				col.r=255;
				//Okay, this is the green value, oranges are added with val and val2, then part of the 'white' component
				//by adding alpha.
				//Remember, val2 is 'flame' noise and val is small noise.
				col.g=clamp((255-(val2*30))*0.7+(val*50)+(alpha*20),0,255);
				//Blue is removed to add yellows, small noise and again, needs white component.
				col.b=((val*255)*0.5)+((alpha+0.2)*30);
				//Finally the alpha for the actual image is based mostly on the distance and the flame map.
				//The conversion to 8 bit value seems to modulus the value instead of clamp, so I make sure
				//it does not exceed 0-255
				alpha=clamp(alpha-(1-(val2*0.2)),0,1);
				col.a=alpha*255;
				break;
			case SunType_WhiteDwarf:
				col.r=clamp(1-(val2*0.5)-(val*0.5)+(alpha*0.1), 0, 1)*255;
				col.g=clamp(1-(val2*0.5)-(val*0.7)+(alpha*0.2), 0, 1)*255;
				col.b=255;
				alpha=clamp(alpha-(1-(val2*0.2)),0,1);
				col.a=alpha*255;
				break;
			}
			//col.a=255;
			m_Image.SetPixel(x, y, col);
		}
	}
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
	//lsize is important, specifies the resolution of the sun and therefore, the speed of the
	//update function. Basically just a scale between quality and speed.
	double lsize=200;
	m_Image=sf::Image(lsize, lsize, sf::Color(0, 0, 0, 0));

	m_Sprite.SetImage(m_Image);
}
