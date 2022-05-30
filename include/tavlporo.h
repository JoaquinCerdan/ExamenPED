#ifndef _TAVLPORO_
#define _TAVLPORO_

#include "tvectorporo.h"

class TNodoAVL;

class TAVLPoro
{
    friend class TNodoAVL;

    // Sobrecarga del operador salida
    friend ostream & operator<<(ostream &,const TAVLPoro &);

    public:
        //Constructor por defecto
        TAVLPoro ();
        //Constructor de copia
        TAVLPoro (const TAVLPoro &);
        //Destructor
        ~ TAVLPoro ();
        // Sobrecarga del operador asignación
        TAVLPoro & operator=(const TAVLPoro &);
        // Sobrecarga del operador igualdad
        bool operator==(const TAVLPoro &) const;
        // Sobrecarga del operador desigualdad
        bool operator!=(const TAVLPoro &) const;
        // Devuelve TRUE si el árbol está vacío, FALSE en caso contrario
        bool EsVacio() const;
        // Inserta el elemento TPoro en el árbol
        bool Insertar(const TPoro &);
        // Devuelve TRUE si el elemento está en el árbol, FALSE en caso contrario
        bool Buscar(const TPoro &) const;
        // Borra un elemento TPoro del árbol AVL
        bool Borrar(const TPoro &);
        // Devuelve la altura del árbol (la altura de un árbol vacío es 0)
        int Altura() const;
        // Devuelve el elemento TPoro raíz del árbol AVL
        TPoro Raiz() const;
        // Devuelve el número de nodos del árbol (un árbol vacío posee 0 nodos)
        int Nodos() const;
        // Devuelve el número de nodos hoja en el árbol (la raíz puede ser nodo hoja)
        int NodosHoja() const;
        // Devuelve el recorrido en Inorden sobre un vector
        TVectorPoro Inorden() const;
        // Devuelve el recorrido en Preorden sobre un vector
        TVectorPoro Preorden() const;
        // Devuelve el recorrido en Postorden sobre un vector
        TVectorPoro Postorden() const;

    private:
        // Puntero al nodo raíz
        TNodoAVL *raiz;
        // AUXILIAR: Devuelve el recorrido en inorden
        void InordenAux(TVectorPoro &, int &) const;
        // AUXILIAR: Devuelve el recorrido en preorden
        void PreordenAux(TVectorPoro &, int &) const;
        // AUXILIAR: Devuelve el recorrido en postorden
        void PostordenAux(TVectorPoro &, int &) const;
        //Función auxiliar
        void Copia(const TAVLPoro &);
        //Busca el Maximo
        TNodoAVL* Maximo();
        //Función auxiliar para las inserciones
        bool
        BorrarAux(const TPoro &, bool &);
        //Función auxiliar para las inserciones
        bool
        InsertarAux(const TPoro &, bool &);
        //Funciones auxiliares para las rotaciones
        void
        EquilibrarIzq(const bool &);
        void
        EquilibrarDcha(const bool &);
        
};

class TNodoAVL
{
    friend class TAVLPoro;

    public:
        //Constructor por defecto
        TNodoAVL ();
        //Constructor copia
        TNodoAVL (const TNodoAVL &);
        //Destructor
        ~TNodoAVL ();
        // Sobrecarga del operador asignación
        TNodoAVL & operator=(const TNodoAVL &);

    private:
        // El elemento del nodo
        TPoro item;
        // Subárbol izquierdo y derecho
        TAVLPoro iz, de;
        // Factor de equilibrio
        int fe;
};

#endif