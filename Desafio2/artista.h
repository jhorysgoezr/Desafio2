#ifndef ARTISTA_H
#define ARTISTA_H

#include "estructuras.h"

class artista
{
private:
    int codigo;
    int edad;
    string pais;

public:
    artista();
    artista (int c, int e, const string& p);
    artista(const artista& otro);

    int getCodigo() const {return codigo;}
    int getEdad() const{return edad;}
    string getPais() const{return pais;}

    void setCodigo(int c) {codigo = c;}
    void setEdad(int e) {edad = e;}
    void setPais(const string& p) {pais = p;}
    bool operator ==(const artista& otro)const;
    bool operator !=(const artista& otro)const;
    friend ostream& operator <<(ostream& os, const artista& _artista){
        os <<"Artista - Codigo: " <<_artista.codigo
           <<", Edad: "<<_artista.edad
           <<", pais "<<_artista.pais;
        return os;
    }
};

#endif
