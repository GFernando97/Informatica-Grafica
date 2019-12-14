// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"
#include "material.h"


// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class Malla3D
{
   public:

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato();

   // dibuja el objeto en modo diferido (usando VBOs)
   GLuint CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram);
   void draw_ModoDiferido();

   void draw_ModoAjedrez();

   void draw(int modoDibujado, bool chessMode) ;

   void setMaterial(Material mat){this->material=mat;}

   protected: 
   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)
   void immediateColorPicker(const float R= 0.142, const float G=0.227, const float B=0.239);
   void deferredColorPicker(const float R=0.195, const float G=0.060, const float B=0.084);
   void chessColorPicker( const Tupla3f Color1={0.060, 0.110,0.113}, const Tupla3f Color2={0.53, 0.53, 0.53});



   std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f ;   // una terna de 3 enteros por cada cara o triángulo


   //Vectores usados para guardar los valores de color de los modos inmediato, diferido y ajedrez;
   std::vector<Tupla3f> immediateColor;   
   std::vector<Tupla3f> deferredColor;
   std::vector<Tupla3f> oddColor;
   std::vector<Tupla3f> pairColor;

   //Vectores usados para guardar las normales
   std::vector<Tupla3f> nVertex;
   std::vector<Tupla3i> nFaces;

   GLuint identificadorVBOv = 0;
   GLuint identificadorVBOf = 0;
   GLuint identificadorVBOc = 0;

   Material material;


} ;


#endif
