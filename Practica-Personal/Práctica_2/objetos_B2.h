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
typedef enum{CUBO, PIRAMIDE, OBJETO_PLY, ESFERA, CONO, CILINDRO, GENERICO} _tipo_objeto;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
	_puntos3D();
void 	draw_puntos(int grosor);
void 	colorPicker();

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
void 	draw_aristas(int grosor);
void    draw_solido();
void 	draw_solido_ajedrez();
void 	draw(_modo modo, float grosor, _opcion &x);

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
void  parametros(vector<_vertex3f> perfil1, int num1, _tipo_objeto tipo);

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

	_piramide(float tam=0.85, float al=1.3);
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



