#include "tvectorporo.h"

void
TVectorPoro::Copia(const TVectorPoro &tvec)
{
    this->dimension = tvec.dimension;
    datos = new TPoro[dimension];
    if(datos == NULL)
        dimension = 0;
    else
    {
        for(unsigned i = 0; i < tvec.dimension; i++)
        {
            datos[i] = tvec.datos[i];
        }
    }

}
ostream&
operator<<(ostream &os, const  TVectorPoro &tvec)
{
    os << "[";
    for(unsigned i=1; i <= tvec.dimension; i++)
    {
        if(i!= 1)
        {
            os << " ";
        }
        os << i << " " << tvec[i];
    }
    os << "]";

    return os;
}
// Constructor por defecto
TVectorPoro::TVectorPoro()
{
    dimension = 0;
    datos = NULL;
    error = TPoro();
}
// Constructor a partir de una dimensión
TVectorPoro::TVectorPoro(const int dimension)
{
    if(dimension <= 0)
    {
        this->dimension = 0;
        datos = NULL;
    }
    else
    {
        this->dimension = dimension;
        datos = new TPoro[this->dimension];
    }
    error = TPoro();
}
// Constructor de copia
TVectorPoro::TVectorPoro(const TVectorPoro &tvec)
{
    dimension = tvec.dimension;
    Copia(tvec);
}
// Destructor
TVectorPoro::~TVectorPoro()
{
    dimension = 0;
    datos = NULL;
    delete datos;
    error.~TPoro();
}
// Sobrecarga del operador asignación
TVectorPoro& 
TVectorPoro::operator=(const TVectorPoro &tvec)
{
    if(this != &tvec)
    {
        (*this).~TVectorPoro();

        dimension = tvec.dimension;
        Copia(tvec);
    }
    return *this;
}
// Sobrecarga del operador igualdad
bool
TVectorPoro::operator==(const TVectorPoro &tvec) const
{
    if(dimension != tvec.dimension)
        return false;
    else
    {
        for(int i = 0; i < dimension; i++)
        {
            if(datos[i] !=tvec.datos[i])
            return false;
        }
    }
    return true;
}
// Sobrecarga del operador desigualdad
bool
TVectorPoro::operator!=(const TVectorPoro &tvec) const
{
    return !(*this == tvec);
}
// Sobrecarga del operador corchete (parte IZQUIERDA)
TPoro&
TVectorPoro::operator[](const int pos)
{
    if(pos >= 1 && pos <= dimension)
        return datos[pos -1];
    else
        return error;
}
// Sobrecarga del operador corchete (parte DERECHA)
TPoro
TVectorPoro::operator[](const int pos) const
{
    if(pos >= 1 && pos <= dimension)
        return datos[pos -1];
    else
        return error;
}
// Devuelve la longitud (dimensión) del vector
int
TVectorPoro::Longitud() const
{
    return dimension;
}
// Devuelve la cantidad de posiciones ocupadas (no vacías) en el vector
int
TVectorPoro::Cantidad() const
{
    TPoro vacio;
    int cont=0;
    for(unsigned i=0; i < dimension; i++)
    {
        if(datos[i]!=vacio)
            cont++;
    }
    return cont;
}
// REDIMENSIONAR el vector de TPoro
bool
TVectorPoro::Redimensionar(const int newTam)
{
    if(newTam<= 0 || newTam == dimension)
        return false;
    if(newTam > dimension)
    {
        TVectorPoro v1(newTam);
        v1.Copia(*this);
        (*this) = v1;
        return true;

    }
    if(newTam < dimension)
    {
        dimension = newTam;
        return true;
    }
    return false;
}