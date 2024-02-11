#ifndef _GRAPHE_
#define _GRAPHE_
#include"pixel.h"
#include<queue>
#include <vector>
#include <fstream>
#include"pixel.h"
#include<queue>
#include"math.h"

#include<stdlib.h>
using namespace std;
class Graphe{

    public : 
    int L, C; //ligne et colonnes lu par le fichier;
    Pixel * tableau; //[L*C];
    int intensite_max ; 
    

    //constructeur du graphe, grace a l'image donnée en parametre
    Graphe(const char * nomFichier);

    //destructeur du graphe
    ~Graphe();
    
    //afficher les valeurs du graphe
    void afficher_valeur() const;

    //retourne la coordonne pour tableau 1D
    int get_coord(int x, int y);

    //retourne la coord du voisin grace a i et j
    int get_voisin(int i,int j,Direction d);

    ////retourne la coord du voisin grace a i
    int get_voisins(int i,Direction d);

    //calcul la capacite des Pixels
    void calcul_capacite();

    //trouve un chemin entre la Source et le puits
    vector<int> trouver_chemin();
    
    //calcul du flot entre un pixel p et q via une direction
    double flot_arc(int p1, int p2);

    //rennvoie la direction oppose de la coordonne donne
    Direction inverser_coord(Direction d);

    //renvoie la direction du voisin de p1 
    Direction voisin_orientation(int p1 , int p2);

    //remplit les flots en fonctions des capacites et des chemins
    void remplir_tout_ces_flot();

    //appel remplir_tout_ces_flots
    void remplir_flot();

    //modifie l'intensite pour la mettre soit a 0 ou bien a 255
    void modif_intensite();

    //permet de créer l'image via le tableau d'intensite modifie
    void creation_image();

    private : 

}; 

#endif