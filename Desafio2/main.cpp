#include <iostream>
#include <chrono>
#include <thread>
#include <sstream>
#include "udeatunes.h"

using namespace std;

bool cargarArchivo(udeatunes& sistema, const string& nombreArchivo,
                   bool (udeatunes::*metodoCarga)(const string&)) {
    string rutas[] = {
        nombreArchivo,
        "./" + nombreArchivo,
        "../" + nombreArchivo,
        "../../" + nombreArchivo
    };

    for (const string& ruta : rutas) {
        if ((sistema.*metodoCarga)(ruta)) {
            cout << nombreArchivo << " cargado desde: " << ruta << endl;
            return true;
        }
    }

    cout << "Advertencia: No se pudo cargar " << nombreArchivo << " desde ninguna ubicacion" << endl;
    return false;
}

void mostrarMenuPrincipal() {
    cout << "\n=== UdeATunes - Sistema de Streaming Musical ===" << endl;
    cout << "1. Ingresar a la plataforma" << endl;
    cout << "2. Salir" << endl;
    cout << "Seleccione una opcion: ";
}


void mostrarMenuEstandar() {
    cout << "\n=== Menu Usuario Estandar ===" << endl;
    cout << "1. Reproduccion aleatoria" << endl;
    cout << "2. Cerrar sesion" << endl;
    cout << "Seleccione una opcion: ";
}


void mostrarMenuPremium() {
    cout << "\n=== Menu Usuario Premium ===" << endl;
    cout << "1. Reproduccion aleatoria" << endl;
    cout << "2. Mi lista de favoritos" << endl;
    cout << "3. Cerrar sesion" << endl;
    cout << "Seleccione una opcion: ";
}


void mostrarMenuReproduccion(udeatunes& sistema) {
    cout << "\nSeleccione una opcion: ";
}


void mostrarMenuFavoritos() {
    cout << "\n=== Mi Lista de Favoritos ===" << endl;
    cout << "1. Editar mi lista de favoritos" << endl;
    cout << "2. Seguir otra lista de favoritos" << endl;
    cout << "3. Ejecutar mi lista de favoritos" << endl;
    cout << "4. Volver al menu principal" << endl;
    cout << "Seleccione una opcion: ";
}

void mostrarMetricas(udeatunes& sistema) {
    cout << "\n=== Metricas de Rendimiento ===" << endl;
    cout << "Iteraciones realizadas: " << sistema.getIteracionesTotales() << endl;
    cout << "Memoria consumida: " << sistema.calcularMemoria() << " bytes" << endl;
}

void simularReproduccion(udeatunes&  sistema) {
    if (!sistema.estaReproduciendo()) return;

    cancion* cancion = sistema.getCancionActual();
    if (!cancion) return;


    album* album = sistema.buscarAlbum(cancion->getCodigoAlbum());
    artista* artista = sistema.buscarArtista(cancion->getCodigoArtista());

    cout << "\n" << string(60, '=') << endl;
    cout << "                    UdeATunes Player" << endl;
    cout << string(60, '=') << endl;

    if (sistema.getUsuarioActual()->esEstandar()) {
        MensajePublicitario* mensaje = sistema.obtenerMensajePublicitario();
        if (mensaje) {
            cout << "Mensaje publicitario: " << mensaje->getContenido() << endl;
            cout << "Categoria del mensaje: ";
            switch (mensaje->getCategoria()) {
            case CATEGORIA_C: cout << "C"; break;
            case CATEGORIA_B: cout << "B"; break;
            case CATEGORIA_AAA: cout << "AAA"; break;
            }
            cout << endl;
            cout << string(60, '-') << endl;
        }
    }

    cout << "Cantante: ";
    if (artista) {
        cout << "Artista #" << artista->getCodigo() << " (" << artista->getPais() << ")";
    } else {
        cout << "Desconocido";
    }
    cout << endl;

    cout << "Album: ";
    if (album) {
        cout << album->getNombre();
    } else {
        cout << "Desconocido";
    }
    cout << endl;

    cout << "Ruta a la portada del album: ";
    if (album) {
        cout << album->getPortada();
    } else {
        cout << "No disponible";
    }
    cout << endl;

    cout << "Titulo de la cancion reproducida: " << cancion->getNombre() << endl;

    cout << "Ruta al archivo de audio: ";
    if (sistema.getUsuarioActual()->esPremium()) {
        cout << cancion->getRutaAudio320() << " (320 kbps)";
    } else {
        cout << cancion->getRutaAudio128() << " (128 kbps)";
    }
    cout << endl;

    cout << "Duracion: " << cancion->getDuracion() << " segundos" << endl;

    cout << string(60, '-') << endl;
    cout << "Opciones de reproduccion:" << endl;

    if (sistema.getUsuarioActual()->esPremium()) {
        cout << "1.- Reproducir    2.- Detener    3.- Siguiente    4.- Anterior" << endl;
        cout << "5.- " << (sistema.getModoRepetir() ? "Desactivar" : "Activar") << " repetir    6.- Volver al menu" << endl;
    } else {
        cout << "1.- Reproducir    2.- Detener    3.- Siguiente    4.- Volver al menu" << endl;
    }

    cout << "*Todas las opciones que apliquen" << endl;
    cout << string(60, '=') << endl;

    cout << "\nReproduciendo por 3 segundos..." << endl;
    this_thread::sleep_for(chrono::seconds(3));

    if (sistema.getCancionesReproducidas() < 5) {
        if (!sistema.siguienteCancion()) {
            sistema.detenerReproduccion();
            cout << "Reproduccion finalizada (limite alcanzado)." << endl;
        }
    } else {
        sistema.detenerReproduccion();
        cout << "Reproduccion finalizada (limite alcanzado)." << endl;
    }
}


void manejarReproduccionAleatoria(udeatunes& sistema) {
    if (!sistema.iniciarReproduccionAleatoria()) {
        cout << "Error: No se pudo iniciar la reproduccion." << endl;
        return;
    }

    int opcion;
    while (sistema.estaReproduciendo()) {
        simularReproduccion(sistema);

        if (!sistema.estaReproduciendo()) break;

        mostrarMenuReproduccion(sistema);
        cin >> opcion;

        if (sistema.getUsuarioActual()->esPremium()) {
            switch (opcion) {
            case 1:
                cout << "Continuando reproduccion..." << endl;
                break;

            case 2:
                sistema.detenerReproduccion();
                cout << "Reproduccion detenida." << endl;
                break;

            case 3:
                if (!sistema.siguienteCancion()) {
                    sistema.detenerReproduccion();
                    cout << "No hay mas canciones disponibles." << endl;
                }
                break;

            case 4:
                if (!sistema.cancionAnterior()) {
                    cout << "No hay cancion anterior disponible." << endl;
                }
                break;

            case 5:
                sistema.alternarRepetir();
                cout << "Modo repetir " << (sistema.getModoRepetir() ? "activado" : "desactivado") << "." << endl;
                break;

            case 6:
                sistema.detenerReproduccion();
                break;

            default:
                cout << "Opcion invalida." << endl;
                break;
            }
        } else {
            switch (opcion) {
            case 1:
                cout << "Continuando reproduccion..." << endl;
                break;

            case 2:
                sistema.detenerReproduccion();
                cout << "Reproduccion detenida." << endl;
                break;

            case 3:
                if (!sistema.siguienteCancion()) {
                    sistema.detenerReproduccion();
                    cout << "No hay mas canciones disponibles." << endl;
                }
                break;

            case 4:
                sistema.detenerReproduccion();
                break;

            default:
                cout << "Opcion invalida." << endl;
                break;
            }
        }
    }

    mostrarMetricas(sistema);
}

void manejarEdicionFavoritos(udeatunes& sistema) {
    cout << "\n=== Editar Lista de Favoritos ===" << endl;
    cout << "1. Agregar cancion" << endl;
    cout << "2. Eliminar cancion" << endl;
    cout << "3. Ver lista actual" << endl;
    cout << "4. Volver" << endl;
    cout << "Seleccione una opcion: ";

    int opcion;
    cin >> opcion;

    switch (opcion) {
    case 1: {
        cout << "Ingrese el ID de la cancion a agregar: ";
        int idCancion;
        cin >> idCancion;

        cancion* cancion = sistema.buscarCancion(idCancion);
        if (cancion) {
            cout << "Cancion encontrada: " << cancion->getNombre() << endl;
            cout << "¿Desea agregarla a favoritos? (1=Si, 0=No): ";
            int confirmar;
            cin >> confirmar;

            if (confirmar == 1) {
                if (sistema.agregarAFavoritos(idCancion)) {
                    cout << "Cancion agregada a favoritos." << endl;
                } else {
                    cout << "Error: No se pudo agregar la cancion." << endl;
                }
            }
        } else {
            cout << "Cancion no encontrada." << endl;
        }
        break;
    }

    case 2: {
        cout << "Ingrese el ID de la cancion a eliminar: ";
        int idCancion;
        cin >> idCancion;

        if (sistema.eliminarDeFavoritos(idCancion)) {
            cout << "Cancion eliminada de favoritos." << endl;
        } else {
            cout << "Error: No se pudo eliminar la cancion." << endl;
        }
        break;
    }

    case 3: {
        listaFavoritos& favoritos = sistema.getUsuarioActual()->getListaFavoritos();
        cout << "\nLista de Favoritos (" << favoritos.obtenerTamano() << " canciones):" << endl;

        for (int i = 0; i < favoritos.obtenerTamano(); i++) {
            int idCancion = favoritos.obtenerCancion(i);
            cancion* cancion = sistema.buscarCancion(idCancion);
            if (cancion) {
                cout << (i + 1) << ". " << cancion->getNombre() << " (ID: " << idCancion << ")" << endl;
            }
        }
        break;
    }

    case 4:
        return;

    default:
        cout << "Opcion invalida." << endl;
        break;
    }
}

void manejarSeguirLista(udeatunes& sistema) {
    cout << "Ingrese el nickname del usuario a seguir: ";
    string nickname;
    cin >> nickname;

    if (sistema.seguirListaFavoritos(nickname)) {
        cout << "Lista de favoritos de " << nickname << " agregada exitosamente." << endl;
    } else {
        cout << "Error: No se pudo seguir la lista de favoritos." << endl;
    }
}

void manejarEjecutarFavoritos(udeatunes& sistema) {
    listaFavoritos& favoritos = sistema.getUsuarioActual()->getListaFavoritos();

    if (favoritos.estaVacia()) {
        cout << "Su lista de favoritos esta vacia." << endl;
        return;
    }

    cout << "¿Como desea reproducir su lista?" << endl;
    cout << "1. En orden original" << endl;
    cout << "2. De forma aleatoria" << endl;
    cout << "Seleccione una opcion: ";

    int opcion;
    cin >> opcion;

    if (opcion == 1) {
        cout << "Reproduciendo lista en orden original..." << endl;
        for (int i = 0; i < favoritos.obtenerTamano() && i < 6; i++) {
            int idCancion = favoritos.obtenerCancion(i);
            cancion* cancion = sistema.buscarCancion(idCancion);
            if (cancion) {
                cout << "Reproduciendo: " << cancion->getNombre() << endl;
                this_thread::sleep_for(chrono::seconds(2));
            }
        }
    } else if (opcion == 2) {
        cout << "Reproduciendo lista de forma aleatoria..." << endl;
        for (int i = 0; i < min(favoritos.obtenerTamano(), 6); i++) {
            int indiceAleatorio = rand() % favoritos.obtenerTamano();
            int idCancion = favoritos.obtenerCancion(indiceAleatorio);
            cancion* cancion = sistema.buscarCancion(idCancion);
            if (cancion) {
                cout << "Reproduciendo: " << cancion->getNombre() << endl;
                this_thread::sleep_for(chrono::seconds(2));
            }
        }
    } else {
        cout << "Opcion invalida." << endl;
    }
}

void manejarMenuFavoritos(udeatunes& sistema) {
    int opcion;

    do {
        mostrarMenuFavoritos();
        cin >> opcion;

        switch (opcion) {
        case 1:
            manejarEdicionFavoritos(sistema);
            break;

        case 2:
            manejarSeguirLista(sistema);
            break;

        case 3:
            manejarEjecutarFavoritos(sistema);
            break;

        case 4:
            return;

        default:
            cout << "Opcion invalida." << endl;
            break;
        }

        mostrarMetricas(sistema);

    } while (opcion != 4);
}

void manejarMenuUsuario(udeatunes& sistema) {
    int opcion;

    do {
        if (sistema.getUsuarioActual()->esPremium()) {
            mostrarMenuPremium();
        } else {
            mostrarMenuEstandar();
        }

        cin >> opcion;

        switch (opcion) {
        case 1:
            manejarReproduccionAleatoria(sistema);
            break;

        case 2:
            if (sistema.getUsuarioActual()->esPremium()) {
                manejarMenuFavoritos(sistema);
            } else {
                sistema.cerrarSesion();
                cout << "Sesion cerrada." << endl;
                return;
            }
            break;

        case 3:
            if (sistema.getUsuarioActual()->esPremium()) {
                sistema.cerrarSesion();
                cout << "Sesion cerrada." << endl;
                return;
            } else {
                cout << "Opcion invalida." << endl;
            }
            break;

        default:
            cout << "Opcion invalida." << endl;
            break;
        }

    } while (sistema.getUsuarioActual() != nullptr);
}

int main() {
    udeatunes sistema;

    cout << "Cargando datos del sistema..." << endl;

    cargarArchivo(sistema, "usuarios.txt", &udeatunes::cargarUsuarios);
    cargarArchivo(sistema, "artistas.txt", &udeatunes::cargarArtistas);
    cargarArchivo(sistema, "albumes.txt", &udeatunes::cargarAlbumes);
    cargarArchivo(sistema, "canciones.txt", &udeatunes::cargarCanciones);
    cargarArchivo(sistema, "publicidad.txt", &udeatunes::cargarMensajesPublicitarios);

    cout << "Datos cargados exitosamente." << endl;
    cout << "Usuarios: " << sistema.getCantidadUsuarios() << endl;
    cout << "Artistas: " << sistema.getCantidadArtistas() << endl;
    cout << "Albumes: " << sistema.getCantidadAlbumes() << endl;
    cout << "Canciones: " << sistema.getCantidadCanciones() << endl;
    cout << "Mensajes publicitarios: " << sistema.getCantidadMensajesPublicitarios() << endl;

    int opcion;

    do {
        mostrarMenuPrincipal();
        cin >> opcion;

        switch (opcion) {
        case 1: {
            string nickname;
            cout << "Ingrese su nickname: ";
            cin >> nickname;

            if (sistema.iniciarSesion(nickname)) {
                cout << "Bienvenido, " << nickname << "!" << endl;
                cout << "Tipo de membresia: " <<
                    (sistema.getUsuarioActual()->esPremium() ? "Premium" : "Estandar") << endl;

                manejarMenuUsuario(sistema);
            } else {
                cout << "Error: Usuario no encontrado." << endl;
            }
            break;
        }

        case 2:
            cout << "Gracias por usar UdeATunes. ¡Hasta luego!" << endl;
            break;

        default:
            cout << "Opcion invalida." << endl;
            break;
        }

    } while (opcion != 2);

    return 0;
}

