
class Cilindro : public ObjRevolucion
{
private:
	float altura;
	float radio;

public:
Cilindro(const int  num_vert_perfil=2, const int num_instancias_perf=20, const float altura=1.0, const float radio=1.0);
};