#ifndef __TVECTORPORO__
#define __TVECTORPORO__

#include "tporo.h"

class TVectorPoro {

    // Sobrecarga del operador salida
    friend ostream & operator<<(ostream &, const TVectorPoro &);

    public:
        // Constructor por defecto
        TVectorPoro();
        // Constructor a partir de una dimensión
        TVectorPoro(const int);
        // Constructor de copia
        TVectorPoro(const TVectorPoro &);
        // Destructor
        ~TVectorPoro();
        // Sobrecarga del operador asignación
        TVectorPoro & operator=(const TVectorPoro &);
        // Sobrecarga del operador igualdad
        bool operator==(const TVectorPoro &) const;
        // Sobrecarga del operador desigualdad
        bool operator!=(const TVectorPoro &) const;
        // Sobrecarga del operador corchete (parte IZQUIERDA)
        TPoro & operator[](const int );
        // Sobrecarga del operador corchete (parte DERECHA)
        TPoro operator[](const int ) const;
        // Devuelve la longitud (dimensión) del vector
        int Longitud() const ;
        // Devuelve la cantidad de posiciones ocupadas (no vacías) en el vector
        int Cantidad() const ;
        // REDIMENSIONAR el vector de TPoro
        bool Redimensionar(const int);

    private:
    
        // Dimension del vector
        int dimension;
        // Datos del vector
        TPoro *datos;
        // Para cuando haya error en el operator[]
        TPoro error;
        //Método auxiliar
        void Copia(const TVectorPoro &);
};

#endif