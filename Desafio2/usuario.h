#ifndef USUARIO_H
#define USUARIO_H

#include <estructuras.h>
#include <listafavoritos.h>

class Usuario
{
private:
    string nickname;
    TipoMembresia tipoMembresia;
    string ciudad;
    string pais;
    string fechaInscripcion;
    listaFavoritos Listafavoritos;

public:
    Usuario();
    Usuario(const string& nick, TipoMembresia tipo, const string& ciu, string &pa, const string& fecha );
    Usuario(const Usuario& otro);

    string getNickname() const {return nickname;}
    TipoMembresia getTipoMembresia() const {return tipoMembresia;}
    string getCiudad() const {return ciudad;}
    string getPais() const {return pais;}
    string getFechaInscripcion(){return fechaInscripcion;}
    listaFavoritos& getListaFavoritos(){return Listafavoritos;}
    const listaFavoritos& getListaFavoritos() const {return Listafavoritos;}


    void setNickname(const string& nick) {nickname = nick;}
    void setTipoMembresia(TipoMembresia tipo) {tipoMembresia = tipo;}
    void setCiudad(const string& ciu) {ciudad = ciu;}
    void setPais(const string& pa) {pais = pa;}
    void setFechaInscripcion(const string& fecha){fechaInscripcion = fecha;}
};

#endif // USUARIO_H
