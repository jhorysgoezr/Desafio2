#include "listafavoritos.h"

listaFavoritos::listaFavoritos(): capacidadMaxima(10000) {}

listaFavoritos::listaFavoritos(const listaFavoritos &otro): capacidadMaxima(otro.capacidadMaxima)
{
    for(int i = 0; i < otro.canciones.obtenerTamano(); i++){
        canciones.agregar(*otro.canciones.obtener(i));
    }
}

bool listaFavoritos::agregarCancion(int idCancion)
{
    if(canciones.obtenerTamano() >= capacidadMaxima){
        return false;
    }
    if (canciones.buscar(idCancion)){
        return false;
    }
    canciones.agregar(idCancion);
    return true;
}

bool listaFavoritos::eliminarCancion(int idCancion)
{
    return canciones.eliminar(idCancion);
}

bool listaFavoritos::tieneCancion(int idCancion) const
{
    return canciones.buscar(idCancion);
}

int listaFavoritos::obtenerTamano() const
{
    return canciones.obtenerTamano();
}

int listaFavoritos::obtenerCancion(int indice) const
{
    int* cancion =canciones.obtener(indice);
    return cancion ? *cancion : -1;
}

bool listaFavoritos::estaVacia() const
{
    return canciones.estaVacia();
}

void listaFavoritos::agregarLista(const listaFavoritos &otraLista)
{
    for(int i = 0; i< otraLista.obtenerTamano(); i++){
        int idCancion = otraLista.obtenerCancion(i);
        if(!canciones.buscar(idCancion) && canciones.obtenerTamano() < capacidadMaxima){
            canciones.agregar(idCancion);
        }
    }
}

listaFavoritos &listaFavoritos::operator=(const listaFavoritos &otro)
{
    if(this != &otro){
        while (!canciones.estaVacia()){
            canciones.eliminar(*canciones.obtener(0));
        }

        capacidadMaxima = otro.capacidadMaxima;
        for(int i = 0; i <otro.canciones.obtenerTamano(); i++){
            canciones.agregar(*otro.canciones.obtener(i));
        }
    }
    return *this;
}


