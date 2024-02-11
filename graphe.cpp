#include<iostream>
#include<stdlib.h>
#include<string.h>
#include <fstream>
#include<queue>
#include<algorithm>
#include"math.h"
#include"pixel.h"
#include"graphe.h"

using namespace std;

Graphe::Graphe(const char * nomFichier) 
{
    int valeurs = 0; //valeur du pixel qu'on va inseré dans le tableau d'intensité
    std::ifstream ifs;
    ifs.open(nomFichier);
    if(ifs.bad())
    {cout<<"Impossible d'ouvrir le fichier "<<nomFichier<<" en lecture \n"; exit(1);}
    string puits;
    
    ifs>>puits;             //caractère inutile
    ifs>>C;                 //le nombre de colonne
    ifs>>L;                 //le nombre de ligne
    ifs>>intensite_max;     //l'intesite maximum
    
    tableau=new Pixel[L*C];     //insertion dans notre tableau de pixel
    for(int i = 0;i<L*C;i++)
    {
        ifs>>valeurs;
        tableau[i].set_intensite(valeurs);      //on saisit les pixels dans le tableau de pixels
    }
    ifs.close();
}

Graphe::~Graphe()
{

}

void Graphe::afficher_valeur()const{

    cout<<"Les Colonnes "<<C<<endl;
    cout<<"Les Lignes "<<L<<endl;
    cout<<"intensité max "<<intensite_max<<endl;
    for(int i = 0;i<L;i++)
        {
            for(int j= 0;j<C;j++)
            {
                cout<<tableau[i*C+j].get_intensite()<<" ";
            }
            cout<<endl;
        }
}



int Graphe::get_coord(int i, int j)
{
    return i*C+j;
}


int Graphe::get_voisins(int k,Direction o)
{
    switch (o) 
    {
        case Est:
            if (k%C==C-1)
            {
                return -1;
            }
            else
            {
                return k+1;
            }
            break;

        case Ouest:
            if (k%C==0)
            {
                return -1;
            }
            else
            {
                return k-1;
            }
            break;


        case Nord:
            if (k<=C-1)
            {
                return -1;
            }
            else
            {
                return k-C;
            }
            break;
        case Sud:
            if (k>=C*(L-1))
            {
                return -1;
            }
            else
            {
                return k+C;
            }
            break;
        
        default:
            cout<<"Pas bon";
            return -1;
        }
}

int Graphe::get_voisin(int i,int j,Direction d)
{
    int c=0;
    switch (d){
        case Nord :
            c=get_coord(i-1,j);
            if((0<=c)&&(c<L*C))
            {
                //cout<<"Nord"<<endl;
                return c;
                break;
            }
            else
            {
                return -1;
                break;
            }
            
        case Sud :
            c=get_coord(i+1,j);
            if((0<=c)&&(c<L*C))
            {
                //cout<<"Sud"<<endl;
                return c;
                break;
            }
            else
            {
                return -1;
                break;
            }
        case Ouest :
            c=get_coord(i,j-1);
            if((0<=c)&&(c<L*C))
            {
                //cout<<"Ouest"<<endl;
                return c;
                break;
            }
            else
            {
                return -1;
                break;
            }
        case Est :
            c=get_coord(i,j+1);
            if((0<=c)&&(c<L*C))
            {
                //cout<<"Est"<<endl;
                return c;
                break;
            }
            else
            {
                return -1;
                break;
            }

        default:
            return -1;
     }
        
}


void Graphe::calcul_capacite(){
    int c=0;
    int v=0;
    Direction o;
    double valeurs = 0;
    for(int i=0;i<L;i++)
    {
        for(int j=0;j<C;j++)
        {
            c=get_coord(i,j);
            for(int k=0;k<4;k++)
            {
                o=static_cast<Direction>(k);
                v=get_voisin(i,j,o);
                if(v!=-1)
                {
                    valeurs =100 * exp(-(pow(tableau[c].get_intensite()-tableau[v].get_intensite(),2)/(2.0*pow(ecart_type,2))));
                    tableau[c].set_capacite(valeurs,o);
                    //tableau[c].set_capacite(exp(-(tableau[c].get_intensite())-((tableau[v].get_intensite())(tableau[v].get_intensite())))/(2.0(ecart_typeecart_type)),o);
                    //cout<<"chemin "<<tableau[c].get_intensite()<<" "<<tableau[get_voisins(c,o)].get_intensite() ;
                    //cout<<"set capacite : "<<tableau[c].get_capacite(o)<<endl;
                }
            }
            //tableau[c].set_capacite((-alphalog((255.0-tableau[c].get_intensite())/255.0)),Source);
            //tableau[c].set_capacite((-alphalog((tableau[c].get_intensite())/255.0)),Puits);
            tableau[c].set_capacite((-alpha*log((255-tableau[c].get_intensite())/255.0)),Source);
            tableau[c].set_capacite((-alpha*log((tableau[c].get_intensite())/255.0)),Puits);
            //cout<<"set capacite puits : "<<tableau[c].get_capacite(Puits);
            //cout<<"set capacite  source: "<<tableau[c].get_capacite(Source);
        }
    }
    
}



vector<int> Graphe::trouver_chemin(){

    vector<int> chemin;         //le vector du chemin a prendre
    bool visite [L*C];          //le tableau de pixel pour savoir si ils ont deja ete visite
    int predeceseur [L*C];      //le tableau de predecesseur de chaque pixels
    queue<int> potentiel_sommet;            //la file des autres sommets a voir
    Direction o;            
    int indice = 0;

    for (int i=0; i<L*C; i++)               //boucle pour initialiser les differents tableaux et file 
    {
        visite[i] = false;
        predeceseur[i] = -1;
        if(tableau[i].get_capacite(Source)>tableau[i].get_flot(Source)) //cas on ajoute a la file a visiter
        {
            potentiel_sommet.push(i);
        }

    }

    while(potentiel_sommet.size()>0)
    {
        indice = potentiel_sommet.front();
        potentiel_sommet.pop();
        //cout << "temp : " << temp << endl;
        //cout << "temp cas puit " << tableau[temp].get_capacite(Puits)<<endl;

        if(tableau[indice].get_capacite(Puits)>tableau[indice].get_flot(Puits))
        {
            break;
        }
    
   
    
   
    for(int k = 0;k < 4;k++)
    {

        o = static_cast<Direction>(k);
        if(get_voisins(indice,o) != -1)  
            {
                if(tableau[indice].get_capacite(o) > tableau[indice].get_flot(o) && !visite[get_voisins(indice,o)])
                {        
                    potentiel_sommet.push(get_voisins(indice,o));
                    predeceseur[get_voisins(indice,o)] = indice;
                    visite[get_voisins(indice,o)] = true;
                }
            }
    }
    visite[indice] = true;

    }
    cout<<"capacite puits "<<tableau[indice].get_capacite(Puits)<<" flot puits "<<tableau[indice].get_flot(Puits)<<endl;
    if((tableau[indice].get_capacite(Puits) <=tableau[indice].get_flot(Puits)))
    {
        //cout<<"je suis dedans"<<endl;
        indice = -1;
    }
    while(indice > -1)
    {
        chemin.push_back(indice);
        indice = predeceseur[indice];
    }
    return chemin;
}




Direction Graphe::voisin_orientation (int p1, int p2){
    Direction d;
    int indice;
    for (int k=0; k<4; k++){
        d = static_cast<Direction>(k);
        indice = get_voisins(p1,d);
        if(indice == p2)
        {
            break;
        }
    }
    if (indice != -1)
    {
        return d;
    }
    else{
        return Source;  
    }
}

Direction Graphe::inverser_coord(Direction d)
{
    switch (d)
    {
    case Est :
         
        return Ouest;
        break;

    case Ouest :
         
        return Est;
        break;
    
     case Nord : 
        return Sud;
        break;
    
    case Sud :
         
        return Nord;
        break;


    default:
        break;
    }
    cout<<"default source"<<endl;
    return Source;
}


double Graphe::flot_arc(int p1, int p2)
{
    Direction d  = voisin_orientation(p1, p2); 
    Direction d_oppose = inverser_coord(d);
    if (d == Source && tableau[p1].get_flot(d) >= tableau[p1].get_capacite(d)) 
    {
        return -1;
    }
    else
    {
        //cout<<"flot retourne : "<<tableau[p1].get_capacite(d) - tableau[p1].get_flot(d) + tableau[p2].get_flot(d_oppose)<<endl;
        if(tableau[p1].get_capacite(d)<tableau[p1].get_flot(d))
        {
            return -1;
        }
        return tableau[p1].get_capacite(d) - tableau[p1].get_flot(d) + tableau[p2].get_flot(d_oppose);
    }


}


void Graphe::remplir_tout_ces_flot()
{
    
    vector<int>chemin; 
    vector<double>potentiel_min;
    double minimum = 0;
    double capa_s = 0;
    double capa_p = 0;
    int k = 0;
    double compare = 0;


    while(trouver_chemin().size()>0)
    //for(int k = 0 ;k<41000 ; k++)
    {
        minimum = 0;
        capa_s = 0;
        capa_p = 0;
        chemin.clear();
        potentiel_min.clear();
        chemin = trouver_chemin();
        
        cout<<"-------chemin "<<k<<" --------"<<endl;

        capa_p = tableau[chemin.front()].get_capacite(Puits) -  tableau[chemin.front()].get_flot(Puits);  
        capa_s = tableau[chemin.back()].get_capacite(Source) - tableau[chemin.front()].get_flot(Source);
        if(capa_p<capa_s)
        {
            minimum = capa_p;
        } 
        else
        {
            minimum = capa_s;
        }
        potentiel_min.push_back(minimum);

        if(chemin.size()==1)
        {
            //cout<<"mini est "<<mini<<endl;
            tableau[chemin.back()].set_flot(minimum + tableau[chemin.back()].get_flot(Source),Source);
            tableau[chemin.front()].set_flot(minimum + tableau[chemin.front()].get_flot(Puits),Puits);
            //cout<<"valeur flot : "<<minimum<<" chemin : "<<tableau[chemin.front()].get_intensite()<<endl;

        }   
        else
        {
            for(unsigned int i = 0  ; i < chemin.size() ; i++ )
            {
                //cout<<" "<<tableau[chemin[i]].get_intensite()<<" "; 
            }
            //cout<<endl;


            for(unsigned int i = chemin.size() -1 ; i > 0 ; i-- )
            {
                //cout<<"potentiel min "<<flot_arc(chemin[i], chemin[i-1])<<"  ";
                compare =(flot_arc(chemin[i], chemin[i-1])); 
                //cout<<"compare "<<compare<<" ";
                if(compare==-1)
                {
                    
                }
                else
                {
                    potentiel_min.push_back(compare);
                }
            }
            //cout<<endl;
            minimum = *min_element(potentiel_min.begin(), potentiel_min.end());
            
            //cout<<"minimu est "<<minimum<<endl;
            tableau[chemin.front()].set_flot(minimum + tableau[chemin.front()].get_flot(Puits), Puits);
            tableau[chemin.back()].set_flot(minimum + tableau[chemin.back()].get_flot(Source), Source);
            
            for( unsigned int i = chemin.size() -1 ; i > 0 ; i--)
            {
                //cout<<"minimum flot "<<minimum<<endl;
                tableau[chemin[i]].set_flot(minimum + tableau[chemin[i]].get_flot(voisin_orientation(chemin[i],chemin[i-1])),voisin_orientation(chemin[i],chemin[i-1]));
                
                //cout<<"flot puits "<<tableau[chemin[i]].get_flot(Puits)<<" chemin : "<<tableau[chemin[i]].get_intensite()<<endl;
                //cout<<"valeur flot : "<<minimum <<" chemin : "<<tableau[chemin[i]].get_intensite()<<endl;
                //cout<<"chemin capacite "<<tableau[chemin[i]].get_capacite(voisin_orientation(i,i-1));
                //cout<<"capa puits "<<tableau[chemin[i]].get_capacite(Puits)<<endl;    
                //cout<<"capa flots "<<tableau[chemin[i]].get_flot(Puits)<<endl;    
            }
        }
    
        
    k++;
    }
    //cout<<"flot 200 sud "<<tableau[0].get_flot(Sud)<<endl;
    //cout<<"capa 200 sud "<<tableau[0].get_capacite(Sud)<<endl;
    //cout<<"flot est 200 "<<tableau[0].get_flot(Source)<<endl;
    //cout<<"capa 200 "<<tableau[0].get_capacite(Source)<<endl;

}
    




void Graphe::remplir_flot()
{

    remplir_tout_ces_flot();

}


void Graphe::modif_intensite()
{
   for(int i = 0 ; i<L*C ;i++)
   {
    if(tableau[i].get_capacite(Puits)==tableau[i].get_flot(Puits))
    {
        tableau[i].set_intensite(255);
    }
    else
    {
        tableau[i].set_intensite(0);
    }
   } 
}


void Graphe::creation_image()
{
    ofstream ofs;
    ofs.open("creation.ascii.pgm");
    ofs<<"P2"<<endl;
    ofs<<C<<" "<<L<<endl;
    ofs<<255<<endl;
    for(int i = 0;i<C;i++)
    {
        for(int j = 0;j<L;j++)
        {
            ofs<<tableau[L*i + j].get_intensite()<< " ";
        }
        ofs<<endl;
    }
}

