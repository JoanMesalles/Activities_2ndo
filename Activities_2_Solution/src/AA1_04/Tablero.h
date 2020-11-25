#pragma once
#include "Casilla.h"
#include "Coordenada.h"
#include <vector>

class Tablero {
	Casilla* casilla; //Esta es la casilla 1 obligatoria
	std::vector<Casilla *> casillas;
};