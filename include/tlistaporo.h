#ifndef __TLISTAPORO__
#define __TLISTAPORO__

#include "tvectorporo.h"

class TListaNodo
{
    friend class TListaPosicion;
    friend class TListaPoro;
    
    public:
        // Constructor por defecto
        TListaNodo ();
        // Constructor de copia
        TListaNodo (const TListaNodo &);
        // Destructor
        ~TListaNodo ();
        // Sobrecarga del operador asignación
        TListaNodo & operator=(const TListaNodo &);
    private:
        // El elemento del nodo
        TPoro e;
        // El nodo anterior
        TListaNodo *anterior;
        // El nodo siguiente
        TListaNodo *siguiente;
        //Método auxiliar
        void
        Copia(const TListaNodo &tnodo);
};

class TListaPosicion {

    friend class TListaPoro;
    friend class TListaNodo;

    public:
        // Constructor por defecto
        TListaPosicion ();
        // Constructor de copia
        TListaPosicion (const TListaPosicion &);
        // Destructor
        ~TListaPosicion ();
        // Sobrecarga del operador asignación
        TListaPosicion& operator=(const TListaPosicion &);
        // Sobrecarga del operador igualdad
        bool operator==(const TListaPosicion &) const;
        // Devuelve la posición anterior
        TListaPosicion Anterior() const;
        // Devuelve la posición siguiente
        TListaPosicion Siguiente() const;
        // Devuelve TRUE si la posición no apunta a una lista, FALSE en caso contrario
        bool EsVacia() const;
    private:
        // Para implementar la POSICIÓN a NODO de la LISTA de TPoro
        TListaNodo *pos;
        // Sobrecarga del operador desigualdad
        bool operator!=(const TListaPosicion &) const;
};

class TListaPoro {

    // Sobrecarga del operador salida
    friend ostream & operator<<(ostream &, const TListaPoro &);

    public:
        // Constructor por defecto
        TListaPoro();
        // Constructor de copia
        TListaPoro (TListaPoro &);
        // Destructor
        ~TListaPoro ();
        // Sobrecarga del operador asignación
        TListaPoro & operator=(const TListaPoro &);
        // Sobrecarga del operador igualdad
        bool operator==(const TListaPoro &) const;
        // Sobrecarga del operador suma
        TListaPoro operator+(const TListaPoro &);
        // Sobrecarga del operador resta
        TListaPoro operator-(const TListaPoro &);
        // Devuelve true si la lista está vacía, false en caso contrario
        bool EsVacia() const;
        // Inserta el elemento en la lista
        bool Insertar(const TPoro &);
        // Busca y borra el elemento
        bool Borrar(const TPoro &);
        // Borra el elemento que ocupa la posición indicada
        bool Borrar(const TListaPosicion &);
        // Obtiene el elemento que ocupa la posición indicada
        TPoro Obtener(const TListaPosicion &) const;
        // Devuelve true si el elemento está en la lista, false en caso contrario
        bool Buscar(const TPoro &) const;
        // Devuelve la longitud de la lista
        int Longitud() const;
        // Devuelve la primera posición en la lista
        TListaPosicion Primera() const;
        // Devuelve la última posición en la lista
        TListaPosicion Ultima() const;
        // Extraer un rango de nodos de la lista
        TListaPoro ExtraerRango (const int, const int);
    private:
        // Primer elemento de la lista
        TListaNodo *primero;
        // Ultimo elemento de la lista
        TListaNodo *ultimo;
};


#endif