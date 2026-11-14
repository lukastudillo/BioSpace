#ifndef GESTOR_INVENTARIO_H
#define GESTOR_INVENTARIO_H
#include "planta.h"
#include <string>

using namespace std;

class GestorInventario {
public:
    GestorInventario();
    ~GestorInventario();

    void agregar(Planta* p, bool guardar = true);
    void eliminar(int pos);
    Planta* obtener(int pos);
    int getCantidad();

    void mostrarTodo();
    void buscar(string texto);
    void avanzarTiempo(int d);
    void regarUna(int pos);
    void regarTodas();
    void cambiarFoto(int pos, string nuevaFoto);

    void guardarCSV();
    void cargarCSV();
    void anotarHistorial(string accion, string detalle);
    void verHistorial();

private:
    Planta** lista;
    int maxPlantas;
    int cantidad;
    int diasTotales;

    void agrandarLista();
    void borrarMemoria();
};

#endif // GESTOR_INVENTARIO_H
