#include "aux.h"
#include "cono.h"

Cono::Cono(const int num_vert_perfil, const int num_instancias_perf, const float altura, const float radio)
{
	std::vector<Tupla3f> perfil_original;
	float incremento = radio/num_vert_perfil;
	float incrementoAlt = altura/num_vert_perfil;
	Tupla3f vAux;

	perfil_original.push_back({0.0,0.0,0.0});
	perfil_original.push_back({-radio,0.0,0.0});
	perfil_original.push_back({0.0, altura, 0.0});

	crearMalla(perfil_original, num_instancias_perf, false, true);

	immediateColorPicker();
	deferredColorPicker();
	chessColorPicker();
}
