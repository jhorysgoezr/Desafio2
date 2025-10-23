#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H



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
};









class estructuras
{
public:
    estructuras();
};

#endif // ESTRUCTURAS_H
