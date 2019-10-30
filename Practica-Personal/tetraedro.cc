#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro()
{
	const float lado = 50;

   v.resize(4);
   v={{ -lado, -lado, -lado },
	  {  0,    -lado,  lado },
	  {  lado, -lado, -lado },
	  {  0,     lado,  0}};
   
   f.resize(4);
   f={{0, 1, 3}, {1, 2, 3},
	  {0, 2, 1}, {2, 0, 3}};	  
    

   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

}

