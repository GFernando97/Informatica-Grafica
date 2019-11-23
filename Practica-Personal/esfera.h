class Esfera : public ObjRevolucion
{
private:
	float radio;
public:
	Esfera (const int num_vert_perfil=10, const int num_instancias_perf=20, const float radio=1.0);
};