#ifndef LUZ_DIRECCIONAL_H
#define LUZ_DIRECCIONAL_H

#include "luz.h"

class LuzDireccional : public Luz
{
protected:
	float alpha = 0.0;
	float beta = 0.0;
public:
	LuzDireccional(const Tupla2f & direccion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso);
	void activar();
	void variarAnguloAlpha(float incremento);
	void variarAnguloBeta(float incremento);
};
#endif