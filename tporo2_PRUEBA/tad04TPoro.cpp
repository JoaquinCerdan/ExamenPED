#include <iostream>
using namespace std;
#include "tporo.h"

/* TRADUCCION DE COLORES Y COMPARACION CADENA "" CON NULL */


int
main(void)
{

  TPoro a(0, 0, 0);
  TPoro a2(0, 0, 0, "");

  TPoro b(0, 0, 0, "rojo");
  TPoro b2(0, 0, 0, "Rojo");
  TPoro b3(0, 0, 0, "RojO");

  if(a == a2)
    cout << "IGUALES" << endl;
  else
    cout << "DISTINTOS"  << endl;
  

  if ((b == b2) && (b == b3)) 
    cout << "IGUALES" << endl;
  else
    cout << "DISTINTOS"  << endl;
  

}
