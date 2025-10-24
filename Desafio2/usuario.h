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

    bool esPremium()const;
    bool esEstandar()const;
    bool agregarAFavoritos(int idCancion);
    bool eliminarDeFavoritos(int idCancion);
    bool tieneEnFavoritos(int idCancion);
    bool seguirListaFavoritos(const Usuario& otroUsuario);

    bool operator == (const Usuario& otro) const;
    bool operator !=(const Usuario& otro) const;

    Usuario& operator =(const Usuario& otro);

    friend ostream& operator <<(ostream& os, const Usuario& usuario){
        os <<"Usuario - Nickname: " <<usuario.nickname
           <<", tipo: "<<(usuario.tipoMembresia == PREMIUM ? "Premium" : "Estandar")
           <<", Ciudad: "<<usuario.ciudad
           <<", Pais: "<<usuario.pais
           <<", Fecha: "<<usuario.fechaInscripcion;
        if(usuario.esPremium()){
            os<<", Favoritos: "<<usuario.Listafavoritos.obtenerTamano();
        }
        return os;
    }
};

#endif
