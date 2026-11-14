#ifndef PLANTA_H
#define PLANTA_H
#include <string>

using namespace std;

class Planta {
public:
    Planta(string n,
           string esp,
           string lug,
           string l,
           string f,
           float ag = 100,
           int d = 0);

    string getNombre();
    string getEspecie();
    string getLugar();
    string getLuz();
    string getFoto();
    float getAgua();
    float getMinimo();
    int getDias();

    void setFoto(string nuevaFoto);
    void setAgua(float nuevoNivel);

    bool faltaAgua();
    void pasarDias(int d);
    void regar();
    void mostrarLinea(int num);
    void mostrarInfo();

private:
    string nombre;
    string especie;
    string lugar;
    string luz;
    string luzIdeal;
    string foto;
    float agua;
    float minimo;
    float gastoDiario;
    int dias;

    void datosPorEspecie();
    float factorLuz();
};

#endif //PLATA_H
