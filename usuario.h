//Alejandro Hernández Cerezo y Jose Manuel Pinto Lozano
#ifndef USUARIO_H
#define USUARIO_H

#include "listaAccesoPartidas.h"
#include "fecha.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

enum tNivel {Principiante, Medio, Experto};
enum tResultado {Gana, Pierde, Empata};

const int NRN = 5;

struct tUsuario{
	string identificador;
	string password;
	tNivel dificultad;
	int racha;
	bool espera;
	tFecha ult_conex;
	int ganadas;
	int empatadas;
	int perdidas;
	string avisos;
	tListaAccesoPartidas listapartidas;
};

void guardar(tUsuario const& usuario, ofstream & archivo);  //Guarda en el archivo los datos de tUsuario
void iniciar(tUsuario & usuario, string const& id, string const& pas); //Inicia un nuevo elemento tUsuario
bool cargar(tUsuario & usuario, ifstream & archivo);		//Carga del archivo los datos de tUsuario
bool iniciarSesion(tUsuario & usuario, string const& clave);		//Comprueba la existencia del usuario y la concoordancia de la clave
void limpiarAvisos(tUsuario & usuario); //Borra el campo avisos del usuario
void actualizarAvisos(tUsuario & usuario, string const& aviso); //Añade los nuevos avisos recibidos por el usuario a su campo avisos
string escribir(tNivel const & dificultad); //Muestra por pantalla enumerado tNivel
string mostrar_espera(bool espera); //Muestra por pantalla si el usuario esta esperando una nueva partida
bool nuevaPartida(tUsuario & usuario, const tParIdEn & par);  //Añade a su lista partidas una nueva en caso de no estar llena
void aplicarFinPartida(tUsuario & usuario, string const& idPar, tResultado resultado); //Modifica los campos del usuario con los nuevos datos al finalizar una partida
#endif