#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructuras
typedef struct Nodo
{
    char instruccion[]
    char *etiqueta; // Etiqueta para instrucciones beq / j
    int immediate;  // Valor para instrucción addi

    struct Nodo *sgte;
} nodo;

typedef struct Lista
{
    int largo;      // Largo total de la lista

    nodo *inicio;
} lista;

// Cabeceras
void menu();
void ejecucion();
void leerArchivoControl();
int contarInstrucciones();
void asignarTipoInstruccion(char *nombre, int *arregloTipos);
