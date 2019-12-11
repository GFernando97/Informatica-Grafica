#ifndef _CONO_H
#define _CONO_H

#include "aux.h"
#include "objrevolucion.h"

class Cono : public ObjRevolucion
{
private:
	float altura;
	float radio;
public:
	Cono(const int num_vert_perfil=2, const int num_instancias_perf=20, const float altura=40.0, const float radio=30.0);
};

#endif