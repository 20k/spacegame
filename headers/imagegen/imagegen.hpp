#ifndef INCLUDES_IMAGEGEN_HEADER
#define INCLUDES_IMAGEGEN_HEADER
#include <SFML/Graphics.hpp>

struct Lim{
    int Val;
    sf::Color Colour;
    Lim(){}
};

class PlanetHelper{

    public:
        Lim *Lims;
        double **Array;
        sf::Image Image;
        int Radius;
        int Limnum;


        void GetNoise();

        void GenerateImage();

        PlanetHelper(int pRadius, Lim *pLims, int pLimnum);

        sf::Color &GetColoursFromHeightmap(int x, int y);
        int ReturnTier(int x, int y);
};




#endif
