//Alejandro Hernández Cerezo y Jose Manuel Pinto Lozano
#ifndef LISTAPARTIDAS_H
#define LISTAPARTIDAS_H

#include "partida.h"
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

using tListaPartidas = vector<tPartida>;

void guardar(tListaPartidas const & partidas, ofstream & archivo); //Guarda la lista de partidas en el archivo
bool cargar(tListaPartidas & partidas, ifstream & archivo);	//Carga la lista partidas del archivo
void insertar(tListaPartidas & partidas, tPartida const& partida);	//Inserta una nueva partida en la lista de partidas

#endif