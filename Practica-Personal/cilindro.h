#ifndef CILINDRO_H
#define CILINDRO_H

#include "aux.h"
#include "objrevolucion.h"

class Cilindro : public ObjRevolucion
{
/*private:
	float altura ;
	float radio ;*/
public:
Cilindro(const int  num_vert_perfil=2, const int num_instancias_perf=20, const float altura=40.0, const float radio=10.0);
};

#endif