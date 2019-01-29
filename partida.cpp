//Alejandro Hernández Cerezo y Jose Manuel Pinto Lozano
#include "partida.h"

//Sobrecarga del tipo tEstadoPartida para interpretar los datos del archivo de carga
istream & operator>>(istream & archivo, tEstadoPartida & estado){
	int num;
	archivo >> num;
	switch (num){
		case 0:estado=EnCurso; break;
		case 1:estado=Terminada; break;
	}
	return archivo;
}

void nueva(tPartida & partida, string const& adv1, string const& adv2){
	ostringstream flujo;
	flujo << fechaActual() << "_" << adv1 << "_" << adv2;
	partida.identificador = flujo.str();
	partida.adv1 = adv1;
	partida.adv2 = adv2;
	partida.inicio = fechaActual();
	partida.fin = partida.inicio;
	partida.estado = EnCurso;
	iniciar(partida.juego);
}

void guardar(const tPartida & partida,ofstream & archivo){
	archivo << partida.identificador << '\n';
	archivo << partida.adv1 << '\n';
	archivo << partida.adv2 << '\n';
	archivo << partida.inicio <<" "<<partida.fin<<'\n';
	archivo << partida.estado << '\n';
	guardar(partida.juego, archivo);
}

bool cargar(tPartida & partida, ifstream & archivo){
	archivo >> partida.identificador >> partida.adv1 >> partida.adv2 >> partida.inicio >> partida.fin >> partida.estado;
	return !archivo.fail() && cargar(partida.juego, archivo);
}

bool actual(tPartida const& partida){
	if (partida.juego.turno == Jugador1) return true;
	else return false;
}

bool aplicarJugada(tPartida & partida, int col){
	if (aplicarJugada(partida.juego, col)){
		partida.fin = fechaActual();
		if (partida.juego.estado != Jugando){  //Solo en caso de que ya no se este jugando se pasara a partida terminada
			partida.estado = Terminada;
			partida.fin = fechaActual();
		}
		return true;
	}
	return false; //Solo se devuelve false en caso de movimiento invalido o de que el estado anterior no sea jugando
}

void abandonar(tPartida & partida){
	partida.estado = Terminada;
	partida.fin = fechaActual();
}