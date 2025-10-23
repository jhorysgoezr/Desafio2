#ifndef ALBUM_H
#define ALBUM_H

#include <estructuras.h>

class album
{
private:
    int codigo;
    string nombre;
    string fechaLanzamiento;
    int duracion;
    Genero generos[4];
    int cantidadGeneros;
    string portada;
    ListaEnlazada<int>canciones;
public:
    album();
    album(int c, const string& n, const string& f, int d, const string& p);
    album(const album& otro);
};

#endif // ALBUM_H
