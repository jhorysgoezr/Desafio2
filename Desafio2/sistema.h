#ifndef SISTEMA_H
#define SISTEMA_H

class Sistema
{
private:
    Usuario** usuarios;
    Artista** artistas;
    Publicidad** anuncios;
    int numUsuarios, numArtistas, numAnuncios;

public:
    Sistema();
    ~Sistema();
    void cargarDatos();
    Usuario* login(const char* Validacion);
    void mostrarMenu(Usuario* u);
};

#endif // SISTEMA_H
