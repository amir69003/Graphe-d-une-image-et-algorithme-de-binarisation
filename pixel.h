#ifndef _PIXEL_
#define _PIXEL_

enum Direction {Nord = 0, Sud  = 1, Ouest = 2, Est = 3, Source = 4, Puits = 5}; //enum des differents direction possible

const double ecart_type=30.0;        //ecart-type
const double alpha=2.0;           //alpah


class Pixel{
    
    public :
    
    Pixel();  
    
    //retourne l'intensite du pixel
     int get_intensite();
    
    //parametrer l'intensite
    void set_intensite(int i);
    
    //retourne la capacite
    double get_capacite(Direction d);
    
    //parametrer la capacite
    void set_capacite(double i, Direction d);
    
    //retourne le flot
    double get_flot(Direction d);

    //parametrer le flot
    void set_flot(double i,Direction d );

    private : 
    
    int intensite_lumineuse; //0 à 255
    double capacite[6]; //Nord, Sud, Ouest, Est, Source, Puits
    double flot[6]; //Nord, Sud, Ouest, Est, Source, Puits
};

#endif