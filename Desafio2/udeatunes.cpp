#include "udeatunes.h"


udeatunes::udeatunes():usuarioActual(nullptr), reproduciendo(false), cancionActual(nullptr),
    modoRepetir(false), cancionesReproducidas(0), limiteReproduccion(5),
    iteracionesTotales(0), gen(rd()) {}

udeatunes::~udeatunes()
{
}

bool udeatunes::cargarUsuarios(const string &archivo)
{
    ifstream file(archivo);
    if (!file.is_open()) return false;

    string linea;
    while (getline(file, linea)) {
        istringstream iss(linea);
        string nickname, tipo, ciudad, pais, fecha;

        if (iss >> nickname >> tipo >> ciudad >> pais >> fecha) {
            TipoMembresia tipoMem = (tipo == "premium") ? PREMIUM : ESTANDAR;
            usuarios.agregar(Usuario(nickname, tipoMem, ciudad, pais, fecha));
            iteracionesTotales++;
        }
    }
    file.close();
    return true;
}

bool udeatunes::cargarArtistas(const string &archivo)
{
    ifstream file(archivo);
    if (!file.is_open()) return false;

    string linea;
    while (getline(file, linea)) {
        istringstream iss(linea);
        int codigo, edad;
        string pais;

        if (iss >> codigo >> edad >> pais) {
            artistas.agregar(artista(codigo, edad, pais));
            iteracionesTotales++;
        }
    }
    file.close();
    return true;
}

bool udeatunes::cargarAlbumes(const string &archivo)
{
    ifstream file(archivo);
    if (!file.is_open()) return false;

    string linea;
    while (getline(file, linea)) {
        istringstream iss(linea);
        int codigo, duracion;
        string nombre, fecha, portada;

        if (iss >> codigo >> nombre >> fecha >> duracion >> portada) {
            albumes.agregar(album(codigo, nombre, fecha, duracion, portada));
            iteracionesTotales++;
        }
    }
    file.close();
    return true;
}

bool udeatunes::cargarCanciones(const string &archivo)
{
    ifstream file(archivo);
    if (!file.is_open()) return false;

    string linea;
    while (getline(file, linea)) {
        istringstream iss(linea);
        int identificador, duracion;
        string nombre, ruta128, ruta320;

        if (iss >> identificador >> nombre >> duracion >> ruta128 >> ruta320) {
            canciones.agregar(cancion(identificador, nombre, duracion, ruta128, ruta320));
            iteracionesTotales++;
        }
    }
    file.close();
    return true;
}

bool udeatunes::cargarMensajesPublicitarios(const string &archivo)
{
    ifstream file(archivo);
    if (!file.is_open()) return false;

    string linea;
    while (getline(file, linea)) {
        if (linea.empty()) continue;

        size_t pos = linea.find(' ');
        if (pos == string::npos) continue;

        string categoriaStr = linea.substr(0, pos);
        string contenido = linea.substr(pos + 1);

        CategoriaPubicidad categoria;
        if (categoriaStr == "C") categoria = CATEGORIA_C;
        else if (categoriaStr == "B") categoria = CATEGORIA_B;
        else if (categoriaStr == "AAA") categoria = CATEGORIA_AAA;
        else continue;

        mensajesPublicitarios.agregar(MensajePublicitario(contenido, categoria));
        iteracionesTotales++;
    }
    file.close();
    return true;
}

bool udeatunes::iniciarSesion(const string &nickname)
{
    for (int i = 0; i < usuarios.obtenerTamano(); i++) {
        Usuario* usuario = usuarios.obtener(i);
        if (usuario && usuario->getNickname() == nickname) {
            usuarioActual = usuario;
            iteracionesTotales++;
            return true;
        }
        iteracionesTotales++;
    }
    return false;
}

void udeatunes::cerrarSesion()
{
    usuarioActual = nullptr;
    detenerReproduccion();
}

Usuario *udeatunes::getUsuarioActual() const
{
    return usuarioActual;
}

bool udeatunes::iniciarReproduccionAleatoria()
{
    if (!usuarioActual || canciones.estaVacia()) return false;

    uniform_int_distribution<> dis(0, canciones.obtenerTamano() - 1);
    int indiceAleatorio = dis(gen);
    cancionActual = canciones.obtener(indiceAleatorio);

    if (cancionActual) {
        reproduciendo = true;
        cancionActual->incrementarReproducciones();
        cancionesReproducidas++;

        iteracionesTotales++;
        return true;
    }
    return false;
}

bool udeatunes::siguienteCancion()
{
    if (!usuarioActual || !reproduciendo) {
        return false;
    }

    if (modoRepetir && cancionActual) {
        cancionActual->incrementarReproducciones();
        iteracionesTotales++;
        return true;
    }

    if (usuarioActual->esPremium() && cancionActual) {
        pilaAnterior.apilar(cancionActual->getIdentificador());
    }

    uniform_int_distribution<> dis(0, canciones.obtenerTamano() - 1);
    int indiceAleatorio = dis(gen);
    cancionActual = canciones.obtener(indiceAleatorio);

    if (cancionActual) {
        cancionActual->incrementarReproducciones();
        cancionesReproducidas++;

        iteracionesTotales++;
        return true;
    }
    return false;
}

bool udeatunes::cancionAnterior()
{
    if (!usuarioActual || !usuarioActual->esPremium() || pilaAnterior.estaVacia()) {
        return false;
    }

    int* idCancionAnterior = pilaAnterior.obtenerTope();
    if (!idCancionAnterior) return false;

    for (int i = 0; i < canciones.obtenerTamano(); i++) {
        cancion* cancion = canciones.obtener(i);
        if (cancion && cancion->getIdentificador() == *idCancionAnterior) {
            cancionActual = cancion;
            pilaAnterior.desapilar();
            iteracionesTotales++;
            return true;
        }
        iteracionesTotales++;
    }
    return false;
}

void udeatunes::detenerReproduccion()
{
    reproduciendo = false;
    cancionActual = nullptr;
    modoRepetir = false;
    cancionesReproducidas = 0;

    while (!pilaAnterior.estaVacia()) {
        pilaAnterior.desapilar();
    }
}

void udeatunes::alternarRepetir()
{
    if (usuarioActual && usuarioActual->esPremium()) {
        modoRepetir = !modoRepetir;
    }
}

bool udeatunes::estaReproduciendo() const
{
    return reproduciendo;
}

cancion *udeatunes::getCancionActual() const {
    return cancionActual;
}

bool udeatunes::getModoRepetir()
{
    return modoRepetir;
}

int udeatunes::getCancionesReproducidas()
{
    return cancionesReproducidas;
}

bool udeatunes::agregarAFavoritos(int idCancion) {
    if (!usuarioActual || !usuarioActual->esPremium()) return false;

    bool cancionExiste = false;
    for (int i = 0; i < canciones.obtenerTamano(); i++) {
        cancion* Cancion = canciones.obtener(i);
        if (Cancion && Cancion->getIdentificador() == idCancion) {
            cancionExiste = true;
            break;
        }
        iteracionesTotales++;
    }

    if (cancionExiste) {
        iteracionesTotales++;
        return usuarioActual->agregarAFavoritos(idCancion);
    }
    return false;
}

bool udeatunes::eliminarDeFavoritos(int idCancion) {
    if (!usuarioActual || !usuarioActual->esPremium()) return false;
    iteracionesTotales++;
    return usuarioActual->eliminarDeFavoritos(idCancion);
}

bool udeatunes::seguirListaFavoritos(const string &nicknameUsuario) {
    if (!usuarioActual || !usuarioActual->esPremium()) return false;

    for (int i = 0; i < usuarios.obtenerTamano(); i++) {
        Usuario* usuario = usuarios.obtener(i);
        if (usuario && usuario->getNickname() == nicknameUsuario) {
            iteracionesTotales++;
            return usuarioActual->seguirListaFavoritos(*usuario);
        }
        iteracionesTotales++;
    }
    return false;
}

MensajePublicitario *udeatunes::obtenerMensajePublicitario() {
    if (mensajesPublicitarios.estaVacia()) return nullptr;

    ListaEnlazada<int> indicesPonderados;
    for (int i = 0; i < mensajesPublicitarios.obtenerTamano(); i++) {
        MensajePublicitario* mensaje = mensajesPublicitarios.obtener(i);
        if (mensaje) {
            int prioridad = mensaje->getPrioridad();
            for (int j = 0; j < prioridad; j++) {
                indicesPonderados.agregar(i);
            }
        }
        iteracionesTotales++;
    }

    if (indicesPonderados.estaVacia()) return nullptr;

    uniform_int_distribution<> dis(0, indicesPonderados.obtenerTamano() - 1);
    int indiceAleatorio = dis(gen);
    int* indice = indicesPonderados.obtener(indiceAleatorio);

    iteracionesTotales++;
    return indice ? mensajesPublicitarios.obtener(*indice) : nullptr;
}

cancion *udeatunes::buscarCancion(int idCancion) {
    for (int i = 0; i < canciones.obtenerTamano(); i++) {
        cancion* cancion = canciones.obtener(i);
        if (cancion && cancion->getIdentificador() == idCancion) {
            iteracionesTotales++;
            return cancion;
        }
        iteracionesTotales++;
    }
    return nullptr;
}

album *udeatunes::buscarAlbum(int codigoAlbum) {
    for (int i = 0; i < albumes.obtenerTamano(); i++) {
        album* album = albumes.obtener(i);
        if (album && album->getCodigo() == codigoAlbum) {
            iteracionesTotales++;
            return album;
        }
        iteracionesTotales++;
    }
    return nullptr;
}

artista *udeatunes::buscarArtista(int codigoArtista) {
    for (int i = 0; i < artistas.obtenerTamano(); i++) {
        artista* artista = artistas.obtener(i);
        if (artista && artista->getCodigo() == codigoArtista) {
            iteracionesTotales++;
            return artista;
        }
        iteracionesTotales++;
    }
    return nullptr;
}

int udeatunes::getIteracionesTotales() const {
    return iteracionesTotales;
}

void udeatunes::resetearIteraciones() {
    iteracionesTotales = 0;
}

int udeatunes::calcularMemoria() const {
    int memoria = 0;

    memoria += usuarios.obtenerTamano() * sizeof(Usuario);

    memoria += artistas.obtenerTamano() * sizeof(artista);

    memoria += albumes.obtenerTamano() * sizeof(album);

    memoria += canciones.obtenerTamano() * sizeof(cancion);

    memoria += mensajesPublicitarios.obtenerTamano() * sizeof(MensajePublicitario);

    memoria += sizeof(udeatunes);

    return memoria;
}
