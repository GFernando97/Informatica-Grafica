#include "aux.h"
#include "malla.h"

using namespace std;
// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato(visualizacion modoVisualizacion, tipoSombreado sombreadoSel, variacionAngulo anguloSel, incDecAngulo variacionSelec)
{
  // visualizar la malla usando glDrawElements,
	if(modoVisualizacion != ILUMINACION){
		if(modoVisualizacion!= CHESSMODE){
			glShadeModel(GL_FLAT);
			glEnable(GL_CULL_FACE);

			glEnableClientState(GL_VERTEX_ARRAY);
		    glVertexPointer(3, GL_FLOAT, 0, v.data());
		    glShadeModel(GL_FLAT);
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(3, GL_FLOAT, 0, immediateColor.data());

			if(modoVisualizacion==SOLIDO){
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			else if(modoVisualizacion==PUNTOS){
				  glDisable(GL_CULL_FACE);
				  glPointSize(2.0);
				  glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			}

			else if(modoVisualizacion==LINEAS){
				glPolygonMode(GL_FRONT, GL_LINE);
			}

			glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, f.data());
			glDisableClientState(GL_COLOR_ARRAY);
			glDisableClientState(GL_VERTEX_ARRAY);
		}

		else draw_ModoAjedrez();
	}

	else if(modoVisualizacion==ILUMINACION and sombreadoSel==FLAT){
		material.aplicar();
		if(nVertex.empty()) 
			calcular_normales();
		glShadeModel(GL_FLAT);
		glEnable(GL_NORMALIZE);

		glBegin(GL_TRIANGLES);

		for(int i = 0; i < nFaces.size(); i++){
			glNormal3fv(nFaces[i]);

			glVertex3fv(v[f[i](X)]);
			glVertex3fv(v[f[i](Y)]);
			glVertex3fv(v[f[i](Z)]);
		}

		glEnd();
	}

	else if(modoVisualizacion==ILUMINACION and sombreadoSel==SMOOTH){
		cout << "Entra en la condicion ILUMINACION Y FLAT\n ";
		material.aplicar();
		cout << "Maria no es real\n";
		if(nVertex.empty()) {
			calcular_normales();
			cout << "Normales calculadas\n";
		
		}
		glShadeModel(GL_FLAT);
		glEnable(GL_NORMALIZE);

		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, v.data());
		glNormalPointer(GL_FLOAT, 0, nVertex.data());
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, f.data());
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}


	
	
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

void Malla3D::draw_ModoDiferido(visualizacion modoVisualizacion, tipoSombreado sombreadoSel, variacionAngulo anguloSel, incDecAngulo variacionSelec)
{
  if(identificadorVBOv == 0)
    identificadorVBOv = CrearVBO(GL_ARRAY_BUFFER, 3*v.size()*sizeof(float), v.data());
  if(identificadorVBOf == 0)
    identificadorVBOf = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, 3*f.size()*sizeof(unsigned), f.data());
  if(identificadorVBOc == 0)
    identificadorVBOc = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, 3*deferredColor.size()*sizeof(unsigned), deferredColor.data());
   
   if(modoVisualizacion != ILUMINACION){
   		glShadeModel(GL_FLAT);
		glEnable(GL_CULL_FACE);
		if(modoVisualizacion!= CHESSMODE){
			glBindBuffer(GL_ARRAY_BUFFER, identificadorVBOv);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glEnableClientState(GL_VERTEX_ARRAY);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, identificadorVBOf);

			glBindBuffer(GL_ARRAY_BUFFER, identificadorVBOc);
			glColorPointer(3, GL_FLOAT, 0, 0);	
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glEnableClientState(GL_COLOR_ARRAY);

			if(modoVisualizacion==SOLIDO){
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			else if(modoVisualizacion==PUNTOS){
				glDisable(GL_CULL_FACE);
				glPointSize(2.0);
				glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			}
			else if(modoVisualizacion==LINEAS){
				glPolygonMode(GL_FRONT, GL_LINE);
			}

			glDrawElements(GL_TRIANGLES, 3*f.size(),GL_UNSIGNED_INT, 0);
			glDisableClientState(GL_COLOR_ARRAY);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glDisableClientState(GL_VERTEX_ARRAY);
		}

		else draw_ModoAjedrez();
	}
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

void Malla3D::draw(dibujado modoDibujado, visualizacion modoVisualizacion, tipoSombreado sombreadoSel, 
            variacionAngulo anguloSel, incDecAngulo variacionSelec)
{
	if(modoDibujado== INMEDIATO){
		draw_ModoInmediato(modoVisualizacion, sombreadoSel, anguloSel, variacionSelec);
	}
	else if(modoDibujado==DIFERIDO){
		draw_ModoDiferido(modoVisualizacion, sombreadoSel, anguloSel, variacionSelec);
	}
	
}

//-----------------------------------------------------------------------------
// Función de calcular normales
void Malla3D::calcular_normales()
{

	Tupla3f vAux1, vAux2, vAux3;
	Tupla3f vOp1, vOp2, vPerp, vNorm;
	vector<int> auxiliar;

	for(unsigned int i = 0; i < v.size(); i++){
		nVertex.push_back({0.0, 0.0, 0.0});
		auxiliar.push_back(0.0);
	}

	for(unsigned int i = 0; i < f.size(); i++){
		vAux1 = v[f[i](X)];
		vAux2 = v[f[i](Y)];
		vAux3 = v[f[i](Z)];

		vOp1 = vAux2 - vAux1;
		vOp2 = vAux3 - vAux1;

		vPerp = vOp1.cross(vOp2);
		cout << "Va a calcular las normales\n";
		vNorm = vPerp.normalized();
		nFaces.push_back(vNorm);

		nVertex[f[i](X)] = nVertex[f[i](X)] + nFaces[i];
		auxiliar[f[i](X)]++;
		nVertex[f[i](Y)] = nVertex[f[i](Y)] + nFaces[i];
		auxiliar[f[i](Y)]++;
		nVertex[f[i](Z)] = nVertex[f[i](Z)] + nFaces[i];
		auxiliar[f[i](Z)]++;
	}

	for(unsigned int i = 0; i < nVertex.size(); i++){
		nVertex[i] = nVertex[i] / auxiliar[i];
		nVertex[i].normalized();
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

