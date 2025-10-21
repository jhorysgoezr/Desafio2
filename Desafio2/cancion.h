#ifndef CANCION_H
#define CANCION_H

class cancion
{
private:
    int id;
    char* nombre;
    int duracion;
    char* ruta128;
    char* ruta320;
    int reproducciones;
public:
    cancion();
    ~Cancion();
    void mostrarInfo(bool premium);

};

#endif // CANCION_H
