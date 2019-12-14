#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{


   // inicializar la tabla de vértices
	v = {   { lado,  lado,  lado},
          { lado,  lado, -lado},
          { lado, -lado,  lado}, 
          { lado, -lado, -lado},
          {-lado,  lado,  lado},
          {-lado,  lado, -lado},
          {-lado, -lado,  lado},
          {-lado, -lado, -lado}};
   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
    f = { { 4, 6, 2 }, { 2, 0, 4 },
          { 0, 2, 3 }, { 3, 1, 0 },
          { 1, 3, 7 }, { 7, 5, 1 },
          { 5, 7, 6 }, { 6, 4, 5 },
          { 5, 4, 0 }, { 0, 1, 5 },
          { 6, 7, 3 }, { 3, 2, 6 }};

  immediateColorPicker();
  deferredColorPicker();
  chessColorPicker();        
}

