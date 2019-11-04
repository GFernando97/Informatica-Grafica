#include "aux.h"
#include "malla.h"

using namespace std;
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
  if(identificadorVBOv == 0)
    identificadorVBOv = CrearVBO(GL_ARRAY_BUFFER, 3*v.size()*sizeof(float), v.data());
  if(identificadorVBOf == 0)
    identificadorVBOf = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, 3*f.size()*sizeof(unsigned), f.data());
  
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   // completar (práctica 1)
	glBindBuffer(GL_ARRAY_BUFFER, identificadorVBOv);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glEnableClientState(GL_VERTEX_ARRAY);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, identificadorVBOf);
	glDrawElements(GL_TRIANGLES, 3*f.size(),GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
}
// -----------------------------------------------------------------------------
// Visualización en modo Ajedrez

void Malla3D::draw_ModoAjedrez(int inicio){
	std::vector<Tupla3i> chessF;

  	for (int i = inicio; i < f.size(); i += 2)
    	chessF.push_back(f[i]);

  	glEnableClientState(GL_VERTEX_ARRAY);
  	glVertexPointer(3, GL_FLOAT, 3, v.data());
  	glDrawElements(GL_TRIANGLES, chessF.size()*3, GL_UNSIGNED_INT, chessF.data());
  	glDisableClientState(GL_VERTEX_ARRAY);

}

//-----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(int modoDibujado, bool chessMode, int inicio)
{
	if(chessMode==false){
		if(modoDibujado==1){
			draw_ModoInmediato();
		}
		else draw_ModoDiferido();
	}
	

	else draw_ModoAjedrez(inicio);
}

//-----------------------------------------------------------------------------
// Función de calcular normales
void Malla3D::calcular_normales(){

	glEnable(GL_NORMALIZE);

	for(int i = 0; i < v.size(); i++){
		
	}
}

