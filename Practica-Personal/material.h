#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "aux.h"

class Material
{
private:
	Tupla4f diffuse;
	Tupla4f specular;
	Tupla4f ambient;
	float brightness = 0.0;

public:
	Material(){};
	Material( Tupla4f mDiffuse, Tupla4f mSpecular, Tupla4f mAmbient, float brightness);
	void aplicar();

};

#endif