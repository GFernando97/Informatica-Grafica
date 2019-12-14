#include "luz.h"

void Luz::activar(){
	glEnable(id);
	glLightfv(id, GL_AMBIENT, ambientColor);
	glLightfv(id, GL_DIFFUSE, diffuseColor);
	glLightfv(id, GL_SPECULAR, specularColor);
	glLightfv(id, GL_POSITION, position);


}