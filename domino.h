#ifndef DOMINO_H
#define DOMINO_H

const int MAX_FITXES = 7;
const int MAX_JUGADORS = 4;


typedef struct
{
	int valor1;
	int valor2;
} Fitxa;

typedef struct
{
	Fitxa fitxes[MAX_FITXES];
	int nFitxes;
	bool haPogutTirar;
} Jugador;

typedef struct
{
	Jugador jugadors[MAX_JUGADORS];
	int jugadorActual;
	int valorEsq;
	int valorDret;
	int nTornsPassant;
} Partida;

int jugaDomino(Fitxa fitxesInicials[MAX_FITXES * MAX_JUGADORS], Fitxa fitxesJugades[MAX_FITXES * MAX_JUGADORS * 2], int& nFitxesJugades);


#endif

