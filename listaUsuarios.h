//Alejandro Hernández Cerezo y Jose Manuel Pinto Lozano
#ifndef LISTAUSUARIOS_H
#define LISTAUSUARIOS_H

#include "usuario.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
using tListaUsuarios = vector<tUsuario>;

void guardar(tListaUsuarios const& usuarios, ofstream & archivo);  //Guarda la lista de usuarios en el archivo
bool cargar(tListaUsuarios & usuarios, ifstream & archivo);			//Carga la lista de usuarios del archivo
bool buscar(tListaUsuarios const& usuarios, string const& idUser, int & pos);		/*Busca un usuario especifico y devuelve su posicion,
																					si no existe es la posicion en la que deberia estar*/
bool insertar(tListaUsuarios & usuarios, tUsuario const& usuario, int & pos);  //Inserta un nuevo usuario en caso de que no exista
bool buscarUsuarioEsperando(tListaUsuarios const& usuarios, tNivel nivel,int & pos); /*Busca los usuarios de tu mismo nivel que se 
																					 encuentran esperando para nueva partida y devuelve false si no existen*/
#endif