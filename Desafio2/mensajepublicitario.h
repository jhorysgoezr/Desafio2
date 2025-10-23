#ifndef MENSAJEPUBLICITARIO_H
#define MENSAJEPUBLICITARIO_H

#include <estructuras.h>

class MensajePublicitario
{
private:
    string contenido;
    CategoriaPubicidad categoria;
public:
    MensajePublicitario();
    MensajePublicitario(const string& c, CategoriaPubicidad cat);
    MensajePublicitario(const MensajePublicitario& otro);
};

#endif // MENSAJEPUBLICITARIO_H
