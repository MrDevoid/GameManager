//Alejandro Hernández Cerezo y Jose Manuel Pinto Lozano
#ifndef LISTA_ACCESO_PARTIDAS_H
#define LISTA_ACCESO_PARTIDAS_H

#include <string>
#include <vector>
const int MAX_PAR_US = 10;
using namespace std;

struct tParIdEn{
	string identificador;
	int enlace;
};

using tListaAccesoPartidas = vector<tParIdEn>;

void iniciar(tListaAccesoPartidas & lista); //Inicia el vector de partidas en curso
bool llena(tListaAccesoPartidas const & lista); //Comprueba que el tamaño de tListaAccesoPartidas no supera MAX_PAR_US
bool insertar(tListaAccesoPartidas & lista, tParIdEn par); //Inserta un nuevo elemento tParIdEn en la lista
bool eliminar(tListaAccesoPartidas & lista, string const& id); //Elimina un elemento tParIdEn de la lista

#endif