#include "cancion.h"

cancion::cancion():identificador(0), duracion(0), reproducciones(0) {}

cancion::cancion(int id, const string &n, int d, const string &r128, const string &r320):
    identificador(id),nombre(n),duracion(d), rutaAudio128(r128), rutaAudio320(r320), reproducciones(0)
{

}

cancion::cancion(const cancion &otro):
    identificador(otro.identificador), nombre(otro.nombre),duracion(otro.duracion),
    rutaAudio128(otro.rutaAudio128),rutaAudio320(otro.rutaAudio320), reproducciones(otro.reproducciones)
{

}

void cancion::incrementarReproducciones()
{
    reproducciones++;
}

int cancion::getCodigoArtista() const
{
    return identificador/10000;
}

int cancion::getCodigoAlbum() const
{
    return (identificador % 10000) / 100;
}

int cancion::getCodigoCancion() const
{
    return identificador % 100;
}

bool cancion::operator ==(const cancion &otro) const
{
    return identificador == otro.identificador;
}

bool cancion::operator !=(const cancion &otro) const
{
    return !(*this == otro);
}
