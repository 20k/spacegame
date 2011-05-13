#include "imagegen/imagegen.hpp"
#include "pnoise/pnoise.h"
#include "space/planet.h"


void SetPixelWithVariance(int r, int g, int b, int x, int y, int variance, sf::Image &Image)
{


        int br, bg, bb;
        br=r*variance;
        bg=g*variance;
        bb=b*variance;


        if(br>255) {
                br=255;
        }
        if(br<0) {
                br=0;
        }
        if(bg>255) {
                bg=255;
        }
        if(br<0) {
                bg=0;
        }
        if(bb>255) {
                bb=255;
        }
        if(br<0) {
                bb=0;
        }

        sf::Color Temp;
        Temp.r=br;
        Temp.g=bg;
        Temp.b=bb;
        Image.SetPixel(x, y, Temp);



}

void PlanetHelper::GetNoise()
{


        Array=PerlinNoise::Generate(Planet::XYOffset*Planet::OffsetMul, Planet::XYOffset*Planet::OffsetMul, Radius*2, Radius*2, 5, 2, 25);


}


PlanetHelper::PlanetHelper(int pRadius, Lim*pLims, int pLimnum)
{

        Radius=pRadius;
        Limnum=pLimnum;
        Lims=new Lim[pLimnum];
        for(int i=0; i<pLimnum; i++) {
                Lims[i]=pLims[i];
        }

}






void ParseData( int minx, int maxx, int miny, int maxy, int Radius, double **&Array )
{

        for(int x=0; x<Radius*2; x++) {
                for(int y=0; y<Radius*2; y++) {

                        if(sqrt(pow(x-Radius, 2)+pow(y-Radius,2))<Radius) {

                                double Total=0;
                                double Count=0;

                                for(int i=minx; i<maxx; i++) {       ///Lopside the terrain generation and smooth the heightmap to remove little things.
                                        for(int j=miny; j<maxy; j++) {
                                                if(x+i>0 && x+i<Radius*2  && y+j>0 && y+j<Radius*2 ) {
                                                        Total+=Array[x+i][y+j];
                                                        Count++;
                                                }
                                        }
                                }

                                if(Count!=0) {
                                        Array[x][y]=Total/Count;

                                }
                        }
                }

        }
}


sf::Color &PlanetHelper::GetColoursFromHeightmap( int x, int y )
{

        int B=0;

        for(int i=0; i<Limnum; i++) {

                if(Array[x][y]*255>Lims[i].Val) {

                        if(Lims[i].Val>B) {
                                B=Lims[i].Val;
                        }

                }

        }

        return Lims[B].Colour;

}

int PlanetHelper::ReturnTier(int x, int y)
{


        int B=0;

        for(int i=0; i<Limnum; i++) {

                if(Array[x][y]*255>Lims[i].Val) {

                        if(Lims[i].Val>B) {
                                B=Lims[i].Val;
                        }

                }

        }

        return B;


}


void PlanetHelper::GenerateImage()
{


        ParseData(2, 2, 2, 2, Radius,  Array);

        sf::Color C;

        sf::Color Last;


        for(int x=0; x<Radius*2; x++) {
                for(int y=0; y<Radius*2; y++) {

                        if((sqrt(pow(x-Radius, 2)+pow(y-Radius,2)))<Radius) {

                                sf::Color Final(0,0,0);
                                Last=Final;
                                Final=GetColoursFromHeightmap(x, y);
                                int Check=0;
                                int LastCheck=0;
                                int xlowerlim=1, xupperlim=1, ylowerlim=1, yupperlim=1;
                                if(x+-xlowerlim>0 && x+xlowerlim<Radius*2 ) {
                                        for(int i=-xlowerlim; i<xupperlim+1; i++) {
                                                Check=ReturnTier(x+i, y);
                                                LastCheck=ReturnTier(x+i-1, y);
                                                if(Check!=LastCheck) {
                                                        Final=GetColoursFromHeightmap(x-1, y);
#ifdef SHADING
                                                        set_pixel_with_variance((Final.r+Last.r)/2, (Final.g+Last.g)/2, (Final.b+Last.b)/2,Array[x-1][y], x-1, y, Image);
#endif
                                                }
                                        }
                                }
                                Check=0;
                                if(y+-ylowerlim>0 && y+ylowerlim<Radius*2 ) {
                                        for(int i=-ylowerlim; i<yupperlim+1; i++) {
                                                Check=ReturnTier(x, y+i);
                                                LastCheck=ReturnTier(x, y+i-1);
                                                if(Check!=LastCheck) {
                                                        Final=GetColoursFromHeightmap(x, y-1);
#ifdef SHADING
                                                        set_pixel_with_variance((Final.r+Last.r)/2, (Final.g+Last.g)/2, (Final.b+Last.b)/2,Array[x][y-1], x, y-1, Image);
#endif
                                                }
                                        }
                                }
                                SetPixelWithVariance(Final.r, Final.g, Final.b, x, y, 1, Image);
                        } else {
                                SetPixelWithVariance(255, 0, 255,  x, y, 1, Image);
                        }
                }
        }
}
