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

    string getContenido() const {return contenido;}
    CategoriaPubicidad getCategoria() const {return categoria;}

    void setContenido(const string& c) {contenido = c;}
    void setCategoria(CategoriaPubicidad cat) {categoria = cat;}

    int getPrioridad() const;

    bool operator == (const MensajePublicitario& otro)const;
    bool operator != (const MensajePublicitario& otro)const;

    friend ostream& operator <<(ostream& os, const MensajePublicitario& mensaje){
        os<<"Publicidad ["<<mensaje.getPrioridad() <<"] -"<<mensaje.contenido;
        return os;
    }

};

#endif // MENSAJEPUBLICITARIO_H
