#ifndef LUZ_H_
#define LUZ_H_

#include "aux.h"

class Luz
{
public:
	void activar();

protected:
	Tupla4f position;
	GLenum id;
	Tupla4f ambientColor;
	Tupla4f specularColor;
	Tupla4f diffuseColor;
};

#endif