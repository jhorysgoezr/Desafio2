#include "album.h"

album::album():codigo(0),duracion(0),cantidadGeneros(0) {}

album::album(int c, const string &n, const string &f, int d, const string &p):
    codigo(c), nombre(n), fechaLanzamiento(f), duracion(d), portada(p),cantidadGeneros(0)
{
    }

album::album(const album &otro):codigo(otro.codigo), nombre(otro.nombre),fechaLanzamiento(otro.fechaLanzamiento),
        duracion(otro.duracion),portada(otro.portada), cantidadGeneros(otro.cantidadGeneros)
{
    for(int i= 0; i<cantidadGeneros; i++){
        generos[i] = otro.generos[i];
    }

    for (int i = 0; i<otro.canciones.obtenerTamano(); i++){
        canciones.agregar(*otro.canciones.obtener(i));
    }
}
