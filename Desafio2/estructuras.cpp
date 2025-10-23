#include "estructuras.h"

estructuras::estructuras() {}

template<typename T>
ListaEnlazada<T>::~ListaEnlazada(){
    while (cabeza){
        Nodo* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

template<typename T>
void ListaEnlazada<T>::agregar(const T &dato)
{
    Nodo* nuevo = new Nodo(dato);
    if (!cabeza){
        cabeza = nuevo;
    }
    else {
        Nodo* actual = cabeza;
        while (actual->siguiente){
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
    tamano++;
}

template<typename T>
bool ListaEnlazada<T>::eliminar(const T &dato)
{
    if (!cabeza) return false;

    if (cabeza->dato == dato){
        Nodo* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
        tamano--;
        return true;
    }

    Nodo* actual = cabeza;
    while(actual->siguiente && actual->siguiente->dato != dato){
        actual = actual->siguiente;
    }

    if(actual->siguiente){
        Nodo* temp = actual->siguiente;
        actual->siguiente = actual->siguiente->siguiente;
        delete temp;
        tamano--;
        return true;
    }
    return false;
}
