#include <cmath>
#include "aux.h"
#include "malla.h"
#include "tetraedro.h"


Tetraedro::Tetraedro()
{
	const float lado = 30.0;

   v={  {-lado, -lado,  lado},  // 0
        { lado, -lado,  lado},  // 1
        { 0.0,   lado, 	0.0},  // 2
        { 0.0,  -lado, -lado}};
   
   f={  {0, 1, 2}, {2, 1, 3},
        {3, 0, 2}, {0, 3, 1}};	  
  

  immediateColorPicker();
  deferredColorPicker();
  chessColorPicker();
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
}

