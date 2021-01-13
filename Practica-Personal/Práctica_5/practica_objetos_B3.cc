//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos_B3.h"


using namespace std;

//Variables Teclado
_opcion opcion=NO_OPTION;
_tipo_objeto t_objeto=CUBO;
_modo   modo=POINTS;
// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x,Size_y,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x=50,Window_y=50,Window_width=450,Window_high=450;

// variables que determinan la velocidad de las modificaciónes del modelo jerárquico
int v_giro_cabeza = 5;
int v_giro_brazos = 5;
int v_giro_piernas = 5;

// objetos
_cubo cubo;
_piramide piramide;
_objeto_ply  ply; 
_rotacion rotacion; 
_esfera esfera;
_cilindro cilindro;
_cono cono;
_copa copa;
_robot robot;

int estadoRaton[3], xc, yc;

void pick_color(int x, int y);



//**************************************************************************
//
//***************************************************************************

void clean_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero, plano_traser)
//  plano_delantero>0  plano_trasero>PlanoDelantero)
glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
	
glDisable(GL_LIGHTING);
glLineWidth(2);
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//****************************2***********************************************

void draw_objects()
{

switch (t_objeto){
	case CUBO: cubo.draw(modo,2,opcion);break;
	case PIRAMIDE: piramide.draw(modo,2,opcion);break;
        case OBJETO_PLY: ply.draw(modo,2,opcion);break;
        case ESFERA: esfera.draw(modo,2,opcion);break;
        case CONO: cono.draw(modo,2,opcion);break;
        case CILINDRO: cilindro.draw(modo,2,opcion);break;
        case GENERICO: copa.draw(modo,2,opcion);break;
        case ARTICULADO: robot.draw(modo,2,opcion);break;
	}
	opcion=NO_OPTION;


}


//**************************************************************************
//
//***************************************************************************

void draw(void)
{

glDrawBuffer(GL_FRONT);
clean_window();
change_observer();
draw_axis();
draw_objects();

if(t_objeto==ARTICULADO){
    glDrawBuffer(GL_BACK);
    clean_window();
    change_observer();
    robot.seleccion(100);
}

glFlush();
}



//***************************************************************************
// Funcion llamada cuando se produce un robot.cambiar[] en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
float Aspect_ratio;

Aspect_ratio=(float) Alto1/(float )Ancho1;
Size_y=Size_x*Aspect_ratio;
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


//**********-o*****************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_key(unsigned char Tecla1,int x,int y)
{
switch (toupper(Tecla1)){
	case 'Q':exit(0);
	case '1':modo=POINTS;break;
	case '2':modo=EDGES;break;
	case '3':modo=SOLID;break;
	case '4':modo=SOLID_CHESS;break;
    case 'P':t_objeto=PIRAMIDE;break;
    case 'C':t_objeto=CUBO;break;
    case 'O':t_objeto=OBJETO_PLY;break;	
    case 'A':t_objeto=ESFERA;break;
    case 'S':t_objeto=CILINDRO;break;
    case 'D':t_objeto=CONO;break;
    case 'X':opcion=COLORPICKER;break;
    case 'G':t_objeto=GENERICO;break;
    case 'T':t_objeto=ARTICULADO;break;

    //Movimientos
    case 'W': robot.giro_cabeza += v_giro_cabeza; break;
    case 'E': robot.giro_cabeza -= v_giro_cabeza; break;
    case 'H': robot.giro_mano_izquierda += v_giro_brazos; break;
    case 'J': robot.giro_mano_izquierda -= v_giro_brazos; break;
    case 'K': robot.giro_mano_derecha += v_giro_brazos; break;
    case 'L': robot.giro_mano_derecha -= v_giro_brazos; break;
    case 'V': robot.giro_pie_derecho -= v_giro_piernas; break;
    case 'B': robot.giro_pie_derecho += v_giro_piernas; break;
    case 'N': robot.giro_pie_izquierdo -= v_giro_piernas; break;
    case 'M': robot.giro_pie_izquierdo += v_giro_piernas; break; 
  
	}
glutPostRedisplay();
}

//***************************************************************************
// Funcion l-olamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_key(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
    
	}
glutPostRedisplay();
}



//***************************************************************************
// Funciones para manejo de eventos del ratón
//***************************************************************************

void clickRaton( int boton, int estado, int x, int y )
{
if(boton== GLUT_RIGHT_BUTTON) {
   if( estado == GLUT_DOWN) {
      estadoRaton[2] = 1;
      xc=x;
      yc=y;
     } 
   else estadoRaton[2] = 1;
   }
if(boton== GLUT_LEFT_BUTTON) {
  if( estado == GLUT_DOWN) {
      estadoRaton[2] = 2;
      xc=x;
      yc=y;
      pick_color(xc, yc);
    } 
  }
}

/*************************************************************************/

void getCamara (GLfloat *x, GLfloat *y)
{
*x=Observer_angle_x;
*y=Observer_angle_y;
}

/*************************************************************************/

void setCamara (GLfloat x, GLfloat y)
{
Observer_angle_x=x;
Observer_angle_y=y;
}



/*************************************************************************/

void RatonMovido( int x, int y )
{ 
float x0, y0, xn, yn; 
if(estadoRaton[2]==1) 
    {getCamara(&x0,&y0);
     yn=y0+(y-yc);
     xn=x0-(x-xc);
     setCamara(xn,yn);
     xc=x;
     yc=y;
     glutPostRedisplay();
    }
}



void procesar_color(unsigned char color[3])
{

 
 switch (color[0])
      {case 100: 
                 if (robot.activo[0]==0) 
                      {robot.activo[0]=1;
                       robot.cambiar[0]=1;
                      }
                  else 
                      {robot.activo[0]=0;
                       robot.cambiar[0]=0;
                      }
                  break; 
        case 120:
                  if (robot.activo[1]==0) 
                       {robot.activo[1]=1;
                        robot.cambiar[1]=1;
                       }
                  else 
                       {robot.activo[1]=0;
                        robot.cambiar[1]=0;
                       } 
                  break;
        case 140: 
                  if (robot.activo[2]==0) 
                       {robot.activo[2]=1;
                        robot.cambiar[2]=1;
                       }
                  else 
                       {robot.activo[2]=0;
                        robot.cambiar[2]=0;
                       }
                  break; 
        case 160: 
                  if (robot.activo[3]==0) 
                       {robot.activo[3]=1;
                        robot.cambiar[3]=1;
                       }
                  else 
                       {robot.activo[3]=0;
                        robot.cambiar[3]=0;
                       }
                  break;
        case 180: 
                  if (robot.activo[4]==0) 
                       {robot.activo[4]=1;
                        robot.cambiar[4]=1;
                       }
                  else 
                       {robot.activo[4]=0;
                        robot.cambiar[4]=0;
                       }
                  break;
                 

        case 200: 
                  if (robot.activo[5]==0) 
                       {robot.activo[5]=1;
                        robot.cambiar[5]=1;
                       }
                  else 
                       {robot.activo[5]=0;
                        robot.cambiar[5]=0;
                       }
                  break;
    }         
                           
 }



void pick_color(int x, int y)
{
GLint viewport[4];
unsigned char pixel[3];

glGetIntegerv(GL_VIEWPORT, viewport);
glReadBuffer(GL_BACK);
glReadPixels(x,viewport[3]-y,1,1,GL_RGB,GL_UNSIGNED_BYTE,(GLubyte *) &pixel[0]);
printf(" valor x %d, valor y %d, color %d, %d, %d \n",x,y,pixel[0],pixel[1],pixel[2]);

procesar_color(pixel);
glutPostRedisplay();
}


//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{

// se inicalizan la ventana y los planos de corte
Size_x=0.5;
Size_y=0.5;
Front_plane=1;
Back_plane=1000;

// se incia la posicion del observador, en el eje z
Observer_distance=4*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cua*ply1l sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
change_projection();
glViewport(0,0,Window_width,Window_high);



}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************


int main(int argc, char *argv[] )
{
 



// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido_rotation Rotation;
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(Window_x,Window_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(Window_width,Window_high);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("PRACTICA - 2: Fernando Lojano");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw);
// asignación de la funcion llamada "change_window_size" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "normal_key" al evento correspondiente
glutKeyboardFunc(normal_key);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_key);


// eventos ratón
    glutMouseFunc( clickRaton );
    glutMotionFunc( RatonMovido );

// funcion de inicialización
initialize();

// creación del objeto ply
ply.parametros(argv[1]);

//ply1 = new _objeto_ply(argv[1]);

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
