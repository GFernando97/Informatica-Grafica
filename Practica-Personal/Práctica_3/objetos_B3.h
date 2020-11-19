//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include <random>


const float AXIS_SIZE=5000;
typedef enum{COLORPICKER, NO_OPTION} _opcion;
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID} _modo;
typedef enum{CUBO, PIRAMIDE, OBJETO_PLY, ESFERA, SEMIESFERA, CONO, CILINDRO, GENERICO, ARTICULADO} _tipo_objeto;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
  _puntos3D();
void  draw_puntos(int grosor);
void  colorPicker();

vector<_vertex3f> vertices;
_vertex3f color1{0.258,0.0,0.223};
_vertex3f color2{0.862,0.8,1.0};

};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

  _triangulos3D();
void  draw_aristas(int grosor);
void  draw_solido();
void  draw_solido_ajedrez();
void  draw(_modo modo, float grosor, _opcion &x);

vector<_vertex3i> caras;
};


//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();

int   parametros(char *archivo);
};

//************************************************************************
// objeto por revolución
//************************************************************************

class _rotacion: public _triangulos3D
{
public:
       _rotacion();
void  parametros(vector<_vertex3f> perfil1, int num1, _tipo_objeto tipo, bool tapa_inferior, bool tapa_superior);

vector<_vertex3f> perfil; 
int num;
};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

  _cubo(float tam=0.5);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

  _piramide(float tam=0.5, float al=0.75);
};


class _esfera: public _rotacion{

public:

_esfera(float radio=2.0, int n_vert=20, int n_inst=30);

};


class _cono: public _rotacion{

public:
  _cono(float radio=2.0, int n_rev=30, int altura=2);
};


class _cilindro: public _rotacion{
public:
  _cilindro(float radio=2.0, int n_rev=20, int altura=2);
};

class _copa: public _rotacion{
public: 
  _copa();
};

class _semiesfera: public _rotacion{
public:
  _semiesfera(float radio=2.0, int n_vert=20, int n_inst=30);
};




//************************************************************************
// objeto articulado: tanque
//************************************************************************

class _chasis: public _triangulos3D
{
public:
       _chasis();
void  draw(_modo modo, float grosor, _opcion &x);

float altura;

protected:
_rotacion  rodamiento;
_cubo  base;
};

//************************************************************************

class _torreta: public _triangulos3D
{
public:
       _torreta();
void  draw(_modo modo,  float grosor,  _opcion &x);

float altura;
float anchura;

protected:
_cubo  base;
_piramide parte_trasera;
};

//************************************************************************

class _tubo: public _triangulos3D
{
public:
       _tubo();
void  draw(_modo modo,  float grosor,  _opcion &x);

protected:
_rotacion tubo_abierto; // caña del cañón
};

//************************************************************************

class _tanque: public _triangulos3D
{
public:
       _tanque();
void  draw(_modo modo, float grosor,  _opcion &x);

float giro_tubo;
float giro_torreta;

float giro_tubo_min;
float giro_tubo_max;

protected:
_chasis  chasis;
_torreta  torreta;
_tubo     tubo;
};

/*
//************************************************************************
// objeto articulado: Robot
//************************************************************************
class _robot:public _triangulos3D{
public:
  _robot();
  void draw(_modo modo, float grosor, _opcion &x);

  float giro_cabeza;

  float giro_mano_izquierda;
  float giro_mano_derecha;

  float giro_pie_izquierdo;
  float giro_pie_derecho;

protected:
  _cabezaR cabeza;
  _torsoR torso;
  _brazoR brazoDerecho;
  _brazoR brazoIzquierdo;
  _piernaR piernaDerecha;
  _piernaR piernaIzquierda;
}

class _cabezaR: public _triangulos3D{
  public:
    _cabezaR();
    void draw(_modo modo, float grosor, _opcion &x);


}

*/
class _cabezaR:public _triangulos3D{
public:
  _cabezaR();
  void draw(_modo modo, float grosor, _opcion &x );

protected:
  _semiesfera cabeza;
  _esfera ojo_derecho;
  _esfera ojo_izquierdo;
  _cilindro oreja_izquierda;
  _cilindro oreja_derecha;

};

class _torsoR:public _triangulos3D{
public:
  _torsoR();
  void draw(_modo modo, float grosor, _opcion &x);
protected:
  _esfera torso;
};



/*
//************************************************************************
// objeto articulado: tanque
//************************************************************************

_chasis::_chasis()
{
// perfil para un cilindro
vector<_vertex3f> perfil;
_vertex3f aux;
aux.x=0.107;aux.y=-0.5;aux.z=0.0;
perfil.push_back(aux);
aux.x=0.107;aux.y=0.5;aux.z=0.0;
perfil.push_back(aux);
rodamiento.parametros(perfil,12, CILINDRO, true, true);
altura=0.22;
};

void _chasis::draw(_modo modo, float grosor,  _opcion &x)
{
glPushMatrix();
glScalef(1.0,0.22,0.95);
base.draw(modo, grosor, x);
glPopMatrix();

glPushMatrix();
glRotatef(90.0,1,0,0);
rodamiento.draw(modo,  grosor, x);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.25,0.0,0.0);
glRotatef(90.0,1,0,0);
rodamiento.draw(modo,  grosor, x);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.5,0.0,0.0);
glRotatef(90.0,1,0,0);
rodamiento.draw(modo,  grosor, x);
glPopMatrix();

glPushMatrix();
glTranslatef(0.25,0.0,0.0);
glRotatef(90.0,1,0,0);
rodamiento.draw(modo,  grosor, x);
glPopMatrix();

glPushMatrix();
glTranslatef(0.5,0.0,0.0);
glRotatef(90.0,1,0,0);
rodamiento.draw(modo,  grosor, x);
glPopMatrix();
}

//************************************************************************

_torreta::_torreta()
{
altura=0.18;
anchura=0.65;
};

void _torreta::draw(_modo modo, float grosor,  _opcion &x)
{
glPushMatrix();
glScalef(0.65,0.18,0.6);
base.draw(modo,  grosor, x);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.325,0,0);
glRotatef(90.0,0,0,1);
glScalef(0.18,0.16,0.6);
parte_trasera.draw(modo,  grosor, x);
glPopMatrix();
}

//************************************************************************

_tubo::_tubo()
{
// perfil para un cilindro
vector<_vertex3f> perfil;
_vertex3f aux;
aux.x=0.04;aux.y=-0.4;aux.z=0.0;
perfil.push_back(aux);
aux.x=0.04;aux.y=0.4;aux.z=0.0;
perfil.push_back(aux);
tubo_abierto.parametros(perfil,12,CILINDRO, false, false);
};

void _tubo::draw(_modo modo, float grosor, _opcion &x)
{

glPushMatrix();
glTranslatef(0.4,0,0);
glRotatef(90.0,0,0,1);
tubo_abierto.draw(modo,  grosor, x);
glPopMatrix();
}


//************************************************************************

_tanque::_tanque()
{
giro_tubo=2.0;
giro_torreta=0.0;
giro_tubo_min=-9;
giro_tubo_max=20;
};

void _tanque::draw(_modo modo, float grosor,  _opcion &x)
{
glPushMatrix();
chasis.draw(modo,  grosor, x);

glRotatef(giro_torreta,0,1,0);
glPushMatrix();
glTranslatef(0.0,(chasis.altura+torreta.altura)/2.0,0.0);
torreta.draw(modo,  grosor, x);
glPopMatrix();

glPushMatrix();
glTranslatef(torreta.anchura/2.0,(chasis.altura+torreta.altura)/2.0,0.0);
glRotatef(giro_tubo,0,0,1);
tubo.draw(modo,  grosor, x);
glPopMatrix();
glPopMatrix();

};
*/

