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
