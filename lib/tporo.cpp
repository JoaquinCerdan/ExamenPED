#include "tporo.h"

// INICIO Funciones auxiliares
void
TPoro::minusculas(char* colorX)
{
    color  = new char[strlen(colorX)];

    for(int i =0; i < strlen(colorX); i++)
    {
        color[i] = tolower(colorX[i]);
    }
    color[strlen(colorX)] = '\0';

       //color = colorX;
}
void
TPoro::Copia(const TPoro &tporo)
{
    this->x = tporo.x;
    this->y = tporo.y;
    this->volumen = tporo.volumen;
    this->color = tporo.color;
}

// FIN funciones auxiliares

// Sobrecarga del operador SALIDA
ostream&
operator<<(ostream &os,const TPoro &tporo)
{
    if(!tporo.EsVacio()){
        os.setf(ios::fixed);
        os.precision( 2 );
        os<<"("<<tporo.PosicionX()<<", "<<tporo.PosicionY()<<") "<<tporo.Volumen()<<" ";
        if(tporo.Color()!=NULL)
            os<<tporo.Color();
        else
            os<<"-";
    }
    else
        os << "()";
    return os;
}
// Constructor por defecto
TPoro::TPoro()
{
    x = 0;
    y = 0;
    volumen = 0;
    color = NULL;
}
// Constructor a partir de una posición y un volumen
TPoro::TPoro(const int x, const int y, const double volumen)
{
    this->x = x;
    this->y = y;
    this->volumen = volumen;
    this->color = NULL;
}
// Constructor a partir de una posición, un volumen y un color
TPoro::TPoro(const int x, const int y, const double volumen, char * color)
{
    this->x = x;
    this->y = y;
    this->volumen = volumen;
    if(color != NULL)
        minusculas(color);
    else
        this->color = color;
}
// Constructor de copia
TPoro::TPoro(const TPoro &tporo)
{
    Copia(tporo);
}
// Destructor
TPoro::~TPoro()
{
    x = 0;
    y = 0;
    volumen = 0;
    color = NULL;
    delete color;
}
// Sobrecarga del operador asignación
TPoro&
TPoro::operator=(const TPoro &tporo)
{
    if(this != &tporo){
        (*this).~TPoro();
        Copia(tporo);
    }

    return *this;
}
// Sobrecarga del operador igualdad
bool
TPoro::operator==(const TPoro &tporo) const
{
    if(tporo.x == x)
        if(tporo.y == y)
            if(tporo.volumen == volumen)
                if(tporo.color != NULL && color != NULL)
                {
                    if(strcmp(tporo.color, color) == 0)
                        return true;
                }
                else if(tporo.color == NULL && color == NULL)
                    return true;
    return false;
}
// Sobrecarga del operador desigualdad
bool
TPoro::operator!=(const TPoro &tporo) const
{
    if(tporo == (*this))
        return false;
    return true;
}
// Modifica la posición
void
TPoro::Posicion(const int x, const int y)
{
    this->x = x;
    this->y = y;
}
// Modifica el volumen
void
TPoro::Volumen(const double volumen)
{
    this->volumen = volumen;
}
// Modifica el color
void
TPoro::Color(char * color)
{
    if(color != NULL)
        minusculas(color);
}
// Devuelve la coordenada x de la posición
int
TPoro::PosicionX() const
{
    return x;
}
// Devuelve la coordenada y de la posición
int
TPoro::PosicionY() const
{
    return y;
}
// Devuelve el volumen
double
TPoro::Volumen() const
{
    return volumen;
}
// Devuelve el color
char*
TPoro::Color() const
{
    return color;
}
// Devuelve cierto si el poro está vacío
bool
TPoro::EsVacio() const
{
    if(x == 0)
        if(y == 0)
            if(volumen == 0)
                if(color == NULL)
                    return true;
    return false;
}