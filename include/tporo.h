#ifndef __TPORO__
#define __TPORO__

#include <iostream>
#include <queue>
#include <string.h>
#include <ctype.h>
using namespace std;

class TPoro{
    
    //friend class TListaPoro;

    // Sobrecarga del operador SALIDA
    friend ostream & operator<<(ostream &, const TPoro &);

    public:
        // Constructor por defecto
        TPoro();
        // Constructor a partir de una posición y un volumen
        TPoro(const int, const int, const double);
        // Constructor a partir de una posición, un volumen y un color
        TPoro(const int, const int, const double, char *);
        // Constructor de copia
        TPoro(const TPoro &);
        // Destructor
        ~TPoro();
        // Sobrecarga del operador asignación
        TPoro & operator=(const TPoro &);
        // Sobrecarga del operador igualdad
        bool operator==(const TPoro &) const;
        // Sobrecarga del operador desigualdad
        bool operator!=(const TPoro &) const;
        // Modifica la posición
        void Posicion(const int, const int);
        // Modifica el volumen
        void Volumen(const double);
        // Modifica el color
        void Color(char *);
        // Devuelve la coordenada x de la posición
        int PosicionX() const;
        // Devuelve la coordenada y de la posición
        int PosicionY() const;
        // Devuelve el volumen
        double Volumen() const;
        // Devuelve el color
        char * Color() const;
        // Devuelve cierto si el poro está vacío
        bool EsVacio() const;
    private:
        // Coordenada x de la posición
        int x;
        // Coordenada y de la posición
        int y;
        // Volumen
        double volumen;
        // Color
        char* color;
        //Método auxiliar
        void Copia(const TPoro &);
        //Método auxiliar
        void minusculas(char* color);
};

#endif