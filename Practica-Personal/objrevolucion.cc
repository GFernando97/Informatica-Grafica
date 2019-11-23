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

ObjRevolucion::ObjRevolucion(const std::string &nombreArchivo) {
	std::vector<Tupla3f> perfil;
	const int N = 20;

	ply::read_vertices(nombreArchivo, perfil);
}

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
    
}

void ObjRevolucion::crearMalla(const std::vector<Tupla3f> & perfil_original, const int num_instancias_perf, const bool conTapas) {
	Tupla3f vAux;
	const float parte = (2*M_PI) /num_instancias_perf;
	const int M = perfil_original.size();
	int a, b;

	for (int i = 0; i < num_instancias_perf; i++){
		for (int j = 0; j < M; j++){
			vAux(X) = perfil_original[j](X) * cos(parte *i);
			vAux(Y) = perfil_original[j](Y);
			vAux(Z) = perfil_original[j](Z) * sin(parte *i);

			v.push_back(vAux);
		}
	}


	for (int i = 0;  i  < num_instancias_perf; i++){
		for (int j = 0; j < M; j++){
			a = M*i+j;
			b = M*((i+1) % num_instancias_perf) + j;

			f.push_back(Tupla3i(b, a, b+1));
			f.push_back(Tupla3i(b+1, a, a+1));
		}
	}

	if(conTapas){

		v.push_back(Tupla3f(0.0, v[0](Y), 0.0));

		for(int i = 0; i < num_instancias_perf; i++){
			f.push_back(Tupla3i(M*i, M*((i+1)% num_instancias_perf), num_instancias_perf*M));
		}

		v.push_back(Tupla3f(0.0, v[perfil_original.size()-1](Y), 0.0));

		for(int i = 0; i < num_instancias_perf; i++){
			f.push_back(Tupla3i(num_instancias_perf*M+1, M+M*((i+1)%num_instancias_perf)-1, M*(i+1)-1));
		}

	}
}
