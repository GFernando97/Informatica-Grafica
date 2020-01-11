#include "material.h"

Material::Material( Tupla4f mDiffuse, Tupla4f mSpecular, Tupla4f mAmbient, float brightness)
{
	diffuse = mDiffuse;
	specular = mSpecular;
	ambient = mAmbient;
	this->brightness = brightness*128.0;
}


void Material::aplicar(){
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brightness);
}
