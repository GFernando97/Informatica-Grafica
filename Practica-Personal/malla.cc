#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato()
{
  // visualizar la malla usando glDrawElements,
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, v.data());

	glDrawElements(GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, f.data());
	glDisableClientState(GL_VERTEX_ARRAY);

  
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

GLuint Malla3D::CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram){
	GLuint id_vbo;

	glGenBuffers(1, &id_vbo);
	glBindBuffer(tipo_vbo, id_vbo);

	glBufferData(tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW);

	glBindBuffer(tipo_vbo, 0);
	return id_vbo;
}

void Malla3D::draw_ModoDiferido()
{
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   // completar (práctica 1)
	glBindBuffer(GL_ARRAY_BUFFER, identificadorVBOv);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glEnableClientState(GL_VERTEX_ARRAY);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, identificadorVBOf);
	glDrawElements(GL_TRIANGLES, 3*f.size(),GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw()
{
	draw_ModoInmediato();
}

