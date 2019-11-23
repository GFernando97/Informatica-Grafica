#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{


   // inicializar la tabla de vértices
	v = {   {-lado, -lado, -lado},
          {-lado, -lado, +lado},
          {-lado, +lado, -lado}, 
          {-lado, +lado, +lado},
          {+lado, -lado, -lado},
          {+lado, -lado, +lado},
          {+lado, +lado, -lado},
          {+lado, +lado, +lado}};
   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
    f = { { 0, 2, 4 }, { 4, 2, 6 },
          { 1, 5, 3 }, { 3, 5, 7 },
          { 1, 3, 0 }, { 0, 3, 2 },
          { 5, 4, 7 }, { 7, 4, 6 },
          { 1, 0, 5 }, { 5, 0, 4 },
          { 3, 7, 2 }, { 2, 7, 6 }};

          
}

