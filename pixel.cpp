#include"pixel.h"


Pixel::Pixel()
{
    intensite_lumineuse = 0;

    for(int i=0;i<6;i++)
    {
        flot[i]=0;
        capacite[i]=0;
    }
}

double Pixel::get_capacite(Direction d)
{
    return capacite[d];
}

void Pixel::set_capacite(double i, Direction d)
{
    capacite[d]= i;
}

double Pixel::get_flot(Direction d)
{
    return flot[d];
}

void Pixel::set_flot(double i, Direction d)
{
    flot[d]=i;
}

int Pixel::get_intensite()
{
    return intensite_lumineuse;
}

void Pixel::set_intensite(int i)
{
    intensite_lumineuse = i;

}