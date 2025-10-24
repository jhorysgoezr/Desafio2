#ifndef LISTAFAVORITOS_H
#define LISTAFAVORITOS_H

#include <cancion.h>
#include <estructuras.h>


class listaFavoritos
{
private:
    ListaEnlazada<int> canciones;
    int capacidadMaxima;
public:
    listaFavoritos();
    listaFavoritos(const listaFavoritos& otro);

    bool agregarCancion(int idCancion);
    bool eliminarCancion(int idCancion);
    bool tieneCancion(int idCancion) const;
    int obtenerTamano() const;
    int obtenerCancion(int indice) const;
    bool estaVacia() const;
    void agregarLista(const listaFavoritos& otraLista);

    listaFavoritos& operator=(const listaFavoritos& otro);

    friend ostream& operator <<(ostream& os, const listaFavoritos& _lista){
        os <<"Lista de Favoritos - Canciones: : " << _lista.obtenerTamano()
           <<"/"<< _lista.capacidadMaxima;
        return os;
    }

};

#endif // LISTAFAVORITOS_H
