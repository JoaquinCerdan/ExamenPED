#include "tlistaporo.h"

//////////////////
//CLASE TLISTANODO
//////////////////
void
TListaNodo::Copia(const TListaNodo &tnodo)
{
    e = TPoro(tnodo.e);
    anterior = tnodo.anterior;
    siguiente = tnodo.siguiente;
}
// Constructor por defecto
TListaNodo::TListaNodo()
{
    e = TPoro();
    siguiente = NULL;
    anterior = NULL;

}
// Constructor de copia
TListaNodo::TListaNodo(const TListaNodo &tnodo)
{
    Copia(tnodo);
}
// Destructor
TListaNodo::~TListaNodo ()
{
    e.~TPoro();
    siguiente = NULL;
    anterior = NULL;
    delete siguiente, anterior;
}
// Sobrecarga del operador asignación
TListaNodo&
TListaNodo::operator=(const TListaNodo &tnodo)
{
    if(this != &tnodo)
    {
        (*this).~TListaNodo();
        Copia(tnodo);
    }
    return *this;
}

//////////////////////
//CLASE TLISTAPOSICION
//////////////////////

// Sobrecarga del operador igualdad
bool
TListaPosicion::operator!=(const TListaPosicion &tpos) const
{
    if(pos != tpos.pos)
        return true;
    return false;
}
// Constructor por defecto
TListaPosicion::TListaPosicion ()
{
    pos = NULL;
}
// Constructor de copia
TListaPosicion::TListaPosicion (const TListaPosicion &tpos)
{
    pos = tpos.pos;
}
// Destructor
TListaPosicion::~TListaPosicion ()
{
    pos = NULL;
    delete pos;
}
// Sobrecarga del operador asignación
TListaPosicion&
TListaPosicion::operator=(const TListaPosicion &tpos)
{
    if(this != &tpos)
    {
    (*this).~TListaPosicion();

    pos = tpos.pos;
    }

    return *this;
}
// Sobrecarga del operador igualdad
bool
TListaPosicion::operator==(const TListaPosicion &tpos) const
{
    if(pos == tpos.pos)
        return true;
    return false;
}
// Devuelve la posición anterior
TListaPosicion
TListaPosicion::Anterior() const
{
   TListaPosicion aux;

    if(this->pos == NULL)
        return aux;

    aux.pos = this->pos->anterior;

    return aux; 
}
// Devuelve la posición siguiente
TListaPosicion
TListaPosicion::Siguiente() const
{
    TListaPosicion aux;

    if(this->pos == NULL)
        return aux;

    aux.pos = this->pos->siguiente;

    return aux;
}
// Devuelve TRUE si la posición no apunta a una lista, FALSE en caso contrario
bool
TListaPosicion::EsVacia() const
{
  if(pos == NULL)
    return true;
    
  return false;
}

//////////////////
//CLASE TLISTAPORO
//////////////////

// Sobrecarga del operador salida
ostream&
operator<<(ostream &os, const TListaPoro &tlista)
{
    TListaPosicion aux;
    aux = tlista.Primera();
    os << "(";
    if(tlista.Longitud() == 0)
    {
        os << ")";
        return os;
    }
    os << tlista.Obtener(aux);
    for(unsigned i = 1; i < tlista.Longitud(); i++)
    {
        aux = aux.Siguiente();
        os << " " << tlista.Obtener(aux);
    }
    os << ")";
    return os;
}
// Constructor por defecto
TListaPoro::TListaPoro()
{
    primero = NULL;
    ultimo = NULL;
    
}
// Constructor de copia
TListaPoro::TListaPoro (TListaPoro &tlista)
{
    primero = NULL;
    ultimo = NULL;
    *this = tlista;
}
// Destructor
TListaPoro::~TListaPoro ()
{
    TListaPosicion prim;
    prim = Primera();

    while(!prim.EsVacia())
    {
        prim = prim.Siguiente();
    }
    delete primero;

    primero = NULL; 
}
// Sobrecarga del operador asignación
TListaPoro&
TListaPoro::operator=(const TListaPoro &tlista)
{
  if(this != &tlista)
  {
    (*this).~TListaPoro();

    TListaNodo *aux = tlista.primero;

    while(aux != NULL)
    {
      Insertar((*aux).e);
      aux = (*aux).siguiente;
    }
  }
  return (*this);
}
// Sobrecarga del operador igualdad
bool
TListaPoro::operator==(const TListaPoro &tlista) const
{
    TListaNodo *izq = primero;
    TListaNodo *dcha = tlista.primero;

    if((*this).Longitud() != tlista.Longitud())
        return false;
    for(int i = 0; i < (*this).Longitud(); i++)
    {
        if(izq != dcha)
            return false;

        izq = izq->siguiente;
        dcha = dcha->siguiente;
    }
    return true;
}
// Sobrecarga del operador suma
TListaPoro
TListaPoro::operator+(const TListaPoro &tlista)
{
    TListaPoro aux;
    aux = *this;
    TListaNodo *primero;
    primero = tlista.primero;

    while(primero != NULL)
    {
        aux.Insertar((*primero).e);
        primero = (*primero).siguiente;
    }

    return aux;
}
// Sobrecarga del operador resta
TListaPoro
TListaPoro::operator-(const TListaPoro &tlista)
{
    TListaPoro aux;
    TListaNodo *prim = (*this).primero;

    while(prim != NULL)
    {
        if(!tlista.Buscar((*prim).e))
            aux.Insertar((*prim).e);

        prim = (*prim).siguiente;
    }

    return aux;
}
// Devuelve true si la lista está vacía, false en caso contrario
bool
TListaPoro::EsVacia() const
{
if(primero == NULL)
    if(ultimo == NULL)
        return true;
  return false;
}
// Inserta el elemento en la lista
bool
TListaPoro::Insertar(const TPoro &tporo)
{
    TListaNodo *aux = new TListaNodo();
    aux->e = tporo;

    if(Buscar(tporo))
        return false;

    if(EsVacia())
    {
        primero = aux;
        ultimo = aux;
        return true;
    }
    else
    {
        TListaPosicion inicio = Primera();

        while(!inicio.EsVacia())
        {
            //Si el poro la posición donde nos encontramos es mayor que el poro a insertar
            if(tporo.Volumen() < inicio.pos->e.Volumen())
            {
                //Si la primera posición es mayor que la que se va a insertar
                if(inicio == Primera())
                {
                    //Apuntamos en siguiente del Nodo a insertar la antigua primera posición
                    aux->siguiente = this->primero;
                    //Guardamos en primero el nuevo Nodo
                    this->primero->anterior = aux;
                    primero = aux;
                    return true;
                }
            }
            //Si el poro la posición donde nos encontramos es mayor/igual que el poro a insertar
            else
            {
                //Si la siguiente posicion es vacia insertamos en la siguiente
                if(inicio == Ultima())
                {
                    aux->siguiente = inicio.Siguiente().pos;
                    aux->anterior = inicio.pos;
                    inicio.pos->siguiente = aux;
                    ultimo = aux;

                    return true;
                }
                //Si la posición siguiente es mayor que la del poro a insertar
                if(tporo.Volumen() <= inicio.Siguiente().pos->e.Volumen())
                {
                    aux->siguiente = inicio.pos->siguiente;
                    aux->anterior = inicio.pos;
                    inicio.pos->siguiente = aux;
                    aux->siguiente->anterior = aux;
                    return true;
                }
            }
            inicio = inicio.Siguiente();
        }
    }
    return false;
}
// Busca y borra el elemento
bool
TListaPoro::Borrar(const TPoro &tporo)
{

    
    if(!Buscar(tporo))
        return false;
    
    TListaPosicion aux;

    aux = Primera();

    for(int i = 0; i < (*this).Longitud(); i++)
    {
        
        if(aux.pos->e == tporo)
        {
            if(aux.pos == ultimo && ultimo == primero)
            {
                ultimo = NULL;
                primero = NULL;

                aux.pos->~TListaNodo();
                
                return true;
            }
            if(aux.pos == ultimo)
            {
                
                //ultimo->anterior->siguiente = ultimo->siguiente;
                ultimo = aux.pos->anterior;

                aux.pos->~TListaNodo();
                
                return true;
            }
            if(aux.pos == primero)
            {
                aux.pos->siguiente->anterior = NULL;
                primero = aux.pos->siguiente;

                aux.pos->~TListaNodo();
                return true;
            }
            TListaNodo *antes, *despues;
            antes = aux.pos->siguiente->anterior;
            despues = aux.pos->anterior->siguiente;

            antes->siguiente = despues;
            despues->anterior = antes;

            aux.pos->~TListaNodo();
            return true;
        }
        aux = aux.Siguiente();
        
    }
    return false;
}
// Borra el elemento que ocupa la posición indicada
bool
TListaPoro::Borrar(const TListaPosicion &tpos)
{
    if(tpos.EsVacia()){
        return false;
    }
    if(tpos.pos == ultimo && ultimo == primero)
    {
        ultimo = NULL;
        primero = NULL;

        tpos.pos->~TListaNodo();
        
        return true;
    }
    if(tpos.pos == ultimo)
    {
        ultimo = tpos.pos->anterior;
        ultimo->siguiente = NULL;

        tpos.~TListaPosicion();
        return true;
    }
    if(tpos.pos == primero)
    {
        primero = tpos.pos->siguiente;
        primero->anterior = NULL;

        tpos.~TListaPosicion();
        return true;
    }

    tpos.pos->siguiente->anterior = tpos.pos->anterior;
    tpos.pos->anterior->siguiente = tpos.pos->siguiente;

    tpos.~TListaPosicion();
    return true;
}
// Obtiene el elemento que ocupa la posición indicada
TPoro
TListaPoro::Obtener(const TListaPosicion &tpos) const
{
    TPoro tporo;

    if(!tpos.EsVacia())
    {
        tporo = tpos.pos->e;
    }
    
    return tporo;
}
// Devuelve true si el elemento está en la lista, false en caso contrario
bool
TListaPoro::Buscar(const TPoro &tporo) const
{
    TListaNodo *primero = (*this).primero;

    if((*this).EsVacia())
        return false;
    do
    {
        if(primero->e == tporo)
            return true;
        primero = (*primero).siguiente;
    }while(primero != NULL);

    return false; 
}
// Devuelve la longitud de la lista
int
TListaPoro::Longitud() const
{
    TListaPosicion aux = Primera();
    int i=0;

    for(i; !aux.EsVacia(); i++)
        aux = aux.Siguiente();

    return i;
}
// Devuelve la primera posición en la lista
TListaPosicion
TListaPoro::Primera() const
{
    TListaPosicion aux;
    aux.pos = primero;

    return aux;
}
// Devuelve la última posición en la lista
TListaPosicion
TListaPoro::Ultima() const
{
    TListaPosicion aux;
    aux.pos = ultimo;

    return aux;
}
// Extraer un rango de nodos de la lista
TListaPoro
TListaPoro::ExtraerRango (const int n1, const int n2)
{
    TListaPoro aux;
    TListaNodo *prim;

    prim = primero;
    int i = 1;

    while(prim!= NULL && i < n1)
    {
        prim = prim->siguiente;
        i++;
    }
    while(prim!= NULL && i <= n2)
    {
        aux.Insertar(prim->e);
        Borrar(prim->e);

        prim = prim->siguiente;
        i++;
    }

    return aux;
}
