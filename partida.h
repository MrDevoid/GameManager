//Alejandro Hernández Cerezo y Jose Manuel Pinto Lozano
#ifndef PARTIDA_H
#define PARTIDA_H

#include "fecha.h"
#include "Conecta4.h"
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;
enum tEstadoPartida {EnCurso, Terminada};

struct tPartida{
	string identificador;
	string adv1;
	string adv2;
	tFecha inicio;
	tFecha fin;
	tEstadoPartida estado;
	tConecta4 juego;
};


void nueva(tPartida & partida, string const& adv1, string const& adv2);		//Crea una nueva partida iniciando todos sus campos
void guardar(const tPartida & partida, ofstream & archivo);		//Guarda los datos de tPartida en el archivo
bool cargar(tPartida & partida, ifstream & archivo);		//Carga los datos de tPartida del archivo
bool actual(tPartida const& partida);		//Devuelve true en caso de ser el turno de Jugador 1, false en caso contrario
void abandonar(tPartida & partida);		//Actualiza los campos de una partida que se abandona
bool aplicarJugada(tPartida & partida, int col); //Aplica la jugada indicada si es posible y actualiza los campos de la partida
#endif