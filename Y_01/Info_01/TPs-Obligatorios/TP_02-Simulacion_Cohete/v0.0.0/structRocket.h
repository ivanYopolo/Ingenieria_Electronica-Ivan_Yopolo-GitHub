typedef char bool;

struct Rocket{
	int Attempt;	// Intentos [0; 3].
	int Current; 	// Cohete actual.
	int Mass;		// Masa del cohete [kg].
	bool Success; 	// Fue exitoso? 1: SÍ; 0: NO.
	
	// ### Tamaño Array = N° Intentos (3 MAX) ###
	int RandForce[3];	// Fuerza aleatoria [N].
	int RandAngle[3];	// Ángulo aleatorio [DEG].
	int Velocity[3];	// Velocidad calculada [m/s].
	int Height[3];		// Altura calculada [m].
	float eC[3];		// Energía Cinética [J].
	float eP[3];		// Energía Potencial [J].
	char PerfMes[3][12];// Mensaje del rendimiento o performance (1/intento).
	
	float CosAngleDeg;	// Coseno del ángulo [DEG].
	float SinAngleDeg;	// Seno del ángulo [DEG].
};