#ifndef UDEATUNES_H
#define UDEATUNES_H

#include "usuario.h"
#include <chrono>
#include <random>
#include <mensajepublicitario.h>
#include <cancion.h>
#include <album.h>
#include <artista.h>
#include <estructuras.h>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class udeatunes
{
private:
    ListaEnlazada<Usuario> usuarios;
    ListaEnlazada<artista> artistas;
    ListaEnlazada<album> albumes;
    ListaEnlazada<cancion> canciones;
    ListaEnlazada<MensajePublicitario> mensajesPublicitarios;

    Usuario* usuarioActual;
    bool reproduciendo;
    cancion* cancionActual;
    Cola<int> historialReproduccion;
    Pila<int> pilaAnterior;
    bool modoRepetir;
    int cancionesReproducidas;
    int limiteReproduccion;

    int iteracionesTotales;

    random_device rd;
    mt19937 gen;
public:
    udeatunes();

    bool cargarUsuarios(const string& archivo);
    bool cargarArtistas(const string& archivo);
    bool cargarAlbumes(const string& archivo);
    bool cargarCanciones(const string& archivo);
    bool cargarMensajesPublicitarios(const string& archivo);

    bool iniciarSesion(const string& nickname);
    void cerrarSesion();

    Usuario* getUsuarioActual() const;

    bool iniciarReproduccionAleatoria();
    bool siguienteCancion();
    bool cancionAnterior();

    void detenerReproduccion();
    void alternarRepetir();

    bool estaReproduciendo() const;
    cancion* getCancionActual() const;
    bool getModoRepetir();
    int getCancionesReproducidas();

    bool agregarAFavoritos(int idCancion);

    bool eliminarDeFavoritos(int idCancion);

    bool seguirListaFavoritos(const string& nicknameUsuario);

    MensajePublicitario* obtenerMensajePublicitario();


    cancion* buscarCancion(int idCancion);

    album* buscarAlbum(int codigoAlbum);

    artista* buscarArtista(int codigoArtista);

    int getIteracionesTotales() const;

    void resetearIteraciones();

    int calcularMemoria() const;

    int getCantidadUsuarios() const { return usuarios.obtenerTamano(); }
    int getCantidadArtistas() const { return artistas.obtenerTamano(); }
    int getCantidadAlbumes() const { return albumes.obtenerTamano(); }
    int getCantidadCanciones() const { return canciones.obtenerTamano(); }
    int getCantidadMensajesPublicitarios() const { return mensajesPublicitarios.obtenerTamano(); }


};

#endif
