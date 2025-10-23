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

template<typename T>
bool ListaEnlazada<T>::buscar(const T &dato) const
{
    Nodo* actual = cabeza;
    while (actual){
        if (actual->dato == dato) return true;
        actual = actual->siguiente;
    }
    return false;
}

template<typename T>
T *ListaEnlazada<T>::obtener(int indice) const
{
    if (indice < 0|| indice >=tamano ) return nullptr;

    Nodo* actual = cabeza;
    for (int i = 0; i<indice; i++){
        actual = actual->siguiente;
    }
    return &(actual->dato);
}

template<typename T>
Cola<T>::~Cola()
{
    while (frente){
        NodoCola* temp = frente;
        frente = frente->siguiente;
        delete temp;
    }
}

template<typename T>
void Cola<T>::encolar(const T &dato)
{
    NodoCola* nuevo = new NodoCola(dato);
    if(!frente){
        frente = final = nuevo;
    }
    else{
        final->siguiente = nuevo;
        final = nuevo;
    }
    tamano++;
}

template<typename T>
bool Cola<T>::desencolar()
{
    if (!frente) return false;

    NodoCola* temp = frente;
    frente = frente->siguiente;
    if(!frente) final = nullptr;
    delete temp;
    tamano--;
    return true;
}

template<typename T>
T *Cola<T>::obtenerFrente() const
{
    return frente ? &(frente->dato): nullptr;
}

template<typename T>
Pila<T>::~Pila()
{
    while(tope){
        NodoPila* temp = tope;
        tope = tope.siguiente;
        delete temp;
    }
}

template<typename T>
void Pila<T>::apilar(const T &dato)
{
    NodoPila* nuevo = new NodoPila(dato);
    nuevo->siguiente = tope;
    tope = nuevo;
    tamano++;
}

template<typename T>
bool Pila<T>::desapilar()
{
    if(!tope)return false;

    NodoPila* temp = tope;
    tope = tope.siguiente;
    delete temp;
    tamano--;
    return true;
}

template<typename T>
T *Pila<T>::obtenerTope() const
{
    return tope ? &(tope.dato):nullptr;
}
