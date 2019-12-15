

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    Front_plane       = 50;
    Back_plane        = 2000.0;
    Observer_distance = 4*Front_plane;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;

    ejes.changeAxisSize( 5000 );

    // crear los objetos de la escena....
    Material m({0.0215,0.1745,0.0215,1.0},{0.07568,0.61424,0.07568,1.0},{0.633,0.727811,0.633,1.0},76.8);
    directionalLight = new LuzDireccional({100.0, 100.0}, GL_LIGHT1, {0.0,0.0,0.0,1.0},{1.0,1.0,1.0,1.0}, {1.0,1.0,1.0,1.0});
    cubo = new Cubo(); 
    cubo->setMaterial(m);
    tetraedro = new Tetraedro();  
    objply = new ObjPLY("plys/Deer.ply");
    cilindro = new Cilindro();
    cono = new Cono();
    esfera = new Esfera();
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
  glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer
  redimensionar(UI_window_width, UI_window_height);
}

// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::confParametrosDibujado(){
  using namespace std;

/*
  directionalLight->activar();
  glShadeModel(GL_SMOOTH);
  //Dibujar sin ningun parametro, directamente en pantalla
    //Ahora se van a dibujar objetos simultaneos
*/
  glPushMatrix();
  glTranslatef(50,50,50);
  if(cubo != nullptr)
    cubo->draw(modoDibujado, modoVisualizacion);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-50, -50, -50);
  if(tetraedro != nullptr)
    tetraedro->draw(modoDibujado, modoVisualizacion);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(50, -50, 50);
  if(cilindro != nullptr)
    cilindro->draw(modoDibujado, modoVisualizacion);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-50, 50 , 50);
  if(cono != nullptr)
    cono->draw(modoDibujado, modoVisualizacion);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-100, 50, 50);
  if(esfera != nullptr)
    esfera->draw(modoDibujado, modoVisualizacion);
  glPopMatrix();

  
  glPushMatrix();
  glRotatef(-90.0, 1.0, 0.0, 0.0);
  glScalef(0.2, 0.2, 0.2);
  if(objply != nullptr)
    objply->draw(modoDibujado, modoVisualizacion);
  glPopMatrix();



}

void Escena::dibujar()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
 // glEnable(GL_LIGHTING);
  ejes.draw();
  confParametrosDibujado();

  
    
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir=false;
   bool modoIluminacion=false;
   switch( toupper(tecla) )
   {
      case 'Q' :
         if (modoMenu!=NADA)
            modoMenu=NADA;            
         else {
            salir=true ;
         }
      break ;

      case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
        modoMenu=SELVISUALIZACION;
      break ;

      case 'D' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
        modoMenu=SELDIBUJADO;
      break ;
         // COMPLETAR con los diferentes opciones de teclado
   
      case 'P' :
        if(modoMenu==SELVISUALIZACION){
          modoVisualizacion=PUNTOS;
        }
      break;

      case 'L' :
        if(modoMenu==SELVISUALIZACION){
          modoVisualizacion=LINEAS;
        }
      break;

      case 'S' :
        if(modoMenu==SELVISUALIZACION){
          modoVisualizacion=SOLIDO;
        }
      break;

      case 'A' :
        if(modoMenu==SELVISUALIZACION){
          modoVisualizacion=CHESSMODE;
        }

        else if(modoMenu==SELVISUALIZACION and modoVisualizacion==ILUMINACION){
          variacionSeleccionada=VARALPHA;
        }
      break;

      case 'I' : 
        if(modoMenu==SELVISUALIZACION){
          modoVisualizacion=ILUMINACION; 
        }
      break;

      case '0' :
        if(modoMenu==SELVISUALIZACION and modoVisualizacion==ILUMINACION){
          luzSeleccionada = LIGHT0;
        }
      break;

      case '1' :
        if(modoMenu==SELVISUALIZACION and modoVisualizacion==ILUMINACION){
          luzSeleccionada = LIGHT1;
        }

        else if(modoMenu==SELDIBUJADO){
          modoDibujado=INMEDIATO;
        }
      break;

      case '2' :
        if(modoMenu==SELVISUALIZACION and modoVisualizacion==ILUMINACION){
          luzSeleccionada = LIGHT2;
        }
        else if(modoMenu==SELDIBUJADO){
          modoDibujado=DIFERIDO;
        }
      break;

      case '3' :
        if(modoMenu==SELVISUALIZACION and modoVisualizacion==ILUMINACION){
          luzSeleccionada = LIGHT3;
        }
      break;

      case '4' :
        if(modoMenu==SELVISUALIZACION and modoVisualizacion==ILUMINACION){
          luzSeleccionada = LIGHT4;
        }
      break;

      case '5' :
        if(modoMenu==SELVISUALIZACION and modoVisualizacion==ILUMINACION){
          luzSeleccionada = LIGHT5;
        }
      break;

      case '6' :
        if(modoMenu==SELVISUALIZACION and modoVisualizacion==ILUMINACION){
          luzSeleccionada = LIGHT6;
        }
      break;

      case '7' :
        if(modoMenu==SELVISUALIZACION and modoVisualizacion==ILUMINACION){
          luzSeleccionada = LIGHT7;
        }
      break;

      case 'B' :
        if(modoMenu==SELVISUALIZACION and modoVisualizacion==ILUMINACION){
          variacionSeleccionada=VARALPHA;
        }
      break;

      case '>' :
        if(modoMenu==SELVISUALIZACION and modoVisualizacion==ILUMINACION){
          accionAngulo=INCREMENTO;
        }
      break;

      case '<' :
        if(modoMenu==SELVISUALIZACION and modoVisualizacion==ILUMINACION){
          accionAngulo=DECREMENTO;
        }
      break;
   }
   return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
	}
//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wx = float(Height)*ratio_xy ;
   glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
}
