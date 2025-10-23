#ifndef CANCION_H
#define CANCION_H

#include <estructuras.h>

class cancion
{
private:
    int identificador;
    string nombre;
    int duracion;
    string rutaAudio128;
    string rutaAudio320;
    int reproducciones;

public:
    cancion();
    cancion(int id, const string& n, int d, const string& r128, const string& r320);
    cancion(const cancion& otro);

    int getIdentificador() const {return identificador;}
    string getNombre() const {return nombre;}
    int getDuracion()const {return duracion;}
    string getRutaAudio128() const {return rutaAudio128;}
    string getRutaAudio320() const {return rutaAudio320;}
    int getReproducciones() const{return reproducciones;}

    void setIdentificador(int id) {identificador = id;}
    void setNombre(const string& n) {nombre = n;}
    void setDuracion(int d){duracion = d;}
    void setRutaAudio128(const string& r) {rutaAudio128 = r;}
    void setRutaAudio320(const string& r) {rutaAudio320 = r;}

    void incrementarReproducciones();
    int getCodigoArtista()const;
    int getCodigoAlbum()const;
    int getCodigoCancion()const;

    bool operator ==(const cancion& otro)const;
    bool operator !=(const cancion& otro)const;
    friend ostream& operator <<(ostream& os, const cancion& _cancion){
        os <<"Cancion - ID: " <<_cancion.identificador
           <<", Nombre: "<<_cancion.nombre
           <<", Duraccion: "<<_cancion.duracion<< " seg"
           <<", Reproducciones: "<<_cancion.reproducciones;
        return os;
    }

};

#endif // CANCION_H
