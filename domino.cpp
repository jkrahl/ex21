#include "domino.h"


void quitarFichaDelJugador(Partida& partida, int index)
{
	for (int i = index; i < partida.jugadors[partida.jugadorActual].nFitxes - 1; i++)
	{
		partida.jugadors[partida.jugadorActual].fitxes[i] = partida.jugadors[partida.jugadorActual].fitxes[i + 1];
	}
	partida.jugadors[partida.jugadorActual].nFitxes--;
}

void inicializar(Partida& partida, Fitxa fitxesInicials[MAX_FITXES * MAX_JUGADORS])
{
	for (int i = 0; i < MAX_JUGADORS; i++)
	{
		partida.jugadors[i].nFitxes = MAX_FITXES;
		partida.jugadors[i].haPogutTirar = true;
	}
	for (int i = 0; i < MAX_FITXES * MAX_JUGADORS; i++)
	{
		for (int j = 0; j < MAX_FITXES; j++)
		{
			partida.jugadors[i].fitxes[j] = fitxesInicials[i * MAX_FITXES + j];
		
		}
	}
	partida.jugadorActual = 0;
	partida.nTornsPassant = 0;
	partida.valorDret = -1;
	partida.valorEsq = -1;

	partida.valorEsq = partida.jugadors[0].fitxes[0].valor1;
	partida.valorDret = partida.jugadors[0].fitxes[0].valor2;
	quitarFichaDelJugador(partida, 0);

	partida.jugadorActual = 1;
}

void seleccionaFitxa(Partida& partida, Fitxa& fitxa, int& index)
{
	index = 0;
	bool trobat = false;
	fitxa.valor1 = -1;
	fitxa.valor2 = -1;
	while (!trobat && index < MAX_FITXES)
	{
		if (partida.jugadors[partida.jugadorActual].fitxes[index].valor1 == partida.valorEsq
			|| partida.jugadors[partida.jugadorActual].fitxes[index].valor2 == partida.valorEsq)
		{
			fitxa = partida.jugadors[partida.jugadorActual].fitxes[index];
			trobat = true;
		}
		else if (partida.jugadors[partida.jugadorActual].fitxes[index].valor1 == partida.valorDret 
				|| partida.jugadors[partida.jugadorActual].fitxes[index].valor2 == partida.valorDret)
		{
			fitxa = partida.jugadors[partida.jugadorActual].fitxes[index];
			trobat = true;
		}
		else
			index++;
	}
	if (!trobat)
	{
		partida.nTornsPassant++;
	}
}



void actualitzaPartida(Partida& partida, Fitxa& fitxa, int& index)
{
	partida.nTornsPassant = 0;
	if (partida.valorEsq == fitxa.valor1)
		partida.valorEsq = fitxa.valor2;
	else if (partida.valorEsq == fitxa.valor2)
		partida.valorEsq = fitxa.valor1;
	else if (partida.valorDret == fitxa.valor1)
		partida.valorDret = fitxa.valor2;
	else if (partida.valorDret == fitxa.valor2)
		partida.valorDret = fitxa.valor1;

	quitarFichaDelJugador(partida, index);
}

int guanyador(Partida& partida)
{
	int i = 0;
	bool trobat = false;

	while (!trobat && i < MAX_JUGADORS)
	{
		if (partida.jugadors[i].nFitxes == 0)
			trobat = true;
		else
			i++;
	}

	if (trobat)
		return i;
	else
		return -1;
}

bool partidaBloqueada(Partida& partida)
{
	return (partida.nTornsPassant == 4);
}

void cambioDeTurno(Partida& partida)
{
	partida.jugadorActual = (partida.jugadorActual + 1) % MAX_JUGADORS;
}

int jugaDomino(Fitxa fitxesInicials[MAX_FITXES * MAX_JUGADORS], Fitxa fitxesJugades[MAX_FITXES * MAX_JUGADORS * 2], int& nFitxesJugades)
{
	nFitxesJugades = 0;
	fitxesJugades[0].valor1 = 0;
	fitxesJugades[0].valor2 = 0;
	int jugadorGuanyador = -1;
	bool bloqueada = false;
	Partida partida;

	inicializar(partida, fitxesInicials);
	while ((jugadorGuanyador == -1) && (!bloqueada))
	{
		Fitxa f;
		int index;
		seleccionaFitxa(partida, f, index);
		fitxesJugades[nFitxesJugades].valor1 = f.valor1;
		fitxesJugades[nFitxesJugades].valor2 = f.valor2;
		nFitxesJugades++;
		if (f.valor1 != -1)
		{
			actualitzaPartida(partida, f, index);
			jugadorGuanyador = guanyador(partida);
		}
		else
			bloqueada = partidaBloqueada(partida);
		cambioDeTurno(partida);
	}

	return jugadorGuanyador;
}