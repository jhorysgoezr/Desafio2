#include "mensajepublicitario.h"

MensajePublicitario::MensajePublicitario():categoria(CATEGORIA_C) {}

MensajePublicitario::MensajePublicitario(const string &c, CategoriaPubicidad cat):
    contenido(c), categoria(cat)
{

}

MensajePublicitario::MensajePublicitario(const MensajePublicitario &otro):
    contenido(otro.contenido), categoria(otro.categoria)
{

}

int MensajePublicitario::getPrioridad() const
{
    switch (categoria) {
    case CATEGORIA_C:return 1;
    case CATEGORIA_B:return 2;
    case CATEGORIA_AAA:return 3;
    default:return 1;
    }
}

bool MensajePublicitario::operator ==(const MensajePublicitario &otro) const
{
    return contenido == otro.contenido && categoria == otro.categoria;
}

bool MensajePublicitario::operator !=(const MensajePublicitario &otro) const
{
    return !(*this == otro);
}
