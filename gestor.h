//Alejandro Hernández Cerezo y Jose Manuel Pinto Lozano
#ifndef GESTOR_H
#define GESTOR_H
#include "listaUsuarios.h"
#include "listaPartidas.h"
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

struct tGestor{
	tListaPartidas partidas;
	tListaUsuarios usuarios;
	int indiceusuario;
	int indicepartida;
};

/*Inicializa la lista de partidas y usuarios, devolviendo false si no se ha podido realizar correctamente*/
bool arrancar(tGestor & gestor);	

//Recorre las partidas y rellena las partidas actuales de cada uno de los jugadores
void generarAccesos(tGestor & gestor);

//Guarda los datos modificados de la sesion y apaga el gestor
void apagar(tGestor & gestor);

//Funcion que recibe el usuario y la clave, y devuelve true si se ha iniciado sesion correctamente
bool iniciarSesion(tGestor & gestor, string const& idUsu, string const& clave);

//Añade un nuevo elemento a la lista de usuarios
bool crearCuenta(tGestor & gestor, string const& idUsu, string const& clave);

//Comprueba si tiene avisos
bool tieneAvisos(tGestor const& gestor, string & aviso);

//Elimina todos los avisos de un jugador
void limpiarAvisos(tGestor & gestor);

//String que recoge todos los datos del usuario
string resumenActividad(tGestor const& gestor);

//Funcion que ordena la lista de partidas de un usuario por fecha
void ordenar_Fecha(tGestor & gestor);

//Funcion que ordena la lista de partidas de un usuario por turno y fecha
void ordenar_Turno(tGestor & gestor);

//Devuelve el numero de partidas del usuario en curso
int partidasUsuario(tGestor const& gestor);

//Muestra por pantalla las datos de las partidas de un usuario y si tiene o no el turno
string cabecera(tGestor const& gestor, int posEnCurso);

//Crea una nueva partida
bool nuevaPartida(tGestor & gestor);

//Selecciona la partida indicada por el usuario
void apuntaPartida(tGestor & gestor, int posParEnCurso);

//Muestra el juego por pantalla
void mostrarPartida(tGestor const& gestor);

//Devuelve true si es el turno del usuario
bool esSuTurno(tGestor const& gestor);

//Funcion que controla el funcionamiento de la partida
void jugarPartida(tGestor & gestor, int col);

//Funcion que gestiona el abandono voluntario de la partida
void abandonarPartida(tGestor & gestor);

#endif