#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "esfera.h"
#include "cono.h"
#include "cilindro.h"
#include "objrevolucion.h"
#include "objply.h"
#include "luzdireccional.h"
#include "material.h"
//#include "luzposicional.h"
#include "luz.h"


class Escena
{

   private:

   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;

   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();
  void clear_window();

  tipoSombreado sombreadoSeleccionado=FLAT;
  incDecAngulo accionAngulo;
  variacionAngulo variacionSeleccionada;
  idLuz luzSeleccionada;
  menu modoMenu=NADA;
  visualizacion modoVisualizacion=SOLIDO;
  objeto objetoSeleccionado=CUBO;
  dibujado modoDibujado=INMEDIATO;

   // Objetos de la escena
  LuzDireccional * directionalLight = nullptr;
  Ejes ejes;
  Cubo * cubo = nullptr ; 
  Tetraedro * tetraedro= nullptr ; 
  ObjRevolucion * objRev = nullptr;
  ObjPLY * objply = nullptr;
  Cilindro * cilindro = nullptr;
  Cono * cono = nullptr;
  Esfera * esfera = nullptr;

   
   public:

  Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
  void confParametrosDibujado();
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

};
#endif
