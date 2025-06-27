#include <stdio.h>
#include <string.h>
#include "funciones.h"

Equipo equipos[MAX_EQUIPOS];
Jugador jugadores[MAX_JUGADORES];
int total_equipos = 0;
int total_jugadores = 0;

int buscarEquipo(char *nombre) {
    for (int i = 0; i < total_equipos; i++) {
        if (strcmp(equipos[i].nombre, nombre) == 0) return i;
    }
    if (total_equipos >= MAX_EQUIPOS) {
        printf("¡Máximo de equipos alcanzado!\n");
        return -1;
    }
    strcpy(equipos[total_equipos].nombre, nombre);
    equipos[total_equipos].puntos = 0;
    equipos[total_equipos].goles_a_favor = 0;
    equipos[total_equipos].goles_en_contra = 0;
    equipos[total_equipos].tarjetas_amarillas = 0;
    equipos[total_equipos].tarjetas_rojas = 0;
    return total_equipos++;
}

int buscarJugador(char *nombre) {
    for (int i = 0; i < total_jugadores; i++) {
        if (strcmp(jugadores[i].nombre, nombre) == 0) return i;
    }
    if (total_jugadores >= MAX_JUGADORES) {
        printf("¡Máximo de jugadores alcanzado!\n");
        return -1;
    }
    strcpy(jugadores[total_jugadores].nombre, nombre);
    jugadores[total_jugadores].goles = 0;
    return total_jugadores++;
}



void registrarPartido() {
    char equipo1[MAX_NOMBRE], equipo2[MAX_NOMBRE];
    int goles1, goles2;
    int amarillas1, amarillas2, rojas1, rojas2;
    char goleador[MAX_NOMBRE];
    int idx1, idx2;

    while (getchar() != '\n');  // limpia buffer

    printf("\nNombre del primer equipo: ");
    fgets(equipo1, MAX_NOMBRE, stdin);
    equipo1[strcspn(equipo1, "\n")] = 0;

    printf("Nombre del segundo equipo: ");
    fgets(equipo2, MAX_NOMBRE, stdin);
    equipo2[strcspn(equipo2, "\n")] = 0;

    printf("Goles anotados por %s: ", equipo1); scanf("%d", &goles1);
    printf("Goles anotados por %s: ", equipo2); scanf("%d", &goles2);

    printf("Tarjetas amarillas de %s: ", equipo1); scanf("%d", &amarillas1);
    printf("Tarjetas rojas de %s: ", equipo1); scanf("%d", &rojas1);

    printf("Tarjetas amarillas de %s: ", equipo2); scanf("%d", &amarillas2);
    printf("Tarjetas rojas de %s: ", equipo2); scanf("%d", &rojas2);

    idx1 = buscarEquipo(equipo1);
    idx2 = buscarEquipo(equipo2);

    equipos[idx1].goles_a_favor += goles1;
    equipos[idx1].goles_en_contra += goles2;
    equipos[idx2].goles_a_favor += goles2;
    equipos[idx2].goles_en_contra += goles1;

    equipos[idx1].tarjetas_amarillas += amarillas1;
    equipos[idx1].tarjetas_rojas += rojas1;
    equipos[idx2].tarjetas_amarillas += amarillas2;
    equipos[idx2].tarjetas_rojas += rojas2;

    if (goles1 > goles2) equipos[idx1].puntos += 3;
    else if (goles2 > goles1) equipos[idx2].puntos += 3;
    else {
        equipos[idx1].puntos += 1;
        equipos[idx2].puntos += 1;
    }

    while (getchar() != '\n'); // limpia buffer

    printf("\nIngrese los %d goleadores del equipo %s:\n", goles1, equipo1);
    for (int i = 0; i < goles1; i++) {
        printf("Goleador %d: ", i + 1);
        fgets(goleador, MAX_NOMBRE, stdin);
        goleador[strcspn(goleador, "\n")] = 0;
        jugadores[buscarJugador(goleador)].goles++;
    }

    printf("\nIngrese los %d goleadores del equipo %s:\n", goles2, equipo2);
    for (int i = 0; i < goles2; i++) {
        printf("Goleador %d: ", i + 1);
        fgets(goleador, MAX_NOMBRE, stdin);
        goleador[strcspn(goleador, "\n")] = 0;
        jugadores[buscarJugador(goleador)].goles++;
    }

    printf("Partido registrado con éxito.\n");
}

void mostrarTabla() {
    printf("\n--- TABLA DE POSICIONES ---\n");
    printf("Equipo                Pts GF  GC  DG  TA  TR\n");
    printf("--------------------------------------------\n");
    for (int i = 0; i < total_equipos; i++) {
        int dg = equipos[i].goles_a_favor - equipos[i].goles_en_contra;
        printf("%-20s %3d %3d %3d %3d %3d %3d\n",
            equipos[i].nombre,
            equipos[i].puntos,
            equipos[i].goles_a_favor,
            equipos[i].goles_en_contra,
            dg,
            equipos[i].tarjetas_amarillas,
            equipos[i].tarjetas_rojas);
    }
}

void mostrarGoleador() {
    if (total_jugadores == 0) {
        printf("No hay goles registrados.\n");
        return;
    }

    int max_goles = jugadores[0].goles;
    for (int i = 0; i < total_jugadores; i++) {
        if (jugadores[i].goles > max_goles) {
            max_goles = jugadores[i].goles;
        }
    }

    printf("\n--- Máximos goleadores ---\n");
    for (int i = 0; i < total_jugadores; i++) {
        if (jugadores[i].goles == max_goles) {
            printf("%s con %d goles\n", jugadores[i].nombre, jugadores[i].goles);
        }
    }
}

void menu() {
    int opcion;
    do {
        printf("\n--- MENÚ ---\n");
        printf("1. Registrar un partido\n");
        printf("2. Mostrar tabla de posiciones\n");
        printf("3. Mostrar goleador del torneo\n");
        printf("4. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: registrarPartido(); break;
            case 2: mostrarTabla(); break;
            case 3: mostrarGoleador(); break;
            case 4: printf("Saliendo...\n"); break;
            default: printf("Opción no válida.\n");
        }
    } while (opcion != 4);
}
