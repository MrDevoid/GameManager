//Alejandro Hernández Cerezo y Jose Manuel Pinto Lozano
#include "listaUsuarios.h"

//Funcion auxiliar que desplaza a los usuarios del vector cuando se añade un nuevo usuario
void desplazar(tListaUsuarios & usuarios, int & pos){
	usuarios.push_back(tUsuario());						/*Se añade variable vacia y despues se desplaza a la posicion 
														en la que se debe encontrar el usuario*/
	for (int i = usuarios.size() - 1; i > pos; --i){
		usuarios[i] = usuarios[i - 1];
	}
}

void guardar(tListaUsuarios const& usuarios, ofstream & archivo){
	int tam = usuarios.size();
	archivo << tam << '\n';
	for (int i = 0; i < usuarios.size(); ++i){
		guardar(usuarios[i], archivo);
	}
}

bool cargar(tListaUsuarios & usuarios, ifstream & archivo){
	tUsuario usuario;
	int tam;
	int i = 0;
	archivo >> tam;
	while (i < tam && cargar(usuario, archivo)) usuarios.push_back(usuario), ++i;
	return !archivo.fail() && i == tam;
}

bool buscar(tListaUsuarios const& usuarios, string const& idUser, int & pos){
	int inicio = 0, fin = usuarios.size(), mitad;
	bool encontrado = false;
	while (inicio < fin && !encontrado){			//Se realiza busqueda binaria
		mitad = (inicio + fin - 1) / 2;		//Se actualiza la posicon mitad en funcion de su relacion de orden con el elemento buscado
		if (usuarios[mitad].identificador > idUser) fin = mitad;
		else if (usuarios[mitad].identificador < idUser) inicio = mitad + 1;
		else encontrado = true, pos = mitad;
	}
	if (!encontrado){
		pos = inicio;
		return false;
	}
	else return true;
}

bool insertar(tListaUsuarios & usuarios, tUsuario const& usuario, int & pos){
	if (!buscar(usuarios, usuario.identificador, pos)){			//En caso de no existir se inserta el nuevo usuario
		desplazar(usuarios, pos);
		usuarios[pos] = usuario;
		return true;
	}
	else return false;
}

bool buscarUsuarioEsperando(tListaUsuarios const& usuarios, tNivel nivel, int & pos){
	int i = 0; bool encontrado = false;
	while (i < usuarios.size() && !encontrado){
		if (usuarios[i].espera && usuarios[i].dificultad == nivel){
			pos = i;
			encontrado = true;
		}
		++i;
	}
	return encontrado;
}