#include "tavlporo.h"

//////////////////
//CLASE TNODOAVL//
//////////////////

//Constructor por defecto
TNodoAVL::TNodoAVL (): item(), iz(), de(),fe(0)
{
  //fe = 0;
}
//Constructor copia
TNodoAVL::TNodoAVL (const TNodoAVL &tnodo): item(tnodo.item), iz(tnodo.iz), de(tnodo.de), fe(tnodo.fe)
{
}
//Destructor
TNodoAVL::~TNodoAVL ()
{
  item.~TPoro();
  iz.~TAVLPoro();
  de.~TAVLPoro(); 
}
// Sobrecarga del operador asignación
TNodoAVL&
TNodoAVL::operator=(const TNodoAVL &tnodo)
{
  if(this != &tnodo)
  {
    (*this).~TNodoAVL();

    item = tnodo.item;
    iz = tnodo.iz;
    de = tnodo.de;
  }

  return *this;
}

//////////////////
//CLASE TAVLPORO//
//////////////////

//Devuelve el nodo máximo
TNodoAVL*
TAVLPoro::Maximo()
{
  if(raiz->de.EsVacio())
    return raiz;

  return raiz->de.Maximo();
}
//Clase auxiliar
void
TAVLPoro::Copia(const TAVLPoro &tavl)
{
  if(!tavl.EsVacio())
  {
    TNodoAVL *aux = new TNodoAVL();
  	aux->fe = tavl.raiz->fe;
    (*aux).item = tavl.raiz->item;
    raiz=aux;
  	aux->iz.Copia(tavl.raiz->iz);
  	aux->de.Copia(tavl.raiz->de);
  }
  else
    raiz= NULL;
}
// AUXILIAR: Devuelve el recorrido en inorden
void
TAVLPoro::InordenAux(TVectorPoro &tvec, int &pos) const 
{
  if(raiz != NULL){
		raiz->iz.InordenAux(tvec,pos);

		tvec[pos] = raiz->item;
		pos++;

		raiz->de.InordenAux(tvec,pos);
	}
}
// AUXILIAR: Devuelve el recorrido en preorden
void
TAVLPoro::PreordenAux(TVectorPoro &tvec, int &pos) const
{
  if(raiz != NULL){
    tvec[pos] = raiz->item;
    pos++;

    raiz->iz.PreordenAux(tvec,pos);
    raiz->de.PreordenAux(tvec,pos);
  }
}
// AUXILIAR: Devuelve el recorrido en postorden
void
TAVLPoro::PostordenAux(TVectorPoro &tvec, int &pos) const
{
  if(raiz != NULL){
    raiz->iz.PostordenAux(tvec,pos);
    raiz->de.PostordenAux(tvec,pos);

    tvec[pos] = raiz->item;
    pos++;
  }
}
// Sobrecarga del operador salida
ostream&
operator<<(ostream &os,const TAVLPoro &tavl)
{
  os << tavl.Inorden();
  return os;
}
//Constructor por defecto
TAVLPoro::TAVLPoro ()
{
  raiz = NULL;
}
//Constructor de copia
TAVLPoro::TAVLPoro (const TAVLPoro &tavl)
{
  Copia(tavl);
}
//Destructor
TAVLPoro::~ TAVLPoro ()
{
  if(!EsVacio())
  {
    raiz->iz.~TAVLPoro();
    raiz->de.~TAVLPoro();

    delete raiz;
    raiz = NULL;
  }
}
// Sobrecarga del operador asignación
TAVLPoro&
TAVLPoro::operator=(const TAVLPoro &tavl)
{
  if(this != &tavl)
  {
    if(!(*this).EsVacio())
      (*this).~TAVLPoro();

    Copia(tavl);
  }
  return *this;
}
// Sobrecarga del operador igualdad
bool
TAVLPoro::operator==(const TAVLPoro &tavl) const
{
  TVectorPoro izq;
  TPoro aux;
  if(Nodos() == tavl.Nodos())
  {
    izq = tavl.Preorden();

    for(int i = 1; i <= Nodos(); i++)
    {
      if(!Buscar(izq[i]))
        return false;
    }
    return true;
  }
  return false;
  
}
// Sobrecarga del operador desigualdad
bool
TAVLPoro::operator!=(const TAVLPoro &tavl) const
{
  if((*this) == tavl)
    return false;
  return true;
}
// Devuelve TRUE si el árbol está vacío, FALSE en caso contrario
bool
TAVLPoro::EsVacio() const
{
  return !raiz;
}
void
TAVLPoro::EquilibrarIzq(const bool &estado)
{
  //Rotación II
  if(raiz->iz.raiz->fe == -1 || estado)
  {
    TNodoAVL *j = raiz;

    raiz = j->iz.raiz;
    j->iz.raiz = (*raiz).de.raiz;
    (*raiz).de.raiz = j;

    if(raiz->fe != 0)
    {
      (*raiz).de.raiz->fe = (*raiz).fe = 0;
    }
    else
    {
      (*raiz).de.raiz->fe = -1;
      (*raiz).fe = 1;
    }
  }
  //Rotación ID
  else
  {
    TNodoAVL *j = raiz;
    TNodoAVL *i,*k;

    raiz = (*raiz).iz.raiz->de.raiz;
    i = (*raiz).iz.raiz;
    k = (*raiz).de.raiz;
    raiz->iz.raiz = j->iz.raiz;
    raiz->de.raiz = j;
    j->iz.raiz = k;
    raiz->iz.raiz->de.raiz = i;

    if((*raiz).fe == 0)
      (*raiz).iz.raiz->fe = (*raiz).de.raiz->fe = (*raiz).fe = 0;
    else
    {
      if((*raiz).fe != -1)
		  {
        (*raiz).iz.raiz->fe = -1;
        (*raiz).de.raiz->fe = (*raiz).fe = 0;
      }
      else
      {
        (*raiz).de.raiz->fe = 1;
        (*raiz).iz.raiz->fe = (*raiz).fe = 0;
      }
    }
  }
}
void
TAVLPoro::EquilibrarDcha(const bool &estado)
{
  //Rotación DD 
  if(raiz->de.raiz->fe == 1 || estado)
  {
    TNodoAVL *j = raiz;

    raiz = j->de.raiz;
    j->de.raiz = (*raiz).iz.raiz;
    (*raiz).iz.raiz = j;

    if((*raiz).fe != 0)
    {
      (*raiz).iz.raiz->fe = (*raiz).fe =  0;
    }
    else
    {
      (*raiz).iz.raiz->fe = 1;
      (*raiz).fe = -1;
    }
  }
  //Rotación DI
  else
  {
    TNodoAVL *j = raiz;
    TNodoAVL *i,*k;

    raiz = (*raiz).de.raiz->iz.raiz;
    i = (*raiz).iz.raiz;
    k = (*raiz).de.raiz;
    (*raiz).de.raiz = j->de.raiz;
    (*raiz).iz.raiz = j;
    j->de.raiz = i;
    (*raiz).de.raiz->iz.raiz = k;

    if((*raiz).fe == 0)
      (*raiz).iz.raiz->fe = (*raiz).de.raiz->fe = (*raiz).fe = 0;
    else
    {
      if((*raiz).fe != -1)
      {
        (*raiz).iz.raiz->fe = -1;
        (*raiz).de.raiz->fe = (*raiz).fe = 0;
      }
      else
      {
        (*raiz).de.raiz->fe = 1;
        (*raiz).iz.raiz->fe = (*raiz).fe = 0;
      }
    }
  }
}
// Inserta el elemento en el árbol
bool
TAVLPoro::InsertarAux(const TPoro &tporo, bool &crece)
{
  bool creceIzq = false, creceDcha = false, creceHijo = false;
  if(EsVacio())
  {
    TNodoAVL* aux = new TNodoAVL();
    aux->item = tporo;
    aux->fe = 0;
    raiz = aux;
    crece = true;
  }
  else
  {
    if(tporo.Volumen() < raiz->item.Volumen())
    {
      raiz->iz.InsertarAux(tporo, creceIzq);
      creceHijo = creceIzq;
    }
    else if(tporo.Volumen() > raiz->item.Volumen())
    {
      raiz->de.InsertarAux(tporo, creceDcha);
      creceHijo = creceDcha;
    }

    if(creceHijo)
    {
      if((creceIzq && raiz->fe==1) || (creceDcha && raiz->fe==-1))
      {
        crece = false;
        raiz->fe = 0;
      }
      else if(creceIzq && raiz->fe==0)
      {
        crece = true;
        raiz->fe = -1;
      }
      else if(creceDcha && raiz->fe==0)
      {
        crece = true;
        raiz->fe = 1;
      }
      else if(creceIzq && raiz->fe==-1)
      {
        EquilibrarIzq(false);
      }
      else if(creceDcha && raiz->fe==1)
      {
        EquilibrarDcha(false);
      }
    }
  }
  return crece;
}
// Inserta el elemento TPoro en el árbol
bool
TAVLPoro::Insertar(const TPoro &tporo)
{
  bool crece, aux;
  aux = InsertarAux(tporo, crece);

  return aux;
}
// Devuelve TRUE si el elemento está en el árbol, FALSE en caso contrario
bool
TAVLPoro::Buscar(const TPoro &tporo) const
{
    if(EsVacio())
      return false;
    if(raiz->item == tporo)
      return true;
    if(raiz->item.Volumen() > tporo.Volumen())
      return raiz->iz.Buscar(tporo);
    if(raiz->item.Volumen() < tporo.Volumen())
      return raiz->de.Buscar(tporo);
    return false;
}
// Borra un elemento TPoro del árbol AVL
bool
TAVLPoro::BorrarAux(const TPoro &tporo, bool &decrece)
{
  bool decreceHijoIz=false, decreceHijoDe=false, borraOK=false;

  if(!Buscar(tporo))
    return false;
  else
  {
    if((*raiz).item == tporo)
    {
      if((*raiz).iz.EsVacio() && (*raiz).de.EsVacio())
      {
        raiz= NULL;
        borraOK = decrece = true;
        return true;
      }
      if((*raiz).iz.EsVacio() && !(*raiz).de.EsVacio())
      {
        raiz= (*raiz).de.raiz;
        borraOK = decrece = true;
        return true;
      }
      if(!(*raiz).iz.EsVacio() && (*raiz).de.EsVacio())
      {
        raiz= (*raiz).iz.raiz;
        borraOK = decrece = true;
        return true;
      }

      TNodoAVL *aux = new TNodoAVL(*((*raiz).iz.Maximo()));


      aux->iz = raiz->iz;
      aux->de = raiz->de;
      aux->fe = raiz->fe;

      raiz= aux;

      borraOK = (*raiz).iz.BorrarAux((*(*raiz).iz.Maximo()).item, decreceHijoIz);
    }
    if((*raiz).iz.Buscar(tporo))
      borraOK = (*raiz).iz.BorrarAux(tporo, decreceHijoIz);
    if((*raiz).de.Buscar(tporo))
      borraOK = (*raiz).de.BorrarAux(tporo, decreceHijoDe);
  }

  if(borraOK)
  {
    raiz->fe = raiz->de.Altura() - raiz->iz.Altura();
    TNodoAVL *auxIz = raiz->iz.raiz;
    TNodoAVL *auxDe = raiz->de.raiz;


		if (raiz->fe == 2 && ((auxDe->fe == 0) || (auxDe->fe == 1)))
				EquilibrarDcha(true);

		if(raiz->fe == 2 && auxDe->fe == -1)
				EquilibrarDcha(false);

    if (raiz->fe == -2 && ((auxIz->fe == 0) || (auxIz->fe == -1)))
        EquilibrarIzq(true);

		if(raiz->fe == -2 && auxIz->fe == 1)
				EquilibrarIzq(false);
  }

  return borraOK;
}
// Borra un elemento TPoro del árbol AVL
bool
TAVLPoro::Borrar(const TPoro &tporo)
{
  
  bool decrece = false;
  return BorrarAux(tporo, decrece);
  
}
// Devuelve la altura del árbol (la altura de un árbol vacío es 0)
int
TAVLPoro::Altura() const
{
  if(EsVacio())
    return 0;

  return 1 + max(raiz->de.Altura(), raiz->iz.Altura());
}
// Devuelve el elemento TPoro raíz del árbol AVL
TPoro
TAVLPoro::Raiz() const
{
  if(EsVacio())
  {
    TPoro aux;
    return aux;
  }

  return raiz->item;
}
// Devuelve el número de nodos del árbol (un árbol vacío posee 0 nodos)
int
TAVLPoro::Nodos() const
{
  if(EsVacio())
    return 0;

  int nodos = 1;
  nodos += raiz->iz.Nodos() + raiz->de.Nodos();

  return nodos;
}
// Devuelve el número de nodos hoja en el árbol (la raíz puede ser nodo hoja)
int
TAVLPoro::NodosHoja() const
{
  if(EsVacio())
    return 0;

  int nodos = 0;

  if(raiz->iz.EsVacio() && raiz->de.EsVacio())
    nodos += 1;
  nodos += raiz->iz.NodosHoja() + raiz->de.NodosHoja();

  return nodos;
}
// Devuelve el recorrido en Inorden sobre un vector
TVectorPoro
TAVLPoro::Inorden() const
{
  // Posición en el vector que almacena el recorrido
  int posicion = 1;
  // Vector del tamaño adecuado para almacenar todos los nodos
  TVectorPoro v(Nodos());
  if(v.Longitud() != 0)
    InordenAux(v, posicion);
  return v;
}
// Devuelve el recorrido en Preorden sobre un vector
TVectorPoro
TAVLPoro::Preorden() const
{
  // Posición en el vector que almacena el recorrido
  int posicion = 1;
  // Vector del tamaño adecuado para almacenar todos los nodos
  TVectorPoro v(Nodos());
  if(v.Longitud() != 0)
    PreordenAux(v, posicion);
  return v;
}
// Devuelve el recorrido en Postorden sobre un vector
TVectorPoro
TAVLPoro::Postorden() const
{
  // Posición en el vector que almacena el recorrido
  int posicion = 1;
  // Vector del tamaño adecuado para almacenar todos los nodos
  TVectorPoro v(Nodos());
  if(v.Longitud() != 0)
    PostordenAux(v, posicion);
  return v;
}