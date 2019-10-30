#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{


   // inicializar la tabla de vértices
	v.resize(8);
	v = {{-lado, -lado, lado},
		 {lado, -lado, lado},
		 {lado, -lado, -lado},
		 {-lado, -lado, -lado},
		 {-lado, lado, lado},
		 {lado, lado, lado},
		 {lado, lado, -lado},
		 {-lado, lado, -lado}};
   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
    f.resize(12);
    f = {{ 0, 1, 3 }, { 1, 2, 3 },
    	 { 0, 1, 5 }, { 0, 4, 5 },
    	 { 1, 2, 6 }, { 1, 5, 6 },
    	 { 0, 3, 4 }, { 3, 4, 7 },
    	 { 2, 3, 7 }, { 2, 6, 7 },
    	 { 4, 5, 6 }, { 4, 6, 7 }};

          
}

