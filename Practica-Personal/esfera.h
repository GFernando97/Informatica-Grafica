#ifndef _ESFERA_H
#define _ESFERA_H

#include "aux.h"
#include "objrevolucion.h"

class Esfera : public ObjRevolucion
{
private:
	float radio;
public:
	Esfera(const int num_vert_perfil=10, const int num_instancias_perf=40, const float radio=10.0);
};

#endif