#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <iostream>
#include <string>

using namespace std;

enum TipoMembresia {ESTANDAR, PREMIUM};
enum CategoriaPubicidad {CATEGORIA_C, CATEGORIA_B, CATEGORIA_AAA};

template<typename T>
class ListaEnlazada {
private:
    struct Nodo
    {
        T dato;
        Nodo* siguiente;
        Nodo(const T& d) : dato(d), siguiente(nullptr){}
    };
    Nodo* cabeza;
    int tamano;

public:
    ListaEnlazada(): cabeza(nullptr), tamano(0){}

    ~ListaEnlazada ();
    void agregar(const T& dato);
    bool eliminar(const T& dato);
    bool buscar(const T& dato)const;
    T* obtener(int indice) const;
    int obtenerTamano() const {return tamano;}
    bool estaVacia() const {return tamano == 0;}

    class Iterador{
    private:
        Nodo* actual;
    public:
    Iterador(Nodo* n): actual(n){}
    bool tieneSiguiente() const {return actual != nullptr;}

    T& siguiente(){
        T& dato = actual->dato;
        actual = actual->siguiente;
        return dato;
    }
    };

    Iterador obtenerIterador() const {return Iterador(cabeza);}
};

template<typename T>
class Cola{
private:
    struct  NodoCola {
        T dato;
        NodoCola* siguiente;
        NodoCola(const T& d): dato(d), siguiente(nullptr){}
    };
    NodoCola* frente;
    NodoCola* final;
    int tamano;
public:
    Cola(): frente(nullptr), final(nullptr), tamano(0){}
    ~Cola();
    void encolar(const T& dato);
    bool desencolar();
    T* obtenerFrente()const;
    bool estaVacia() const {return tamano == 0;}
    int obtenerTamano() const {return tamano;}
};

template<typename T>
class Pila{
private:
    struct NodoPila{
        T dato;
        NodoPila* siguiente;
        NodoPila(const T& d): dato(d), siguiente(nullptr) {}
    };
    NodoPila tope;
    int tamano;
public:
    Pila(): tope(nullptr), tamano(0) {}
    ~Pila();
    void apilar(const T& dato);
    bool desapilar();
    T* obtenerTope()const;
    bool estaVacia() const {return tamano == 0;}
    int obtenerTamano() const {return tamano;}
};

class estructuras
{
public:
    estructuras();
};

#endif // ESTRUCTURAS_H
