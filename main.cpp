#include <iostream>
#include <stdlib.h>
#include "graphe.h"
using namespace std;





int main (void)
{
    Graphe test("test.ascii.pgm");
    test.calcul_capacite();
    test.remplir_flot();
    test.modif_intensite();
    test.creation_image();
    return 0;
}