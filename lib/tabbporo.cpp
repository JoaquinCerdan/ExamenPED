#include "tabbporo.h"

//////////////////
//CLASE TNODOABB//
//////////////////

// Constructor por defecto
TNodoABB::TNodoABB (): item(), iz(), de()
{
}
// Constructor de copia
TNodoABB::TNodoABB (const TNodoABB &tnodo): item(tnodo.item), iz(tnodo.iz), de(tnodo.de)
{
}
// Destructor
TNodoABB::~ TNodoABB ()
{
    item.~TPoro();
    iz.~TABBPoro();
    de.~TABBPoro();   
}
// Sobrecarga del operador asignación
TNodoABB&
TNodoABB::operator=(const TNodoABB &tnodo)
{
    if(this != &tnodo)
    {
        (*this).~TNodoABB();
        Copia(tnodo);
    }
    return *this;
}
//Método auxiliar
void
TNodoABB::Copia(const TNodoABB &tnodo)
{
    item = tnodo.item;
    iz = tnodo.iz;
    de = tnodo.de;
}

//////////////////
//CLASE TABBPORO//
//////////////////
void
TABBPoro::Copia(const TABBPoro &tabb)
{
    if(tabb.nodo != NULL)
    {
        TNodoABB *aux = new TNodoABB();
        aux->item = tabb.nodo->item;
        nodo=aux;
        aux->iz.Copia(tabb.nodo->iz);
        aux->de.Copia(tabb.nodo->de);
    }
    else
        nodo = NULL;
}
// Sobrecarga del operador salida
ostream&
operator<<(ostream &os,const TABBPoro &tabb)
{
    os << tabb.Niveles();
    return os;
}
// Constructor por defecto
TABBPoro::TABBPoro()
{
    nodo = NULL;
}
// Constructor de copia
TABBPoro::TABBPoro(const TABBPoro &tabb)
{
    Copia(tabb);
}
// Destructor
TABBPoro::~TABBPoro()
{
    if(!EsVacio())
  {
    nodo->iz.~TABBPoro();
    nodo->de.~TABBPoro();

    delete nodo;
    nodo = NULL;
  }
}
// Sobrecarga del operador asignación
TABBPoro&
TABBPoro::operator=(const TABBPoro &tabb)
{
    if(this != &tabb)
    {
        if(!(*this).EsVacio())
            (*this).~TABBPoro();

        Copia(tabb);
    }
    return *this;
}
// Sobrecarga del operador igualdad
bool
TABBPoro::operator==(const TABBPoro &tabb) const
{
    TVectorPoro izq;
    TPoro aux;

    if(Nodos() == tabb.Nodos())
    {
        izq = tabb.Postorden();

        for(int i = 1; i <= Nodos(); i++)
        {
            if(!Buscar(izq[i]))
                return false;
        }
        return true;
    }
    return false;
}
// Devuelve TRUE si el árbol está vacío, FALSE en caso contrario
bool
TABBPoro::EsVacio() const
{
    return !nodo;
}
//funcion Auxiliar insertarIzq
bool
TABBPoro::insertarIzq(const TPoro &tporo)
{
    if(!nodo->iz.EsVacio())
    {
        nodo->iz.Insertar(tporo);
    }
    else
    {
        TNodoABB *auxN = new TNodoABB();
        TABBPoro auxA;

        (*auxN).item = tporo;
        auxA.nodo = auxN;
        nodo->iz = auxA;

        return true;
    }
    //return false;
}
//funcion Auxiliar insertarDcha
bool
TABBPoro::insertarDcha(const TPoro &tporo)
{
    if(!nodo->de.EsVacio())
    {
        nodo->de.Insertar(tporo);
    }
    else
    {
        TNodoABB *auxN = new TNodoABB();
        TABBPoro auxA;;

        auxN->item = tporo;
        auxA.nodo = auxN;
        nodo->de = auxA;
        return true;
    }
    //return false;
}
// Inserta el elemento en el árbol
bool
TABBPoro::Insertar(const TPoro &tporo)
{
    if(!Buscar(tporo))
    {
        if(EsVacio())
        {
            TNodoABB *aux = new TNodoABB();
            (*aux).item = tporo;
            nodo = aux;
            return true;
        }
        if(tporo.Volumen() < nodo->item.Volumen())
            return insertarIzq(tporo);
        if(tporo.Volumen() > nodo->item.Volumen())
            return insertarDcha(tporo);
    }
    else
        return false;
}
//Devuelve el nodo máximo
TNodoABB*
TABBPoro::Maximo()
{
  if(nodo->de.EsVacio())
    return nodo;

  return nodo->de.Maximo();
}
// Borra el elemento en el árbol
bool
TABBPoro::Borrar(const TPoro &tporo)
{
    if(!Buscar(tporo))
        return false;
    else
    {
        if(nodo->item == tporo)
        {
            if(nodo->iz.EsVacio() && nodo->de.EsVacio())
            {
                nodo = NULL;
                return true;
            }
            if(nodo->iz.EsVacio() && !nodo->de.EsVacio())
            {
                nodo = nodo->de.nodo;
                return true;
            }
            if(!nodo->iz.EsVacio() && nodo->de.EsVacio())
            {
                nodo = nodo->iz.nodo;
                return true;
            }

            TNodoABB *aux = new TNodoABB(*(nodo->iz.Maximo()));
            aux->iz = nodo->iz;
            aux->de = nodo->de;
            nodo = aux;

            return nodo->iz.Borrar((*nodo->iz.Maximo()).item);
        }
        if(nodo->iz.Buscar(tporo))
            nodo->iz.Borrar(tporo);

        nodo->de.Borrar(tporo);
        return true;
    }
}
// Devuelve TRUE si el elemento está en el árbol, FALSE en caso contrario
bool
TABBPoro::Buscar(const TPoro &tporo) const
{
    if(EsVacio())
        return false;
    if(nodo->item.Volumen() > tporo.Volumen())
        nodo->iz.Buscar(tporo);
    else if(nodo->item.Volumen() < tporo.Volumen())
        nodo->de.Buscar(tporo);
    else
        return true;
}
// Devuelve el elemento en la raíz del árbol
TPoro
TABBPoro::Raiz() const
{
    if(EsVacio())
    {
        TPoro aux;
        return aux;
    }

    return (*nodo).item;
}
// Devuelve la altura del árbol (la altura de un árbol vacío es 0)
int
TABBPoro::Altura() const
{
    if(EsVacio())
        return 0;

    return 1 + max((*nodo).de.Altura(), (*nodo).iz.Altura());
}
// Devuelve el número de nodos del árbol (un árbol vacío posee 0 nodos)
int
TABBPoro::Nodos() const
{
    if(EsVacio())
        return 0;

    int nodos = 1;
    nodos += (*nodo).iz.Nodos() + (*nodo).de.Nodos();

    return nodos;
}
// Devuelve el número de nodos hoja en el árbol (la raíz puede ser nodo hoja)
int
TABBPoro::NodosHoja() const
{
    if(EsVacio())
        return 0;

    int nodos = 0;

    if((*nodo).iz.EsVacio() && (*nodo).de.EsVacio())
        nodos += 1;
    nodos += (*nodo).iz.NodosHoja() + (*nodo).de.NodosHoja();

    return nodos;
}
// Devuelve el recorrido en inorden
TVectorPoro
TABBPoro::Inorden() const
{
    // Posición en el vector que almacena el recorrido
    int posicion = 1;
    // Vector del tamaño adecuado para almacenar todos los nodos
    TVectorPoro v(Nodos());
    if(v.Longitud() != 0)
        InordenAux(v, posicion);
    return v;
}
// Devuelve el recorrido en preorden
TVectorPoro
TABBPoro::Preorden() const
{
    // Posición en el vector que almacena el recorrido
    int posicion = 1;
    // Vector del tamaño adecuado para almacenar todos los nodos
    TVectorPoro v(Nodos());
    if(v.Longitud() != 0)
        PreordenAux(v, posicion);
    return v;
}
// Devuelve el recorrido en postorden
TVectorPoro
TABBPoro::Postorden() const
{
    // Posición en el vector que almacena el recorrido
    int posicion = 1;
    // Vector del tamaño adecuado para almacenar todos los nodos
    TVectorPoro v(Nodos());
    if(v.Longitud() != 0)
        PostordenAux(v, posicion);
    return v;
}
// Devuelve el recorrido en niveles
TVectorPoro
TABBPoro::Niveles() const
{
    queue <TABBPoro> myqueue;
    TVectorPoro v(Nodos());
    TABBPoro aux;

    myqueue.push(*this);
    int cont = 1;

    if(!(*this).EsVacio())
    {
        while(!myqueue.empty())
        {
            aux = myqueue.front();
            v[cont] = aux.Raiz();
            myqueue.pop();

            if(!aux.nodo->iz.EsVacio())
                myqueue.push(aux.nodo->iz);
            if(!aux.nodo->de.EsVacio())
                myqueue.push(aux.nodo->de);
            cont++;
        }
    }

    return v;
}
// Suma de dos ABB
TABBPoro
TABBPoro::operator+(const TABBPoro &tabb)
{
    TABBPoro aux(*this);
    TVectorPoro inorden = tabb.Inorden();
    for(int i = 1; i <= inorden.Longitud(); i++)
        aux.Insertar(inorden[i]);

    return aux;   
}
// Resta de dos ABB
TABBPoro
TABBPoro::operator-(const TABBPoro &tabb)
{
    TABBPoro aux;
    TVectorPoro inorden = Inorden();
    for(int i = 1; i <= inorden.Longitud(); i++)
    {
        if(!tabb.Buscar(inorden[i]))
            aux.Insertar(inorden[i]);
    }
        
    return aux;   
}

// AUXILIAR : Devuelve el recorrido en inorden
void
TABBPoro::InordenAux(TVectorPoro &tvec, int &pos) const
{
    if(nodo != NULL){
		nodo->iz.InordenAux(tvec,pos);

		tvec[pos] = nodo->item;
		pos++;

		nodo->de.InordenAux(tvec,pos);
	}
}
// AUXILIAR : Devuelve el recorrido en preorden
void
TABBPoro::PreordenAux(TVectorPoro &tvec, int &pos) const
{
    if(nodo != NULL){
        tvec[pos] = nodo->item;
        pos++;

        nodo->iz.PreordenAux(tvec,pos);
        nodo->de.PreordenAux(tvec,pos);
    }
}
// AUXILIAR : Devuelve el recorrido en postorden
void
TABBPoro::PostordenAux(TVectorPoro &tvec, int &pos) const
{
    if(nodo != NULL){
        nodo->iz.PostordenAux(tvec,pos);
        nodo->de.PostordenAux(tvec,pos);

        tvec[pos] = nodo->item;
        pos++;
    }
}