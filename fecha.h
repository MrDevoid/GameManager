//Alejandro Hernández Cerezo y Jose Manuel Pinto Lozano
#ifndef FECHA_H
#define FECHA_H
#include <ctime>
#include <iomanip>
#include <sstream>
using namespace std;

typedef time_t tFecha;
tFecha fechaActual();  //Devuelve la fecha actual
string stringFecha(tFecha fecha, bool hora);  //Función que muestra la fecha en el formato Año/Mes/Dia (HH:MM:SS)

#endif