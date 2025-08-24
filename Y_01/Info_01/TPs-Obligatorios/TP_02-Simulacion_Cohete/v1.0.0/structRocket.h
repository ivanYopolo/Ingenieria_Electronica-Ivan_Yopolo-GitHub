
struct Rocket{
	int Attempt;	// Intentos [0; 3].
	int Current; 	// Cohete actual.
	int Mass;		// Masa del cohete [kg].
	char Success; 	// Fue exitoso? 1: SÍ; 0: NO.
	
	// ### Tamaño Array = N° Intentos (3 MAX) ###
	float RandForce[3];	// Fuerza aleatoria [N].
	float RandAngle[3];	// Ángulo aleatorio [DEG].
	float RandAngleRAD[3];// Ángulo aleatorio [RAD].
	float Velocity[3];	// Velocidad calculada [m/s].
	float Height[3];		// Altura calculada [m].
	float eC[3];		// Energía Cinética [J].
	float eP[3];		// Energía Potencial [J].
	char PerfMes[3][12];// Mensaje del rendimiento o performance (1/intento).
	
	float CosAngle;	// Coseno del ángulo [RAD].
	float SinAngle;	// Seno del ángulo [RAD].
};