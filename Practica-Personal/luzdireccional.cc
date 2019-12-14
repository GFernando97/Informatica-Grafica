#include "luzdireccional.h"

LuzDireccional::LuzDireccional(const Tupla2f & direccion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso)
{
	position(X) = direccion(X);
	position(Y) = direccion(Y);
	position(Z) = 1.0;
	position(W) = 1.0;

	id = idLuzOpenGL;

	ambientColor = colorAmbiente;
	specularColor = colorEspecular;
	diffuseColor = colorDifuso;
}


void LuzDireccional::activar(){
	glEnable(id);
	glLightfv(id, GL_AMBIENT, ambientColor);
	glLightfv(id, GL_DIFFUSE, diffuseColor);
	glLightfv(id, GL_SPECULAR, specularColor);
	glLightfv(id, GL_POSITION, position);


	position(Y) = cos((beta*M_PI)/180)*position(Y)-sin((beta*M_PI)/180)*position(Z);
	position(Z) = sin((beta*M_PI)/180)*position(Y)+cos((beta*M_PI)/180)*position(Z);

	glLightfv(id, GL_POSITION, position);
}

void LuzDireccional::variarAnguloAlpha(float incremento){
	alpha = alpha + incremento;
	alpha = (int)alpha % 360;
	this->activar();
}

void LuzDireccional::variarAnguloBeta(float incremento){
	beta = beta + incremento;
	beta = (int)beta % 360;
	this->activar();
}