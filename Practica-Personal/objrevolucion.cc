#include "aux.h"
#include "objrevolucion.h"
#include "ply_reader.h"


// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)


ObjRevolucion::ObjRevolucion(const std::string &nombreArchivo, int num_instancias, bool tapa_sup, bool tapa_inf) 
{
	std::vector<Tupla3f> perfil;
	ply::read_vertices(nombreArchivo, perfil);
	crearMalla(perfil, num_instancias, tapa_sup, tapa_inf);
}

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf)
{
	crearMalla(archivo, num_instancias, tapa_sup, tapa_inf );
}

void ObjRevolucion::crearMalla(const std::vector<Tupla3f> & perfil_original, const int num_instancias_perf, const bool tapa_sup, const bool tapa_inf) 
{
	Tupla3f vAux;
	Tupla3i fAux;
	const int M = perfil_original.size();
	const int N = num_instancias_perf;
	int valA, valB,valC;

	//Calculamos los vertices 

	for(int i= 0; i< N; i++){
		for(int j = 0; j < M; j++){
			vAux(X) = perfil_original[j](X) * cos(((2*M_PI)/N)*i);
			vAux(Y) = perfil_original[j](Y);
			vAux(Z) = perfil_original[j](X) * sin(((2*M_PI)/N)*i);

			v.push_back(vAux);
		}
	}

	//calculamos las caras
	for(int i = 0; i < N; i++){
		for(int j = 0; j < M-1; j++){
			valA = M*i+j;
			valB = M*((i+1)%N)+j;

			f.push_back({valB, valA, valB+1});
			f.push_back({valB+1, valA, valA+1});
		}
	}

	//Si el booleano tapa_sup es true, calculamos la tapa superior
	if(tapa_sup){
		vAux(X) = 0.0;
		vAux(Y) = v[0](Y);
		vAux(Z) = 0.0;
		v.push_back(vAux);


		for(int i= 0; i <N; i++){
			valA = M*i;			
			valB = M*((i+1)%N);
			valC = N*M;


			f.push_back({valA, valB, valC});
		}
	}

	if(tapa_inf){
		vAux(X) = 0.0;
		vAux(Y) = v[perfil_original.size()-1](Y);
		vAux(Z) = 0.0;

		v.push_back(vAux);

		for(int i = 0; i < N; i++){
			valA = (N*M+1);
			valB = M + M*((i+1)%N)-1;
			valC = M*(i+1)-1;

			f.push_back({valA, valB, valC});
		}
	}
}
