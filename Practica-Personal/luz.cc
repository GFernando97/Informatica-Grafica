#include "luz.h"

void Luz::activar(){
    glEnable(GL_LIGHTING);
    glEnable(id);
    glLightfv(id, GL_POSITION, position);
    glLightfv(id, GL_AMBIENT,  ambientColor);
    glLightfv(id, GL_SPECULAR, specularColor);
    glLightfv(id, GL_DIFFUSE,  diffuseColor);
}

void Luz::desactivar(){
        glDisable(id);
        glDisable(GL_LIGHTING);
}