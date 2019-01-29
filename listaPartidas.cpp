//Alejandro Hernández Cerezo y Jose Manuel Pinto Lozano
#include "listaPartidas.h"

void guardar(tListaPartidas const & partidas, ofstream & archivo){
	archivo << partidas.size()<<'\n';		//Se escribe el tamaño del vector para despues conocer el numero de partidas
	for (int i = 0; i < partidas.size(); ++i){
		guardar(partidas[i], archivo);
	}
}

bool cargar(tListaPartidas & partidas, ifstream & archivo){
	int tam;
	bool cond = true;
	archivo >> tam;
	partidas.resize(tam);   //Se modifica el tamaño del vector al que indica el archivo (nº de partidas)
	for (int i = 0; i < tam && cond; ++i){
		cond = cargar(partidas[i], archivo);
	}
	return !archivo.fail()&&cond;
}

void insertar(tListaPartidas & partidas, tPartida const& partida){
	partidas.push_back(partida);
}