#include "material.h"

Material::Material( Tupla4f mDiffuse, Tupla4f mSpecular, Tupla4f mAmbient, float brightness)
{
	diffuse = mDiffuse;
	specular = mSpecular;
	ambient = mAmbient;
	this->brightness = brightness;
}


void Material::aplicar(){
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialf(GL_FRONT, GL_SHININESS, brightness);
}
