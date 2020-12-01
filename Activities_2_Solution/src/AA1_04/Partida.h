#pragma once
#include "Pieza.h"
#include "Tablero.h"
#include "Movimiento.h"

const int K_MAX_PIEZAS = 32;
const int K_MAX_MOVS = 99;

class Partida {
	Pieza * piezas[K_MAX_PIEZAS];
	Tablero * tablero;
	std::vector<Movimiento *> movimientos; //Falta max: K_MAX_MOVS
};