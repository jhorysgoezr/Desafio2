#ifndef ARTISTA_H
#define ARTISTA_H

class Artista
{
private:
    char* nombre;
    char* pais;
    album** albumnes;
    int numAlbumnes;
public:
    Artista();
    ~Artista();
    Cancion* obtenerCancionRandom();
};

#endif // ARTISTA_H
