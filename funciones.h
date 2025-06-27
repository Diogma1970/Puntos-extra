#ifndef FUNCIONES_H
#define FUNCIONES_H

#define MAX_EQUIPOS 20
#define MAX_JUGADORES 100
#define MAX_NOMBRE 30
#define MAX_GOLEADORES 5

typedef struct {
    char nombre[MAX_NOMBRE];
    int goles;
} Jugador;

typedef struct {
    char nombre[MAX_NOMBRE];
    int puntos;
    int goles_a_favor;
    int goles_en_contra;
    int tarjetas_amarillas;
    int tarjetas_rojas;
} Equipo;

extern Equipo equipos[MAX_EQUIPOS];
extern Jugador jugadores[MAX_JUGADORES];
extern int total_equipos;
extern int total_jugadores;

int buscarEquipo(char *nombre);
int buscarJugador(char *nombre);
void registrarPartido();
void mostrarTabla();
void mostrarGoleador();
void menu();

#endif
