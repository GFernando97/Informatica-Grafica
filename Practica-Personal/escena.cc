

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
    cubo = new Cubo(); 
    tetraedro = new Tetraedro();  
    objply = new ObjPLY("plys/big_dodge.ply");
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

  int dibujadoSeleccionado=1;
  bool chessModeActivado = false;
  glPointSize(5.0);
  glShadeModel(GL_FLAT);

  switch(modoVisualizacion){
    case PUNTOS:
      glDisable(GL_CULL_FACE);
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    break;

    case LINEAS:  
      glDisable(GL_CULL_FACE);    
      glPolygonMode(GL_FRONT, GL_LINE);
    break;

    case SOLIDO:
      glPolygonMode(GL_FRONT, GL_FILL);
    break;

    case CHESSMODE:
      glPolygonMode(GL_FRONT, GL_FILL);
      chessModeActivado=true;
    break;

    default:
      cout << "modo: " << modoVisualizacion << endl;
    break;
  }

  switch (modoDibujado){
    case INMEDIATO:
      dibujadoSeleccionado=1;
    break;

    case DIFERIDO:
      dibujadoSeleccionado=0;
    break;
  }

  //Ahora se van a dibujar objetos simultaneos
  glPushMatrix();
  glTranslatef(50,50,50);
  if(cubo != nullptr)
    cubo->draw(, false);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-50, -50, -50);
  if(tetraedro != nullptr)
    tetraedro->draw(2, false);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(50, -50, 50);
  if(cilindro != nullptr)
    cilindro->draw(2, true);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-50, 50 , 50);
  if(cono != nullptr)
    cono->draw(2, true);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-100, 50, 50);
  if(esfera != nullptr)
    esfera->draw(2, true);
  glPopMatrix();

  glPushMatrix();
  glScalef(8.0, 8.0, 8.0);
  if(objply != nullptr)
    objply->draw(2, true);
  glPopMatrix();


}

void Escena::dibujar()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
  ejes.draw();
  glEnable(GL_CULL_FACE);

  confParametrosDibujado();



  //Dibujar sin ningun parametro, directamente en pantalla
  
    
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

      case 'O' :
         // ESTAMOS EN MODO SELECCION DE OBJETO
        modoMenu=SELOBJETO;

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
   
      case 'C' :
        if(modoMenu==SELOBJETO){
          objetoSeleccionado=CUBO;
        }
        else{
          cout << "mal momento para este boton.." << endl;
        }
      break;


      //SUBMENÚ SELECCION DE OBJETOS
      case 'T' :
        if(modoMenu==SELOBJETO){
          objetoSeleccionado=TETRAEDRO;
        }
        else{
          cout << "mal momento para este boton..." << endl;
        }
      break;

      case 'P' :
        if(modoMenu==SELVISUALIZACION){
          modoVisualizacion=PUNTOS;
        }
        else{
          cout << "mal momento para este boton..." << endl;
        }
      break;


      //SUBMENÚ SELECCION VISUALIZACION
      case 'L' :
        if(modoMenu==SELVISUALIZACION){
          modoVisualizacion=LINEAS;
        }
        else{
          cout << "mal momento para este boton..." << endl;
        }
      break;

      case 'S' :
        if(modoMenu==SELVISUALIZACION){
          modoVisualizacion=SOLIDO;
        }
        else{
          cout << "mal momento para este boton..." << endl;
        }
      break;

      case 'A' :
        if(modoMenu==SELVISUALIZACION){
          modoVisualizacion=CHESSMODE;
        }
        else{
          cout << "mal momento para este boton..." << endl;
        }
      break;

      case 'I' : 
        if(modoMenu==SELVISUALIZACION){
          modoVisualizacion=ILUMINACION; 
        }


      //SUBMENÚ SELECCION DIBUJADO

     /* case '0' :
          if(modoMenu==SELVISUALIZACION && modoVisualizacion==ILUMINACION){

        }
      break;*/

      case '1' :
        if(modoMenu==SELVISUALIZACION && modoVisualizacion==ILUMINACION){

        }
        if(modoMenu==SELDIBUJADO){
          modoDibujado=INMEDIATO;
        }
        else{
          cout << "mal momento para este boton..." << endl;
        }
      break;

      case '2' :
        if(modoMenu==SELDIBUJADO){
          modoDibujado=DIFERIDO;
        }
        else{
          cout << "mal momento para este boton..." << endl;
        }
      break;


      case '3' : 
        if(modoMenu==SELVISUALIZACION && modoVisualizacion==ILUMINACION){

        }
      break;

      case '4' : 
        if(modoMenu==SELVISUALIZACION && modoVisualizacion==ILUMINACION){

        }
      break;

      case '5' : 
        if(modoMenu==SELVISUALIZACION && modoVisualizacion==ILUMINACION){

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
