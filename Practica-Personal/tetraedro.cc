#include <cmath>
#include "aux.h"
#include "malla.h"
#include "tetraedro.h"


Tetraedro::Tetraedro()
{
	const float lado = 120.0;

   v={  {-lado/2.0, 0.0, -lado/(2.0 * sqrt(3.0))},  // 0
        { lado/2.0, 0.0, -lado/(2.0 * sqrt(3.0))},  // 1
        { 0.0, 0.0, lado/sqrt(3.0)},  // 2
        { 0.0, sqrt((2 * lado * lado)/3), 0.0}};
   
   f={  {3, 2, 1}, {3, 1, 0},
        {3, 0, 2}, {2, 1, 0}};	  
  
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
}

