#include "planta.h"
#include <iostream>

using namespace std;

Planta::Planta(string n, string esp, string lug, string l, string f, float ag, int d) {
    nombre = n;
    especie = esp;
    lugar = lug;
    luz = l;
    foto = f;
    agua = ag;
    dias = d;

    if (especie == "") especie = "Desconocida";
    if (lugar == "") lugar = "Interior";
    if (luz == "") luz = "Luz indirecta";
    if (foto == "") foto = "sin_foto.png";
    if (agua > 100) agua = 100;
    if (agua < 0) agua = 0;

    datosPorEspecie();
}

void Planta::datosPorEspecie() {
    if (especie == "Monstera") {
        minimo = 30;
        gastoDiario = 10;
        luzIdeal = "Luz indirecta";
    } else if (especie == "Ficus") {
        minimo = 35;
        gastoDiario = 9;
        luzIdeal = "Ventana con sol";
    } else if (especie == "Helecho") {
        minimo = 45;
        gastoDiario = 14;
        luzIdeal = "Sombra interior";
    } else if (especie == "Potus") {
        minimo = 25;
        gastoDiario = 8;
        luzIdeal = "Luz indirecta";
    } else if (especie == "Lengua de suegra") {
        minimo = 20;
        gastoDiario = 5;
        luzIdeal = "Luz indirecta";
    } else if (especie == "Cactus / Suculenta") {
        minimo = 15;
        gastoDiario = 4;
        luzIdeal = "Ventana con sol";
    } else {
        minimo = 30;
        gastoDiario = 10;
        luzIdeal = "Luz indirecta";
    }
}

string Planta::getNombre() {
    return nombre;
}
string Planta::getEspecie() {
    return especie;
}
string Planta::getLugar() {
    return lugar;
}
string Planta::getLuz() {
    return luz;
}
string Planta::getFoto() {
    return foto;
}
float Planta::getAgua() {
    return agua;
}
float Planta::getMinimo() {
    return minimo;
}
int Planta::getDias() {
    return dias;
}

void Planta::setFoto(string nuevaFoto) {
    if (nuevaFoto != "") {
        foto = nuevaFoto;
    }
}

void Planta::setAgua(float nuevoNivel) {
    if (nuevoNivel < 0) {
        agua = 0;
    } else if (nuevoNivel > 100) {
        agua = 100;
    } else {
        agua = nuevoNivel;
    }
}

bool Planta::faltaAgua() {
    if (agua <= minimo) {
        return true;
    }
    return false;
}

// cambia que tan rapido se seca segun donde esta puesta
float Planta::factorLuz() {
    if (luz == "Exterior / Balcon") return 1.5;
    if (luz == "Ventana con sol") return 1.25;
    if (luz == "Sombra interior") return 0.7;
    return 1.0;
}

void Planta::pasarDias(int d) {
    if (d <= 0) return;

    float perdida = gastoDiario * factorLuz() * d;
    setAgua(agua - perdida);
    dias = dias + d;

    cout << nombre << " (" << especie << ") quedo con " << (int)agua << "% de agua." << endl;

    if (faltaAgua()) {
        cout << "  Alerta: a " << nombre << " le falta riego (bajo del " << (int)minimo << "%)." << endl;
        cout << "  Bot Telegram: recordatorio enviado para regar " << nombre << " en " << lugar << "." << endl;
    }
}

void Planta::regar() {
    agua = 100;
    cout << "Se rego la planta " << nombre << ". Agua al 100%." << endl;
}

void Planta::mostrarLinea(int num) {
    cout << num << ". " << nombre
         << " | Especie: " << especie
         << " | Lugar: " << lugar
         << " | Luz: " << luz
         << " | Agua: " << (int)agua << "%";

    if (faltaAgua()) {
        cout << " (REGAR!)";
    }
    cout << endl;
}

void Planta::mostrarInfo() {
    cout << "\nDatos de la planta:" << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Especie: " << especie << endl;
    cout << "Lugar: " << lugar << endl;
    cout << "Luz actual: " << luz << " (recomendada: " << luzIdeal << ")" << endl;
    cout << "Agua actual: " << (int)agua << "% (minimo antes de secarse: " << (int)minimo << "%)" << endl;
    cout << "Dias pasados: " << dias << endl;
    cout << "Foto: " << foto << endl;
    if (faltaAgua()) {
        cout << "Estado: Necesita agua" << endl;
    } else {
        cout << "Estado: Bien de agua" << endl;
    }
}
