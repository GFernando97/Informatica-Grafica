#include "cilindro.h"


Cilindro::Cilindro(const int  num_vert_perfil, const int num_instancias_perf, const float altura, const float radio)
{
	float incremento = (float)(2*radio)/(num_vert_perfil);
	Tupla3f vertex;
	std::vector<Tupla3f> perfil_original;
	
	//Primera implementacion de cilindro.
	//Los triangulos se ven como cada forma de vertices
	/*for(float i = 0; i<=num_vert_perfil; i ++){
		vertex(X) = radio;
		vertex(Y) = incremento * i;
		vertex(Z) = 0.0;
		perfil_original.push_back(vertex);
	}*/

	//Segunda implementacion de cilindro
	//Esta vez solo se reconoce una cara en la superficie solida
	perfil_original.push_back({0.0, 0.0, 0.0});
	perfil_original.push_back({-radio, 0.0, 0.0});
	perfil_original.push_back({-radio, altura, 0.0});
	perfil_original.push_back({0.0, altura, 0.0});

	crearMalla(perfil_original, num_instancias_perf, true, true);

	/*for(int i = 0; i < v.size(); i++){
		c.push_back({0.53, 0.53, 0.53});
	}*/


}

