#include "usuario.h"

Usuario::Usuario():tipoMembresia(ESTANDAR) {}

Usuario::Usuario(const string &nick, TipoMembresia tipo, const string &ciu,
                 string &pa, const string &fecha):nickname(nick), tipoMembresia(tipo),
    ciudad(ciu), pais(pa), fechaInscripcion(fecha)
{

}

Usuario::Usuario(const Usuario &otro): nickname(otro.nickname), tipoMembresia(otro.tipoMembresia),
    ciudad(otro.ciudad), pais(otro.pais),fechaInscripcion(otro.fechaInscripcion),
    Listafavoritos(otro.Listafavoritos)
{

}

bool Usuario::esPremium() const
{
    return tipoMembresia == PREMIUM;
}

bool Usuario::esEstandar() const
{
    return tipoMembresia == ESTANDAR;
}

bool Usuario::agregarAFavoritos(int idCancion)
{
    if(esPremium()){
        return Listafavoritos.eliminarCancion(idCancion);
    }
    return false;
}

bool Usuario::eliminarDeFavoritos(int idCancion)
{
    if(esPremium()){
        return Listafavoritos.eliminarCancion(idCancion);
    }
    return false;
}

bool Usuario::tieneEnFavoritos(int idCancion)
{
    if(esPremium()){
        return Listafavoritos.tieneCancion(idCancion);
    }
    return false;
}

bool Usuario::seguirListaFavoritos(const Usuario &otroUsuario)
{
    if(esPremium() && otroUsuario.esPremium()){
        Listafavoritos.agregarLista(otroUsuario.getListaFavoritos());
        return true;
    }
    return false;
}

bool Usuario::operator ==(const Usuario &otro) const
{
    return nickname == otro.nickname;
}

bool Usuario::operator !=(const Usuario &otro) const
{
    return !(*this == otro);
}

Usuario &Usuario::operator =(const Usuario &otro)
{
    if(this != &otro){
        nickname = otro.nickname;
        tipoMembresia = otro.tipoMembresia;
        ciudad = otro.ciudad;
        pais = otro.pais;
        fechaInscripcion = otro.fechaInscripcion;
        Listafavoritos = otro.Listafavoritos;
    }
    return *this;
}
