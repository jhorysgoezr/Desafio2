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
