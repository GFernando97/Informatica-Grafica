#include "aux.h"
#include "esfera.h"

Esfera::Esfera(const int num_vert_perfil, const int num_instancias_perf, const float radio)
{
	std::vector<Tupla3f> perfil_original;
	Tupla3f aux;

	float incremento = 180.0/(float)(num_vert_perfil-1);

	for(float i=-90.0 +incremento; i<= 90.0; i+=incremento){
		aux(X) = cos(i*M_PI/180)*radio;
		aux(Y) = sin(i*M_PI/180)*radio;
		aux(Z) = 0.0;

		perfil_original.push_back(aux);
	}
		perfil_original.push_back({0.0, radio, 0.0});


	crearMalla(perfil_original, num_instancias_perf, true, true);

	immediateColorPicker();
	deferredColorPicker();
	chessColorPicker();


}

