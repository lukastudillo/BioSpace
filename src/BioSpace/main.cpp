#include "gestor_inventario.h"
#include <iostream>
#include <string>

using namespace std;

string pedirEspecie() {
    cout << "\nElige la especie de la planta:" << endl;
    cout << "1. Monstera (Costilla de Adan)" << endl;
    cout << "2. Ficus" << endl;
    cout << "3. Helecho" << endl;
    cout << "4. Potus" << endl;
    cout << "5. Lengua de suegra" << endl;
    cout << "6. Cactus o Suculenta" << endl;
    cout << "7. Otra especie (escribir nombre o no se sabe)" << endl;
    cout << "Opcion: ";

    int op = 0;
    cin >> op;
    cin.ignore();

    if (op == 1) return "Monstera";
    if (op == 2) return "Ficus";
    if (op == 3) return "Helecho";
    if (op == 4) return "Potus";
    if (op == 5) return "Lengua de suegra";
    if (op == 6) return "Cactus / Suculenta";

    string otra;
    cout << "Escribe cual es (o aprieta Enter si no sabes): ";
    getline(cin, otra);
    if (otra == "") {
        otra = "Desconocida";
    }
    cout << "Se usaran condiciones generales para esta planta." << endl;
    return otra;
}

string pedirLuz() {
    cout << "\nQue tanta luz le llega donde esta?" << endl;
    cout << "1. Exterior / Balcon (sol directo)" << endl;
    cout << "2. Ventana con sol" << endl;
    cout << "3. Luz indirecta (pieza iluminada sin sol directo)" << endl;
    cout << "4. Sombra interior (lejos de la ventana o bano)" << endl;
    cout << "Opcion: ";

    int op = 0;
    cin >> op;
    cin.ignore();

    if (op == 1) return "Exterior / Balcon";
    if (op == 2) return "Ventana con sol";
    if (op == 4) return "Sombra interior";
    return "Luz indirecta";
}

int main() {
    GestorInventario gestor;
    gestor.cargarCSV();

    int op = 0;
    while (op != 11) {
        cout << "\n--- BIOSPACE ---" << endl;
        cout << "1. Ver plantas" << endl;
        cout << "2. Buscar planta" << endl;
        cout << "3. Seleccionar una planta (ver datos / regar / borrar)" << endl;
        cout << "4. Agregar planta" << endl;
        cout << "5. Regar todas" << endl;
        cout << "6. Regar una planta" << endl;
        cout << "7. Cambiar foto" << endl;
        cout << "8. Eliminar planta" << endl;
        cout << "9. Pasar dias (simular)" << endl;
        cout << "10. Ver historial" << endl;
        cout << "11. Salir" << endl;
        cout << "Opcion: ";

        if (!(cin >> op)) {
            cin.clear();
            cin.ignore(1000, '\n');
            op = 0;
        } else {
            cin.ignore();
        }

        if (op == 1) {
            gestor.mostrarTodo();
        } else if (op == 2) {
            string texto;
            cout << "Que quieres buscar?: ";
            getline(cin, texto);
            gestor.buscar(texto);
        } else if (op == 3) {
            gestor.mostrarTodo();
            if (gestor.getCantidad() > 0) {
                int num = 0;
                cout << "Numero de planta: ";
                cin >> num;
                cin.ignore();

                int pos = num - 1;
                int subOp = 0;
                while (subOp != 4) {
                    Planta* p = gestor.obtener(pos);
                    if (p == nullptr) break;

                    p->mostrarInfo();
                    cout << "\n1. Regar" << endl;
                    cout << "2. Cambiar foto" << endl;
                    cout << "3. Eliminar" << endl;
                    cout << "4. Volver" << endl;
                    cout << "Opcion: ";
                    cin >> subOp;
                    cin.ignore();

                    if (subOp == 1) {
                        gestor.regarUna(pos);
                    } else if (subOp == 2) {
                        string nf;
                        cout << "Nueva foto: ";
                        getline(cin, nf);
                        gestor.cambiarFoto(pos, nf);
                    } else if (subOp == 3) {
                        gestor.eliminar(pos);
                        break;
                    }
                }
            }
        } else if (op == 4) {
            cout << "\nNueva planta:" << endl;
            string nom = "";
            while (nom == "") {
                cout << "Nombre para tu panta: ";
                getline(cin, nom);
            }

            string esp = pedirEspecie();

            string lug;
            cout << "\nEn que parte de la casa esta? (ej: living, pieza): ";
            getline(cin, lug);

            string l = pedirLuz();

            string f;
            cout << "\nNombre de archivo de foto (enter para omitir): ";
            getline(cin, f);

            cout << "\n1. Guardar / 2. Cancelar: ";
            int conf = 1;
            cin >> conf;
            cin.ignore();

            if (conf != 2) {
                Planta* nueva = new Planta(nom, esp, lug, l, f);
                gestor.agregar(nueva);
                cout << "Planta guardada." << endl;
            } else {
                cout << "Cancelado." << endl;
            }
        } else if (op == 5) {
            gestor.regarTodas();
        } else if (op == 6) {
            gestor.mostrarTodo();
            if (gestor.getCantidad() > 0) {
                int num = 0;
                cout << "Numero de planta a regar: ";
                cin >> num;
                cin.ignore();
                gestor.regarUna(num - 1);
            }
        } else if (op == 7) {
            gestor.mostrarTodo();
            if (gestor.getCantidad() > 0) {
                int num = 0;
                cout << "Numero de planta: ";
                cin >> num;
                cin.ignore();
                string nf;
                cout << "Nueva foto: ";
                getline(cin, nf);
                gestor.cambiarFoto(num - 1, nf);
            }
        } else if (op == 8) {
            gestor.mostrarTodo();
            if (gestor.getCantidad() > 0) {
                int num = 0;
                cout << "Numero de planta a eliminar: ";
                cin >> num;
                cin.ignore();
                gestor.eliminar(num - 1);
            }
        } else if (op == 9) {
            int d = 0;
            cout << "Cuantos dias avanzaron?: ";
            cin >> d;
            cin.ignore();
            gestor.avanzarTiempo(d);
        } else if (op == 10) {
            gestor.verHistorial();
        } else if (op == 11) {
            gestor.guardarCSV();
            cout << "Datos guardados. Saliendo..." << endl;
        } else {
            cout << "Opcion no valida." << endl;
        }
    }

    return 0;
}
