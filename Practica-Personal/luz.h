#ifndef LUZ_H_
#define LUZ_H_

#include "aux.h"

class Luz
{
public:
	Luz(){};
	void activar();
	void desactivar();

protected:
	GLenum id;
	Tupla4f position;
	Tupla4f ambientColor;
	Tupla4f specularColor;
	Tupla4f diffuseColor;
};

#endif