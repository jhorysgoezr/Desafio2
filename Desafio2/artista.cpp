#include "artista.h"

artista::artista() {}

artista::artista(int c, int e, const string &p):codigo(c), edad(e), pais(p){}

artista::artista (const artista &otro): codigo(otro.codigo), edad(otro.edad), pais(otro.pais) {}

bool artista::operator ==(const artista &otro) const
{
    return codigo == otro.codigo;
}

bool artista::operator !=(const artista &otro) const
{
    return !(*this == otro);
}
