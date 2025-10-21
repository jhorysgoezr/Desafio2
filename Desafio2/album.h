#ifndef ALBUM_H
#define ALBUM_H

class album
{
private:
    int id;
    char* nombre;
    cancion** canciones;
    int numCanciones;
public:
    album();
    ~Album();
    void agregarCancion(Cancion* c);
    Cancion* obtenerCancionRandom();
};

#endif // ALBUM_H
