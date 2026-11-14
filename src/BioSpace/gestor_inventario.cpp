#include "gestor_inventario.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

GestorInventario::GestorInventario() {
    maxPlantas = 5;
    cantidad = 0;
    diasTotales = 0;
    lista = new Planta*[maxPlantas];
    for (int i = 0; i < maxPlantas; i++) {
        lista[i] = nullptr;
    }
}

GestorInventario::~GestorInventario() {
    borrarMemoria();
    delete[] lista;
}

void GestorInventario::borrarMemoria() {
    for (int i = 0; i < cantidad; i++) {
        if (lista[i] != nullptr) {
            delete lista[i];
            lista[i] = nullptr;
        }
    }
    cantidad = 0;
}


void GestorInventario::agrandarLista() {
    int nuevoMax = maxPlantas * 2;
    Planta** nuevaLista = new Planta*[nuevoMax];

    for (int i = 0; i < cantidad; i++) {
        nuevaLista[i] = lista[i];
    }
    for (int i = cantidad; i < nuevoMax; i++) {
        nuevaLista[i] = nullptr;
    }

    delete[] lista;
    lista = nuevaLista;
    maxPlantas = nuevoMax;
}

void GestorInventario::agregar(Planta* p, bool guardar) {
    if (p == nullptr) return;

    if (cantidad == maxPlantas) {
        agrandarLista();
    }

    lista[cantidad] = p;
    cantidad++;

    if (guardar) {
        anotarHistorial("Agregar", p->getNombre() + " (" + p->getEspecie() + ")");
        guardarCSV();
    }
}

void GestorInventario::eliminar(int pos) {
    if (pos < 0 || pos >= cantidad) {
        cout << "Numero no valido." << endl;
        return;
    }

    string nom = lista[pos]->getNombre();


    delete lista[pos];
    for (int i = pos; i < cantidad - 1; i++) {
        lista[i] = lista[i + 1];
    }
    lista[cantidad - 1] = nullptr;
    cantidad--;

    cout << "Se elimino la planta " << nom << "." << endl;
    anotarHistorial("Eliminar", nom);
    guardarCSV();
}

Planta* GestorInventario::obtener(int pos) {
    if (pos >= 0 && pos < cantidad) {
        return lista[pos];
    }
    return nullptr;
}

int GestorInventario::getCantidad() {
    return cantidad;
}

void GestorInventario::mostrarTodo() {
    cout << "\n--- Almacen de plantas (" << cantidad << ") ---" << endl;
    if (cantidad == 0) {
        cout << "No tienes plantas agregadas todavia." << endl;
        return;
    }
    for (int i = 0; i < cantidad; i++) {
        lista[i]->mostrarLinea(i + 1);
    }
}

void GestorInventario::buscar(string texto) {
    if (cantidad == 0) {
        cout << "No hay plantas en el almacen." << endl;
        return;
    }

    cout << "\nResultados para: " << texto << endl;
    int cont = 0;
    for (int i = 0; i < cantidad; i++) {
        if (lista[i]->getNombre().find(texto) != string::npos ||
            lista[i]->getEspecie().find(texto) != string::npos ||
            lista[i]->getLugar().find(texto) != string::npos ||
            lista[i]->getLuz().find(texto) != string::npos) {
            lista[i]->mostrarLinea(i + 1);
            cont++;
        }
    }
    if (cont == 0) {
        cout << "No se encontro ninguna planta con ese dato." << endl;
    }
}

void GestorInventario::avanzarTiempo(int d) {
    if (cantidad == 0) {
        cout << "No hay plantas para simular." << endl;
        return;
    }
    if (d <= 0) {
        cout << "Los dias tienen que ser mayor a 0." << endl;
        return;
    }

    diasTotales = diasTotales + d;
    cout << "\nPasaron " << d << " dias:" << endl;

    for (int i = 0; i < cantidad; i++) {
        lista[i]->pasarDias(d);
    }

    anotarHistorial("Simulacion", "Avance de " + to_string(d) + " dias");
    guardarCSV();
}

void GestorInventario::regarUna(int pos) {
    if (pos >= 0 && pos < cantidad) {
        lista[pos]->regar();
        anotarHistorial("Riego", lista[pos]->getNombre());
        guardarCSV();
    } else {
        cout << "Numero de planta incorrecto." << endl;
    }
}

void GestorInventario::regarTodas() {
    if (cantidad == 0) {
        cout << "No hay plantas para regar." << endl;
        return;
    }
    cout << "\nRegando todo el almacen..." << endl;
    for (int i = 0; i < cantidad; i++) {
        lista[i]->regar();
    }
    anotarHistorial("Riego total", "Se regaron todas las plantas");
    guardarCSV();
}

void GestorInventario::cambiarFoto(int pos, string nuevaFoto) {
    if (pos >= 0 && pos < cantidad) {
        lista[pos]->setFoto(nuevaFoto);
        cout << "Foto cambiada a: " << lista[pos]->getFoto() << endl;
        guardarCSV();
    } else {
        cout << "Numero de planta incorrecto." << endl;
    }
}

void GestorInventario::guardarCSV() {
    ofstream arch("plantas.csv");
    if (!arch.is_open()) return;

    arch << "nombre,especie,lugar,luz,foto,agua,dias\n";
    for (int i = 0; i < cantidad; i++) {
        arch << lista[i]->getNombre() << ","
             << lista[i]->getEspecie() << ","
             << lista[i]->getLugar() << ","
             << lista[i]->getLuz() << ","
             << lista[i]->getFoto() << ","
             << lista[i]->getAgua() << ","
             << lista[i]->getDias() << "\n";
    }
    arch.close();
}

void GestorInventario::cargarCSV() {
    ifstream arch("plantas.csv");
    if (!arch.is_open()) return;

    borrarMemoria();
    diasTotales = 0;

    string linea;
    getline(arch, linea); // saltar

    while (getline(arch, linea)) {
        if (linea == "") continue;

        stringstream ss(linea);
        string nom, esp, lug, l, f, sAgua, sDias;

        getline(ss, nom, ',');
        getline(ss, esp, ',');
        getline(ss, lug, ',');
        getline(ss, l, ',');
        getline(ss, f, ',');
        getline(ss, sAgua, ',');
        getline(ss, sDias, ',');

        if (nom != "") {
            float ag = 100;
            int d = 0;
            if (sAgua != "") ag = stof(sAgua);
            if (sDias != "") d = stoi(sDias);

            Planta* nueva = new Planta(nom, esp, lug, l, f, ag, d);
            agregar(nueva, false);

            if (d > diasTotales) {
                diasTotales = d;
            }
        }
    }
    arch.close();
}

void GestorInventario::anotarHistorial(string accion, string detalle) {
    ofstream arch("historial.csv", ios::app);
    if (!arch.is_open()) return;

    arch << "Dia " << diasTotales << " | " << accion << " | " << detalle << "\n";
    arch.close();
}

void GestorInventario::verHistorial() {
    ifstream arch("historial.csv");
    if (!arch.is_open()) {
        cout << "No hay historial todavia." << endl;
        return;
    }

    cout << "\n--- Historial ---" << endl;
    string linea;
    int cont = 0;
    while (getline(arch, linea)) {
        if (linea != "") {
            cout << linea << endl;
            cont++;
        }
    }
    if (cont == 0) {
        cout << "El historial esta vacio." << endl;
    }
    arch.close();
}
