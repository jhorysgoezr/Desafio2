#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <iostream>
#include <string>

using namespace std;

enum TipoMembresia {ESTANDAR, PREMIUM};
enum CategoriaPubicidad {CATEGORIA_C, CATEGORIA_B, CATEGORIA_AAA};
enum Genero{POP, JAZZ,MUSICA_CLASICA, ELECTRONICA, GUARACHA, BLUES, VALLENATO,REGGAE};


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
    int obtenerTamano() const {return tamano;}
    bool estaVacia() const {return tamano == 0;}

    ~ListaEnlazada (){
        while (cabeza){
            Nodo* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
    }

    void agregar(const T &dato)
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

    bool eliminar(const T &dato)
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

    bool buscar(const T &dato) const
    {
        Nodo* actual = cabeza;
        while (actual){
            if (actual->dato == dato) return true;
            actual = actual->siguiente;
        }
        return false;
    }

    T *obtener(int indice) const
    {
        if (indice < 0|| indice >=tamano ) return nullptr;

        Nodo* actual = cabeza;
        for (int i = 0; i<indice; i++){
            actual = actual->siguiente;
        }
        return &(actual->dato);
    }

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
    struct NodoCola {
        T dato;
        NodoCola* siguiente;
        NodoCola(const T& d): dato(d), siguiente(nullptr){}
    };
    NodoCola* frente;
    NodoCola* final;
    int tamano;
public:
    Cola(): frente(nullptr), final(nullptr), tamano(0){}
    bool estaVacia() const {return tamano == 0;}
    int obtenerTamano() const {return tamano;}

    ~Cola(){
        while (frente){
            NodoCola* temp = frente;
            frente = frente->siguiente;
            delete temp;
        }
    }

    void encolar(const T &dato)
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

    bool desencolar()
    {
        if (!frente) return false;

        NodoCola* temp = frente;
        frente = frente->siguiente;
        if(!frente) final = nullptr;
        delete temp;
        tamano--;
        return true;
    }

    T *obtenerFrente() const
    {
        return frente ? &(frente->dato): nullptr;
    }
};


template<typename T>
class Pila{
private:
    struct NodoPila{
        T dato;
        NodoPila* siguiente;
        NodoPila(const T& d): dato(d), siguiente(nullptr) {}
    };
    NodoPila* tope;
    int tamano;
public:
    Pila(): tope(nullptr), tamano(0) {}
    bool estaVacia() const {return tamano == 0;}
    int obtenerTamano() const {return tamano;}

    ~Pila()
    {
        while(tope){
            NodoPila* temp = tope;
            tope = tope->siguiente;
            delete temp;
        }
    }

    void apilar(const T &dato)
    {
        NodoPila* nuevo = new NodoPila(dato);
        nuevo->siguiente = tope;
        tope = nuevo;
        tamano++;
    }

    bool desapilar()
    {
        if(!tope)return false;

        NodoPila* temp = tope;
        tope = tope->siguiente;
        delete temp;
        tamano--;
        return true;
    }


    T *obtenerTope() const
    {
        return tope ? &(tope->dato):nullptr;
    }
};

class estructuras
{
public:
    estructuras();
};

#endif
