//Alejandro Hernández Cerezo y Jose Manuel Pinto Lozano
#include "gestor.h"


bool arrancar(tGestor & gestor){
	bool cond = false;
	ifstream archivopartidas, archivousuarios;
	archivopartidas.open("partidas.txt");
	archivousuarios.open("usuarios.txt");
	if (archivopartidas.is_open() && archivousuarios.is_open() &&
		cargar(gestor.partidas, archivopartidas) && cargar(gestor.usuarios, archivousuarios)){
		cond = true;
		generarAccesos(gestor);
	}
	archivopartidas.close();
	archivousuarios.close();
	return cond;
}

void generarAccesos(tGestor & gestor){
	int posicion;
	tParIdEn par;
	for (int i = 0; i < gestor.partidas.size(); ++i){
		if (gestor.partidas[i].estado == EnCurso){
			par.identificador = gestor.partidas[i].identificador;
			par.enlace = i;
			if (buscar(gestor.usuarios, gestor.partidas[i].adv1, posicion))
				insertar(gestor.usuarios[posicion].listapartidas, par);
			if (buscar(gestor.usuarios, gestor.partidas[i].adv2, posicion))
				insertar(gestor.usuarios[posicion].listapartidas, par);
		}		
	}
}

void apagar(tGestor & gestor){
	ofstream archivopartidas, archivousuarios;
	archivopartidas.open("partidas.txt");
	archivousuarios.open("usuarios.txt");
	guardar(gestor.partidas, archivopartidas);
	guardar(gestor.usuarios, archivousuarios);
	archivopartidas.close();
	archivousuarios.close();
}

//Menu Registro:

bool iniciarSesion(tGestor & gestor, string const& idUsu, string const& clave){
	int posicion;
	if (buscar(gestor.usuarios, idUsu, posicion)){
		if (iniciarSesion(gestor.usuarios[posicion], clave)){
			gestor.indiceusuario = posicion;
			return true;
		}
	}
	return false;
}

bool crearCuenta(tGestor & gestor, string const& idUsu, string const& clave){
	tUsuario usuario; int posicion;
	iniciar(usuario, idUsu, clave);	
	if (insertar(gestor.usuarios, usuario, posicion)){
		gestor.indiceusuario = posicion;
		return true;
	}
	return false;
}

bool tieneAvisos(tGestor const& gestor, string & aviso){
	if (!gestor.usuarios[gestor.indiceusuario].avisos.empty()){
		aviso = gestor.usuarios[gestor.indiceusuario].avisos;
		return true;
	}
	return false;
}

void limpiarAvisos(tGestor & gestor){
	limpiarAvisos(gestor.usuarios[gestor.indiceusuario]);
}

string resumenActividad(tGestor const& gestor){
	stringstream resumen;
	resumen << "Usuario: " << gestor.usuarios[gestor.indiceusuario].identificador << '\n'
			<< "Partidas ganadas: " << gestor.usuarios[gestor.indiceusuario].ganadas << '\n'
			<< "Partidas perdidas: " << gestor.usuarios[gestor.indiceusuario].perdidas << '\n'
			<< "Partidas empatadas: " << gestor.usuarios[gestor.indiceusuario].empatadas << '\n'
			<< "Nivel: " << escribir(gestor.usuarios[gestor.indiceusuario].dificultad) << '\n'
			<< "Racha: " << gestor.usuarios[gestor.indiceusuario].racha << '\n'
			<< "Estado: " << mostrar_espera(gestor.usuarios[gestor.indiceusuario].espera)<<'\n';	
	return resumen.str();	
}


// Menú Usuario:

//Funcion que devuelve true si es el turno del usuario por el que se pregunta
bool turno(tGestor const& gestor, int elemento){
	if (actual(gestor.partidas[elemento])) return gestor.usuarios[gestor.indiceusuario].identificador == gestor.partidas[elemento].adv1;
	else return gestor.usuarios[gestor.indiceusuario].identificador == gestor.partidas[elemento].adv2;
}

//Funcion que ordena por fecha la partida
struct ordFecha{
	bool operator()(tGestor const& gestor, tParIdEn const& elemento, tParIdEn const& elementoarray){
		return gestor.partidas[elemento.enlace].fin > gestor.partidas[elementoarray.enlace].fin;
	}
};

//Funcion que ordena por turno y fecha la partida
struct ordTurno{
	bool operator()(tGestor const& gestor, tParIdEn const& elemento, tParIdEn const & elementoarray){
		bool cond = turno(gestor, elemento.enlace);			
		if (cond == turno(gestor,elementoarray.enlace)){			//Llama a turno con ambas partidas, 									
			return ordFecha()(gestor, elemento, elementoarray);		//y en caso de coincidir en el turno, ordena por fecha
		}
		return cond;
	}
};

//Busqueda por insercion, que se emplea tanto para ordenar por turno como por fecha
template <typename Comp = less<T>>
void ordenarInsercion(tGestor const& gestor ,tListaAccesoPartidas & array, Comp ord = Comp()) {
	size_t N = array.size();
	for (size_t i = 1; i < N; ++i) { 
		tParIdEn elemento = array[i];
		size_t j = i; 
		while (j > 0 && ord(gestor,elemento, array[j - 1])) {
			array[j] = array[j - 1];
			--j;
		}
		array[j] = elemento;
	} 
}

void ordenar_Fecha(tGestor & gestor){
	ordenarInsercion(gestor, gestor.usuarios[gestor.indiceusuario].listapartidas, ordFecha());
}

void ordenar_Turno(tGestor & gestor){
	ordenarInsercion(gestor, gestor.usuarios[gestor.indiceusuario].listapartidas, ordTurno());
}

int partidasUsuario(tGestor const& gestor){
	return gestor.usuarios[gestor.indiceusuario].listapartidas.size();
}

string cabecera(tGestor const& gestor, int posEnCurso){
	int indice=gestor.usuarios[gestor.indiceusuario].listapartidas[posEnCurso].enlace;
	stringstream cabecera;
	if (turno(gestor,indice)) cabecera << " *  ";
	else cabecera << "    ";
	cabecera <<left << setw(17) << gestor.partidas[indice].adv1 <<left<<setw(17)<< gestor.partidas[indice].adv2 << left << stringFecha(gestor.partidas[indice].fin,true);
	return cabecera.str();
}

bool nuevaPartida(tGestor & gestor){
	int posicion;
	tPartida partida;
	tParIdEn par;
	//Comprueba que no ha completado el maximo de partidas y que aun no ha solicitado otra partida
	if (!llena(gestor.usuarios[gestor.indiceusuario].listapartidas) && !gestor.usuarios[gestor.indiceusuario].espera){
		//Busca un usuario de su mismo nivel en espera
		if (buscarUsuarioEsperando(gestor.usuarios, gestor.usuarios[gestor.indiceusuario].dificultad, posicion)){
			//En caso de encontrarlo, crea una nueva partida y la añade a la lista de partidas de cada usuario
			nueva(partida, gestor.usuarios[gestor.indiceusuario].identificador, gestor.usuarios[posicion].identificador);
			insertar(gestor.partidas, partida);
			gestor.indicepartida = gestor.partidas.size() - 1;
			par.enlace = gestor.partidas.size() - 1;
			par.identificador = gestor.partidas[par.enlace].identificador;
			nuevaPartida(gestor.usuarios[gestor.indiceusuario], par);
			nuevaPartida(gestor.usuarios[posicion], par);
			return true;
		}
		//En caso de no encontrar usuarios en espera, se pone el jugador en espera
		else gestor.usuarios[gestor.indiceusuario].espera = true;
	}
	return false;
}


//Menu Partida:

void apuntaPartida(tGestor & gestor, int posParEnCurso){
	gestor.indicepartida=gestor.usuarios[gestor.indiceusuario].listapartidas[posParEnCurso].enlace;
}

void mostrarPartida(tGestor const& gestor){
	mostrar(gestor.partidas[gestor.indicepartida].juego, gestor.partidas[gestor.indicepartida].adv1, gestor.partidas[gestor.indicepartida].adv2);
}

bool esSuTurno(tGestor const& gestor){
	if (actual(gestor.partidas[gestor.indicepartida])) return gestor.usuarios[gestor.indiceusuario].identificador == gestor.partidas[gestor.indicepartida].adv1;
	else return gestor.usuarios[gestor.indiceusuario].identificador == gestor.partidas[gestor.indicepartida].adv2;
}

//Funcion que busca el adversario del jugador actual en la partida seleccionada y devuelve su posicion
void encuentrarival(tGestor & gestor, int & pos){
	string rival;
	if (gestor.usuarios[gestor.indiceusuario].identificador==gestor.partidas[gestor.indicepartida].adv1){
		rival = gestor.partidas[gestor.indicepartida].adv2;
	}
	else rival = gestor.partidas[gestor.indicepartida].adv1;
	buscar(gestor.usuarios, rival, pos);
}

//Funcion que actualiza los datos del usuario y actualiza los avisos
void actualizarinfo(tGestor & gestor, int pos, tResultado act, tResultado otro, string const& aviso){
	aplicarFinPartida(gestor.usuarios[gestor.indiceusuario], gestor.partidas[gestor.indicepartida].identificador, act);
	aplicarFinPartida(gestor.usuarios[pos], gestor.partidas[gestor.indicepartida].identificador, otro);
	actualizarAvisos(gestor.usuarios[pos], aviso);
}


void jugarPartida(tGestor & gestor, int col){
	if (aplicarJugada(gestor.partidas[gestor.indicepartida], col) && gestor.partidas[gestor.indicepartida].juego.estado != Jugando){
		int pos;
		encuentrarival(gestor, pos);
		tResultado act, otro;
		stringstream aviso;
		if (gestor.partidas[gestor.indicepartida].estado == Ganador){
			act = Gana;
			otro = Pierde;
			aviso << "Has ganado la partida contra " << gestor.usuarios[gestor.indiceusuario].identificador << " el " << stringFecha(gestor.partidas[gestor.indicepartida].fin,false);
		}
		else{
			act = Empata, otro = Empata;
			aviso << "Has perdido la partida contra " << gestor.usuarios[gestor.indiceusuario].identificador << " el " << stringFecha(gestor.partidas[gestor.indicepartida].fin, false);
		}
		actualizarinfo(gestor, pos, act, otro, aviso.str());
	}
}

void abandonarPartida(tGestor & gestor){
	string rival;
	stringstream aviso;
	int pos;
	encuentrarival(gestor, pos);
	abandonar(gestor.partidas[gestor.indicepartida]);
	aviso << "Has ganado por abandono contra " << gestor.usuarios[gestor.indiceusuario].identificador << " el " << stringFecha(gestor.partidas[gestor.indicepartida].fin, false);
	actualizarinfo(gestor, pos, Pierde, Gana, aviso.str());

}