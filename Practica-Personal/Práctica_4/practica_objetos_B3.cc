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

bool firstTrace=false;
bool secondTrace=false;
bool thirdTrace=false;
int iter1=0;
int iter2=0;
int iter3=0;

bool activarAnimacion=false;


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

// _objeto_ply *ply1;

 float alfa=0.0;
 float beta=0.0;


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



void luces(float alfa, float beta){
    GLfloat luz_ambiente [ ] = {0.3,0.3,0.3,1.0};
    //GLfloat luz1 [ ] = {1.0,1.0,1.0,1.0};
    GLfloat luz1 [ ] = {0.4,0.6,0.2,0.0};
    //GLfloat luz2 [ ] = {0.2,1.0,0.5,1.0};
    GLfloat posicion1 [ ] = {50.0,50.0,0.0,1.0};
    GLfloat posicion2 [ ] = {-50.0,50.0,0.0,1.0};

    glLightfv (GL_LIGHT0, GL_AMBIENT, luz_ambiente);
    glLightfv (GL_LIGHT1, GL_DIFFUSE, luz1);
    glLightfv (GL_LIGHT1, GL_SPECULAR, luz1);

    glPushMatrix();
    glRotatef(alfa,0,1,0);
    glTranslatef(beta,0,0);
    glLightfv (GL_LIGHT1, GL_POSITION, posicion1);
    glPopMatrix();
   

    //glLightfv (GL_LIGHT2, GL_DIFFUSE, luz2);
    //glLightfv (GL_LIGHT2, GL_SPECULAR, luz2);
    //glLightfv (GL_LIGHT2, GL_POSITION, posicion2);

    glEnable(GL_LIGHT1);
    //glEnable(GL_LIGHT2);



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

clean_window();
change_observer();
luces(alfa,beta);
draw_axis();
draw_objects();
glutSwapBuffers();
}



//**************************************************************************
//Función Animación
//***************************************************************************
void animacion(){

    if(activarAnimacion){
        if(!firstTrace){
            robot.giro_cabeza++;
            robot.giro_pie_izquierdo++;
            robot.giro_pie_derecho--;
            robot.giro_mano_derecha++;
            robot.giro_mano_izquierda--;
            iter1++;
  
            if(iter1==25){
                firstTrace=true;
            }
        }
        
        

        if(firstTrace and !secondTrace){
            robot.giro_cabeza--;
            robot.giro_pie_izquierdo--;
            robot.giro_pie_derecho++;
            robot.giro_mano_derecha--;
            robot.giro_mano_izquierda++;
            iter2++;

            if(iter2<50) secondTrace=false;
            else{
             secondTrace=true;
            }

        }

        if(firstTrace and secondTrace and !thirdTrace){
            robot.giro_cabeza++;
            robot.giro_pie_izquierdo++;
            robot.giro_pie_derecho--;
            robot.giro_mano_derecha++;
            robot.giro_mano_izquierda--;
            iter3++;

            if(iter3<25) thirdTrace=false;
            else{
             firstTrace=false;
             secondTrace=false;
             iter1=0;
             iter2=0;
             iter3=0;
            }
        }
    }
    glutPostRedisplay();   
}





//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
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

    //Modo Dibujado
	case '1':modo=POINTS;break;
	case '2':modo=EDGES;break;
	case '3':modo=SOLID;break;
	case '4':modo=SOLID_CHESS;break;
    case '5':modo=SOLID_ILUMINATED_FLAT;break;
    case '6':modo=SOLID_ILUMINATED_GOURAUD;break;
    case '7':opcion=COLORPICKER;break;

    //Objetos
    case 'A':t_objeto=ARTICULADO;break;
    case 'S':t_objeto=PIRAMIDE;break;
    case 'D':t_objeto=CUBO;break;
    case 'F':t_objeto=OBJETO_PLY;break;	
    case 'G':t_objeto=GENERICO;break;
    case 'H':t_objeto=CILINDRO;break;
    case 'J':t_objeto=ESFERA;break;
    case 'K':t_objeto=CONO;break;

    //Movimientos
    case 'W': robot.giro_cabeza += v_giro_cabeza; break;
    case 'E': robot.giro_cabeza -= v_giro_cabeza; break;
    case 'R': robot.giro_mano_izquierda += v_giro_brazos; break;
    case 'T': robot.giro_mano_izquierda -= v_giro_brazos; break;
    case 'Y': robot.giro_mano_derecha += v_giro_brazos; break;
    case 'U': robot.giro_mano_derecha -= v_giro_brazos; break;
    case 'I': robot.giro_pie_derecho -= v_giro_piernas; break;
    case 'O': robot.giro_pie_derecho += v_giro_piernas; break;
    case 'Z': robot.giro_pie_izquierdo -= v_giro_piernas; break;
    case 'X': robot.giro_pie_izquierdo += v_giro_piernas; break; 
  
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
    case GLUT_KEY_F1:activarAnimacion=true;break;
    case GLUT_KEY_F2:activarAnimacion=false;break;
        case GLUT_KEY_F5:alfa+=5;break;
        case GLUT_KEY_F6:alfa-=5;break;
        case GLUT_KEY_F7:beta+=5;break;
        case GLUT_KEY_F8:beta-=5;break;

	}
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

glutIdleFunc(animacion);

// funcion de inicialización
initialize();

// creación del objeto ply
ply.parametros(argv[1]);

//ply1 = new _objeto_ply(argv[1]);

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
