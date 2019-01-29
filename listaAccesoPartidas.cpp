//Alejandro Hernández Cerezo y Jose Manuel Pinto Lozano
#include "listaAccesoPartidas.h"

//Devuelve la posicion en la ListaAccesoPartidas a partir del indentificador de la partida
bool buscaridentificador(tListaAccesoPartidas & lista, string const& id,int & posicion){
	for (int i = 0; i < lista.size(); ++i){
		if (lista[i].identificador == id){
			posicion = i;
			return true;
		}
	}
	return false;
}

void iniciar(tListaAccesoPartidas & lista){
	
}

bool llena(tListaAccesoPartidas const& lista){
	return lista.size() >= MAX_PAR_US;
}

bool insertar(tListaAccesoPartidas & lista, tParIdEn par){
	if (!llena(lista)){				
		lista.push_back(par);		//En caso de quedar espacio añade el nuevo elemento tParIdEn
		return true;
	}
	return false;
}

bool eliminar(tListaAccesoPartidas & lista, string const& id){
	int posicion;
	if (buscaridentificador(lista, id, posicion)){
		lista[posicion] = lista[lista.size() - 1];  //Dada la posicion de la partida con el identificador id, la busca y la borra
		lista.pop_back();							//Para borrar intercambia con el último y este se elimina
		return true;
	}
	return false;
}