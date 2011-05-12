#include "pnoise/pnoise.h"

// Reference implementation by MMavipc

struct XYD{
    double x, y;
    XYD(){}

};




inline void Distort(double x, double y, XYD&dest, double radius, double xoffset=0, double yoffset=0){  ///radius offsets

        dest.x=(1-((sqrt((x-radius-xoffset)*(x-radius-xoffset) + (y-radius-yoffset)*(y-radius-yoffset))/radius)))*(x-radius-xoffset)+radius;      //+100;
        dest.y=(1-((sqrt((x-radius-xoffset)*(x-radius-xoffset) + (y-radius-yoffset)*(y-radius-yoffset))/radius)))*(y-radius-yoffset)+radius;      //+20;

}

void Fisheye(double x, double y, XYD&dest){
            double z;
            double tmp, rx, ry;
            double ri = 0.5f; // refraction index

            z = (double)sqrt(1.0 - (x * x)  - (y * y));

            rx = ri * x;
            tmp = (double)sqrt(1.0- (rx * rx) - (y * y));
            dest.x = rx * (1.0- (y * y)) / ((z * tmp) + (rx * x));

            ry = ri * y;
            //exit(dest.x);
            tmp = (double)sqrt(1.0- (x * x) - (ry * ry));
            dest.y = ry * (1.0-(x * x)) / ((z * tmp) + (ry * y));       //+20;
}



inline double Noise( double x, double y, int Seed = 337 ) ///There were good reasons why i picked this number, dont change it
{
        int n=(int)x+(int)y*337;
        n=(n<<13)^n;
        int nn=(n*(n*n*41333 +53307781)+1376312589)&0x7fffffff;
        return 1.0-((double)nn/1073741824.0);
}

inline double Smooth(int i, int j)
{
        return (double)(Noise(i, j)+Noise(i+1, j)+Noise(i, j+1)+Noise(i+1, j+1))/4.0;
}

inline double CosineInterpolate( double A, double B, double X )
{
	double ft = X * 3.1415927;
	double f = (1.0 - cos(ft)) * 0.5;
	return A * (1.0 - f) + B * f;
}

double LinearInterpolate(double A, double B, double X)
{
	return A * (1 - X) + (B * X);
}

#define WHICH_INTERPOLATE LinearInterpolate


inline double ** InterpolatedArrayMem(int Xoffset, int Yoffset,int pWidth, int pHeight, int Frequency, double Zoom=1)
{
        int radius=-1;
        XYD r;
        XYD p;
        XYD fin;
        double **Interpolated=new double*[pWidth+1];
        for(int i=0; i<pWidth+1; i++) {
                Interpolated[i]=new double[pHeight+1];
        }
        for(int i=0; i<pWidth+1; i++) {

                for(int j=0; j<pHeight+1; j++) {
                        double X=(((i+Xoffset)*Frequency)/Zoom);
                        double Y=(((j+Yoffset)*Frequency)/Zoom);
                        fin.x=i;
                        fin.y=j;
                        if(pWidth==pHeight){
                            radius=pWidth/2.0;
                            Distort(X, Y, p, radius);
                            r=p;
                        }else{
                                r.x=X;
                                r.y=Y;
                        }
                        double V1=Smooth(r.x ,r.y);
                        double V2=Smooth(r.x+1, r.y);
                        double V3=Smooth(r.x, r.y+1);
                        double V4=Smooth(r.x+1,r.y+1);
                        double I1=WHICH_INTERPOLATE(V1, V2, r.x-int(r.x));
                        double I2=WHICH_INTERPOLATE(V3, V4, r.x-int(r.x));
                        int lx, ly;
                        lx=fin.x;
                        ly=fin.y;
                        Interpolated[lx][ly]=CosineInterpolate(I1, I2,r.y-int(r.y));
                        Interpolated[lx][ly]+=1;
                        Interpolated[lx][ly]/=2;
                }
        }
        delete [] Interpolated[pWidth];
        return Interpolated;
}


//void PerlinNoise::Generate( sf::Image &Image, const int Octaves, const double Zoom, const double Persistence, const int Seed )

double** PerlinNoise::Generate( int Xoffset,int Yoffset, int Width, int Height, int Octaves, int Frequency, double Zoom ){
        double *** Arraymain;
        Arraymain=new double**[Octaves];
        double **Array;
        Array=new double*[Width];

        for(int i=0; i<Width; i++) {
                Array[i]=new double[Height];
        }

        for(int i=0; i<Octaves; i++) {
            #ifdef _MSC_VER
                Arraymain[i]=InterpolatedArrayMem(Xoffset, Yoffset, Width, Height, pow(long double(Frequency), long double(i)), Zoom);
            #else
                Arraymain[i]=InterpolatedArrayMem(Xoffset, Yoffset, Width, Height, pow(Frequency, i), Zoom);
            #endif
        }

        for(int x=0; x<Width; x++) {
                for(int y=0; y<Height; y++) {
                        double Total=0;
                        for(int i=0; i<Octaves; i++) {
                                Total+=Arraymain[i][x][y];
                        }
                        Array[x][y]=(Total/Octaves);
                        Array[x][y]=Array[x][y]/0.75;
                }
        }

        for(int i=0; i<Octaves; i++){
            for(int x=0; x<Width; x++){
                delete [] Arraymain[i][x];
            }
            delete [] Arraymain[i];
        }

        delete [] Arraymain;
        return Array;
}
