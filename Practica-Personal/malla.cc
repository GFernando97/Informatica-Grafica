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
/*	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, v.data());
	glShadeModel(GL_FLAT);
	glColorPointer(3, GL_FLOAT, 0, immediateColor.data());

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, f.data());
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
*/
	//Con Material
	material.aplicar();
	if(nVertex.size()==0)
		calcular_normales();
	glEnable(GL_NORMALIZE);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, v.data());
	glNormalPointer(GL_FLOAT, 0, nVertex.data());
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawElements(GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, f.data());
	glDisableClientState(GL_NORMAL_ARRAY);
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

GLuint Malla3D::CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram)
{
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
  if(identificadorVBOc == 0)
    identificadorVBOc = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, 3*deferredColor.size()*sizeof(unsigned), deferredColor.data());
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   // completar (práctica 1)
	glBindBuffer(GL_ARRAY_BUFFER, identificadorVBOv);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glEnableClientState(GL_VERTEX_ARRAY);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, identificadorVBOf);

	glBindBuffer(GL_ARRAY_BUFFER, identificadorVBOc);
	glColorPointer(3, GL_FLOAT, 0, 0);	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glEnableClientState(GL_COLOR_ARRAY);
	glShadeModel(GL_FLAT);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawElements(GL_TRIANGLES, 3*f.size(),GL_UNSIGNED_INT, 0);

	glDisableClientState(GL_COLOR_ARRAY);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableClientState(GL_VERTEX_ARRAY);
}
// -----------------------------------------------------------------------------
// Visualización en modo Ajedrez

void Malla3D::draw_ModoAjedrez()
{
	std::vector<Tupla3i> chessPairsFaces;
	std::vector<Tupla3i> chessOddsFaces;
  	for (int i = 0; i < f.size(); i+=2){
    		chessPairsFaces.push_back(f[i]);
    		chessOddsFaces.push_back(f[i+1]);
  	}

 
  	glEnableClientState(GL_VERTEX_ARRAY);
  	glEnableClientState(GL_COLOR_ARRAY);

  	glVertexPointer(3, GL_FLOAT, 0, v.data());
  	glColorPointer(3, GL_FLOAT, 0, pairColor.data());
	glDrawElements(GL_TRIANGLES, 3*chessPairsFaces.size(), GL_UNSIGNED_INT, chessPairsFaces.data());
	glColorPointer(3, GL_FLOAT, 0, oddColor.data());
	glDrawElements(GL_TRIANGLES, 3*chessOddsFaces.size(), GL_UNSIGNED_INT, chessOddsFaces.data());
  	
  	glDisableClientState(GL_COLOR_ARRAY);
  	glDisableClientState(GL_VERTEX_ARRAY);
}

//-----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(int modoDibujado, bool chessMode)
{
	if(chessMode){
		draw_ModoAjedrez();
	}
	else{
		if(modoDibujado==0)
			draw_ModoDiferido();
		else if(modoDibujado==1)
			draw_ModoInmediato();
	}
}

//-----------------------------------------------------------------------------
// Función de calcular normales
void Malla3D::calcular_normales()
{
	vector<Tupla3f> NVertex;
	Tupla3f vAux1, vAux2, vAux3;

	vector<int> mod;


	for(int i = 0; i < v.size(); i++){
		nVertex.push_back({0.0, 0.0, 0.0});
	}

	for(int i= 0; i < f.size(); i++){
		vAux1 = v[f[i](X)];
		vAux2 = v[f[i](Y)];
		vAux3 = v[f[i](X)];

		Tupla3f dir1, dir2;

		dir1 = { {vAux2(X)-vAux1(X)}, 
				 {vAux2(Y)-vAux1(Y)},
				 {vAux2(Z)-vAux1(Z)}
				};

		dir2 = { {vAux3(X)-vAux1(X)},
				 {vAux3(Y)-vAux1(Y)},
				 {vAux3(Z)-vAux1(Z)}
				};

		Tupla3f producto_vect;

		producto_vect(X) = dir1(Y)*dir2(Z) - dir1(Z)*dir2(Y);
		producto_vect(Y) = dir1(Z)*dir2(X) - dir1(X)*dir2(Z);
		producto_vect(Z) = dir1(X)*dir2(Y) - dir1(Y)*dir2(X);

		float mod = sqrt(producto_vect(X)*producto_vect(X) + 
						 producto_vect(Y)*producto_vect(Y) + 
						 producto_vect(Z)*producto_vect(Z));

		nFaces.push_back({(int)producto_vect(X)/mod, (int)producto_vect(Y)/mod, (int)producto_vect(Z)/mod});
		

	 	nVertex[f[i](X)](X) += nFaces[i](X);
	    nVertex[f[i](X)](Y) += nFaces[i](Y);
	    nVertex[f[i](X)](Z) += nFaces[i](Z);

	    nVertex[f[i](Y)](X) += nFaces[i](X);
	    nVertex[f[i](Y)](Y) += nFaces[i](Y);
	    nVertex[f[i](Y)](Z) += nFaces[i](Z);

	    nVertex[f[i](Z)](X) += nFaces[i](X);
	    nVertex[f[i](Z)](Y) += nFaces[i](Y);
	    nVertex[f[i](Z)](Z) += nFaces[i](Z);
	}
}


//Funciones auxiliares para seleccion de colores para las caras(triangulos)
void Malla3D::immediateColorPicker(const float R, const float G, const float B)
{
	for(int i = 0; i < v.size(); i++){
		immediateColor.push_back({R,G,B});
	}
}

void Malla3D::deferredColorPicker(const float R, const float G, const float B)
{
	for(int i=0; i < v.size(); i++){
		deferredColor.push_back({R,G,B});
	}
}

void Malla3D::chessColorPicker(const Tupla3f Color1, const Tupla3f Color2)
{
		for(int i = 0; i < v.size(); i++){
  		oddColor.push_back(Color1);
  		pairColor.push_back(Color2);
  	}
}

