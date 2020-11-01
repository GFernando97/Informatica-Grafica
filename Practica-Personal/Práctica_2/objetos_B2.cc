//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B2.h"
#include "file_ply_stl.hpp"


//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(int grosor){
  unsigned int i;
  glPointSize(grosor);
  glColor3f(color1._0, color1._1, color1._2);
  glBegin(GL_POINTS);
  for (i=0;i<vertices.size();i++){
  	glVertex3fv((GLfloat *) &vertices[i]);
  	}
  glEnd();
}


//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(int grosor){
  unsigned int i;
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  glLineWidth(grosor);
  glColor3f(color1._0, color1._1, color1._2);
  glBegin(GL_TRIANGLES);
  for (i=0;i<caras.size();i++){
  	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
  	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
  	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
  	}
  glEnd();
}

//*************************************************************************
// dibujar en modo sólido
//*************************************************************************

void _triangulos3D::draw_solido(){
  unsigned int i;
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glLineWidth(0.7);
  glColor3f(color1._0, color1._1, color1._2);
  glBegin(GL_TRIANGLES);
  for (i=0;i<caras.size();i++){
    glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
    }
  glEnd();
}

//*************************************************************************
// dibujar en modo sólido con apariencia de ajedrez
//*************************************************************************

void _triangulos3D::draw_solido_ajedrez(){
  unsigned int i;
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glLineWidth(0.7);
  glBegin(GL_TRIANGLES);


  for (i=0;i<caras.size();i++)
  {
  if ( i %2 == 0 ){
    glColor3f(color1._0, color1._1, color1._2);
    glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
  }
  else {
    glColor3f(color2._0, color2._1, color2._2);
    glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._2]);

  }


  }
  glEnd();
}

//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float grosor, _opcion &x){
  if(x==COLORPICKER){
  colorPicker();
  x=NO_OPTION;
}
  switch (modo){
  	case POINTS:draw_puntos(grosor);break;
  	case EDGES:draw_aristas(grosor);break;
  	case SOLID_CHESS:draw_solido_ajedrez();break;
  	case SOLID:draw_solido();break;
  }
}


//*************************************************************************
// Cambiar color caras
//*************************************************************************

void _puntos3D::colorPicker(){
  vector<float>valoresGenerados;
  valoresGenerados.resize(6);
  srand((unsigned) time(0));

  for(unsigned int i = 0; i < (unsigned int)valoresGenerados.size(); i++){
    int valor = (rand()%255);
    double transformada = 1.0/255.0*valor;
    valoresGenerados[i] = transformada;
  }

  color1._0=valoresGenerados[0]; 
  color1._1=valoresGenerados[1]; 
  color1._2=valoresGenerados[2];
  color2._0=valoresGenerados[3]; 
  color2._1=valoresGenerados[4]; 
  color2._2=valoresGenerados[5]; 
}


//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam){
  //vertices
  vertices.resize(8);
  vertices[0].x= 0; vertices[0].y = 0; vertices[0].z=tam;
  vertices[1].x= tam; vertices[1].y = 0; vertices[1].z=tam;
  vertices[2].x= tam; vertices[2].y = 0; vertices[2].z=0;
  vertices[3].x= 0; vertices[3].y = 0; vertices[3].z=0;
  vertices[4].x= 0; vertices[4].y= tam; vertices[4].z= tam;
  vertices[5].x= tam; vertices[5].y= tam; vertices[5].z=tam;
  vertices[6].x= tam; vertices[6].y=tam; vertices[6].z=0;
  vertices[7].x= 0; vertices[7].y= tam; vertices[7].z=0;

  // triangulos
  caras.resize(12);
  caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
  caras[1]._0=1;caras[1]._1=5;caras[1]._2=4;
  caras[2]._0=1;caras[2]._1=2;caras[2]._2=5;
  caras[3]._0=2;caras[3]._1=6;caras[3]._2=5;
  caras[4]._0=2;caras[4]._1=3;caras[4]._2=6;
  caras[5]._0=3;caras[5]._1=7;caras[5]._2=6;
  caras[6]._0=3;caras[6]._1=0;caras[6]._2=7;
  caras[7]._0=0;caras[7]._1=4;caras[7]._2=7;
  caras[8]._0=4;caras[8]._1=5;caras[8]._2=6;
  caras[9]._0=4;caras[9]._1=6;caras[9]._2=7;
  caras[10]._0=3;caras[10]._1=1;caras[10]._2=0;
  caras[11]._0=3;caras[11]._1=2;caras[11]._2=1;
}

//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al){

  //vertices 
  vertices.resize(5); 
  vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
  vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
  vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
  vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
  vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;

  //caras
  caras.resize(6);
  caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
  caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;
  caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
  caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
  caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
  caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;
}

//*************************************************************************
// clase esfera
//*************************************************************************

_esfera::_esfera(float radio, int n_vert, int n_inst){
  vector<_vertex3f> perfil;
  _vertex3f aux;

  for(unsigned int i = 1; i < (unsigned)n_vert;i++){
    aux.x=radio*cos(M_PI*i/n_vert-M_PI/2.0);
    aux.y=radio*sin(M_PI*i/n_vert-M_PI/2.0);
    aux.z=0.0;
    perfil.push_back(aux);
    }
    /* 
      float incremento = 180.0/(float)(n_vert-1);
      for(float i = -90.0+incremento ; i <=90.0; i+=incremento){
        aux.x = cos(i*M_PI/180)*radio;
        aux.y = sin(i*M_PI/180)*radio;
        aux.z = 0.0;
        perfil.push_back(aux);
      }

      perfil.push_back({0.0, radio, 0.0});
    */

  parametros(perfil, n_inst, ESFERA);
}

//*************************************************************************
// clase cilindro
//*************************************************************************

_cilindro::_cilindro(float radio, int n_rev, int altura){
  vector<_vertex3f> perfil;
  _vertex3f aux;

  aux.x = radio;
  aux.y = 0.0;
  aux.z = 0.0;
  perfil.push_back(aux);

  aux.x = radio;
  aux.y = altura;
  aux.z = 0.0;
  perfil.push_back(aux);

  parametros(perfil, n_rev, CILINDRO);
}

//*************************************************************************
// clase cono
//*************************************************************************

_cono::_cono(float radio, int n_rev, int altura){
  vector<_vertex3f> perfil;
  _vertex3f aux;

  aux.x = radio;
  aux.y = 0.0;
  aux.z = 0.0;
  perfil.push_back(aux);

  aux.x = 0.0;
  aux.y = altura;
  aux.z = 0.0;
  perfil.push_back(aux);

  parametros(perfil, n_rev, CONO);
}

//*************************************************************************
// clase objeto ply
//*************************************************************************

_objeto_ply::_objeto_ply() {
  // leer lista de coordenadas de vértices y lista de indices de vértices

  //Lista de Coordenadas
}


int _objeto_ply::parametros(char *archivo){
  int n_ver,n_car;
  vector<float> ver_ply ;
  vector<int>   car_ply ;
  
  _file_ply::read(archivo, ver_ply, car_ply );

  n_ver=ver_ply.size()/3;
  n_car=car_ply.size()/3;


  printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

  vertices.resize(n_ver);
  for(unsigned int i = 0; i <(unsigned int)n_ver; i++){
    vertices[i].x = ver_ply[i*3];
    vertices[i].y = ver_ply[i*3+1];
    vertices[i].z = ver_ply[i*3+2];
  }

  caras.resize(n_car);

  for(unsigned int i = 0; i <(unsigned int)n_car; i++){
    caras[i].x = car_ply[i*3];
    caras[i].y = car_ply[i*3+1];
    caras[i].z = car_ply[i*3+2];
  }

  return(0);
}


//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion(){

}


void _rotacion::parametros(vector<_vertex3f> perfil, int num, _tipo_objeto tipo){
  int i,j;
  _vertex3f vertice_aux;
  _vertex3i cara_aux;
  int num_aux;
  float radio = 0.0;

  if(tipo==ESFERA)
    radio= sqrt(perfil[0].x*perfil[0].x+perfil[0].y*perfil[0].y);
   
  // tratamiento de los vértices
  if(tipo==CONO) num_aux=1;
  else num_aux=perfil.size();


  vertices.resize(num_aux*num+2);   //el +2 son los dos vertices de las tapas
  for (j=0;j<num;j++)
    {for (i=0;i<num_aux;i++)
       {
        vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                      perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
        vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                      perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
        vertice_aux.y=perfil[i].y;
        vertices[i+j*num_aux]=vertice_aux;
       }
    }



  // tratamiento de las caras 
  //caras.resize((num_aux-1)*2*num+2*num);  //Habría que generalizar, este casp

  if(tipo != CONO){
    for(i=0; i<num;i++){
      for(j=0; j<num_aux-1;j++){
        cara_aux.x = j+((i+1)%num)*num_aux;
        cara_aux.y = j+1+((i+1)%num)*num_aux;
        cara_aux.z = j+1+i*num_aux;
        caras.push_back(cara_aux);

        cara_aux.x = j+1+i*num_aux;
        cara_aux.y = j+i*num_aux;
        cara_aux.z = j+((i+1)%num)*num_aux;
        caras.push_back(cara_aux);
      }
    }
  }


   // tapa inferior
  if (fabs(perfil[0].x)>0.0){

    vertices[num_aux*num].x = 0.0;
    vertices[num_aux*num].z = 0.0;
    switch(tipo){
      case CONO:     vertices[num_aux*num].y = 0.0;break;
      case ESFERA:   vertices[num_aux*num].y = -radio;break;
      default:       vertices[num_aux*num].y = perfil[0].y;break;
    }

    for(j=0; j < num;j++){
      cara_aux.x = num_aux*num;
      cara_aux.y = j*num_aux;
      cara_aux.z = ((j+1)%num)*num_aux;
      caras.push_back(cara_aux);
    }
  }

   // tapa superior
  if (fabs(perfil[num_aux-1].x)>0.0){

    vertices[num_aux*num+1].x = 0.0;
    vertices[num_aux*num+1].z = 0.0;
    switch(tipo){
      case CONO:     vertices[num_aux*num+1].y = perfil[1].y;break;
      case ESFERA:   vertices[num_aux*num+1].y = radio;break;
      default:       vertices[num_aux*num+1].y = perfil[num_aux-1].y;break;
    }

    for(j=0; j < num;j++){

      cara_aux.x = num_aux*num+1;
      cara_aux.y = num_aux*(j+1)-1;
      cara_aux.z = num_aux+((j+1)%num)*num_aux-1;
      caras.push_back(cara_aux);
    }
  }
}

