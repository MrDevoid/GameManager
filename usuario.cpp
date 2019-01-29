//Alejandro Hernández Cerezo y Jose Manuel Pinto Lozano
#include "usuario.h"

//Sobrecarga del tipo tNivel para interpretar los datos del archivo de carga
istream & operator>> (istream & flujo, tNivel & dif){
	int aux;
	flujo >> aux;
	switch (aux){
	case 0: dif = Principiante; break;
	case 1: dif = Medio; break;
	case 2: dif = Experto; break;
}
	return flujo;
}

void guardar(tUsuario const& usuario, ofstream & archivo){
	archivo << usuario.identificador << '\n' << usuario.password << '\n' << usuario.dificultad
		<< ' ' << usuario.racha << ' ' << usuario.espera << '\n' << usuario.ganadas << ' ' << usuario.perdidas
		<< ' ' << usuario.empatadas << '\n' << usuario.ult_conex << '\n' << usuario.avisos;
	if (usuario.avisos.empty()) archivo << '\n';		//En el caso de que no existan avisos, se añade un salto de linea para mantener la estructura del archivo
	archivo << "_X_X_X_" << '\n';
}

void iniciar(tUsuario & usuario, string const& id, string const& pas){
	usuario.identificador = id;
	usuario.password = pas;
	usuario.dificultad = Principiante;
	usuario.racha = 0;
	usuario.espera = false;
	usuario.ganadas = 0;
	usuario.perdidas = 0;
	usuario.empatadas = 0;
	usuario.ult_conex = fechaActual();
	iniciar(usuario.listapartidas);
}

bool cargar(tUsuario & usuario, ifstream & archivo){
	archivo >> usuario.identificador >> usuario.password
		>> usuario.dificultad >> usuario.racha >> usuario.espera >> usuario.ganadas >>
		usuario.perdidas >> usuario.empatadas >> usuario.ult_conex;
	usuario.avisos = "";		//Se inicializa la variable para que no se acumulen los avisos de distintos usuarios
	string aviso="";
	getline(archivo, aviso);
	while (aviso != "_X_X_X_"){
		if (!aviso.empty())	aviso += '\n';			//En caso de que se lea una linea vacia no se añade salto de linea porque no existen avisos
		usuario.avisos += aviso;
		getline(archivo, aviso);
	}
	
	return !archivo.fail();
}

bool iniciarSesion(tUsuario & usuario, string const& clave){
	if (usuario.password == clave){
		usuario.ult_conex = fechaActual();
		return true;
	}
	else return false;
}

void limpiarAvisos(tUsuario & usuario){
	usuario.avisos.clear();
}

void actualizarAvisos(tUsuario & usuario, string const& aviso){
	usuario.avisos += aviso;
	usuario.avisos += '\n';
}

string escribir (tNivel const & dificultad){
	switch (dificultad){
	case 0: return "Principiante";
	case 1: return "Medio";
	case 2: return "Experto";
	}
}

string mostrar_espera(bool espera){
	if (espera) return "Ya está buscando partida";
	else return "Buscando nuevos adversarios...";
}

bool nuevaPartida(tUsuario & usuario, const tParIdEn & par){
	if (!llena(usuario.listapartidas)){
		insertar(usuario.listapartidas, par);
		usuario.espera = false;
		return true;
	}
	return false;
}

//Sobrecarga del tipo tNivel para subir de nivel
void operator++(tNivel & a){
	  a = tNivel(a + 1);
} 

//Sobrecarga del tipo tNivel para bajar de nivel
void operator--(tNivel &a){
	a = tNivel(a - 1);
}

//Funcion auxiliar que modifica campos del usuario en caso de ganar
void ganada(tUsuario & usuario){
	if (usuario.racha < 0) usuario.racha = 0;		//Si viene de una racha negativa esta primero se inicializa
	++usuario.racha;
	++usuario.ganadas;
	if (usuario.racha == NRN && usuario.dificultad != Experto){ //En caso de nivel Experto no se puede subir más de nivel
		++usuario.dificultad;
		usuario.racha = 0;		//Una vez que se sube de nivel la racha se inicializa
	}
}  

//Funcion auxiliar que modifica campos del usuario en caso de perder
void perdida(tUsuario & usuario){
	if (usuario.racha > 0) usuario.racha = 0;  //Si viene de una racha positivoa esta primero se inicializa
	--usuario.racha;
	++usuario.perdidas;
	if (usuario.racha == -NRN && usuario.dificultad != Principiante){ //En caso de nivel Principiante no se puede bajar más de nivel
		--usuario.dificultad;
		usuario.racha = 0;		//Una vez que se baja de nivel la racha se inicializa
	}
}

//Funcion auxiliar que modifica campos del usuario en caso de empatar
void empate(tUsuario & usuario){
	usuario.racha = 0;		//Se inicializa la racha y no se pueden producir subidas o bajadas de nivel
	++usuario.empatadas;
}

void aplicarFinPartida(tUsuario & usuario, string const& idPar, tResultado resultado){
	switch (resultado){
	case Gana:ganada(usuario); break;
	case Pierde:perdida(usuario); break;
	case Empata:empate(usuario);break;
	}
	eliminar(usuario.listapartidas,idPar);
}