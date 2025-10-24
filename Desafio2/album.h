#ifndef ALBUM_H
#define ALBUM_H

#include <estructuras.h>

class album
{
private:
    int codigo;
    string nombre;
    string fechaLanzamiento;
    int duracion;
    Genero generos[4];
    int cantidadGeneros;
    string portada;
    ListaEnlazada<int>canciones;
public:
    album();
    album(int c, const string& n, const string& f, int d, const string& p);
    album(const album& otro);

    int getCodigo() const {return codigo;}
    string getNombre() const {return nombre;}
    string getFechaLanzamiento() const {return fechaLanzamiento;}
    int getDuracion() const {return duracion;}
    string getPortada() const {return portada;}
    int getCantidadGeneros() const {return cantidadGeneros;}
    Genero getGenero(int indice)const {
        return (indice >= 0 && indice< cantidadGeneros) ? generos[indice]:POP;
    }

    void setCodigo(int c) {codigo = c;}
    void setNombre(const string& n) {nombre = n;}
    void setFechaLanzamiento(const string& f){fechaLanzamiento = f;}
    void setDuracion(int d) {duracion = d;}
    void setPortada(const string& p){portada = p;}

    bool agregarGeneros(Genero g);
    void agregarCancion(int idCancion);
    bool eliminarCacnion(int idCancion);
    bool tieneCancion(int idCancion) const;

    int getCantidadCanciones() const;
    int getCancion(int indice) const;

    bool operator ==(const album& otro) const;
    bool operator !=(const album& otro) const;

    friend ostream& operator <<(ostream& os, const album& _album){
        os <<"Album - CCodigo: "<< _album.codigo
           <<", nombre: " <<_album.nombre
           <<", fecha: "<< _album.fechaLanzamiento
           <<", Duracion: " << _album.duracion << " min"
           <<", Canciones: " << _album.canciones.obtenerTamano();
        return os;
    }
};

#endif
