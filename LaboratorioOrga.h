#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructuras
typedef struct Nodo
{
    char *op;       // Tipo instrucción
    char *rs;       // 1er operando
    char *rt;       // 2do operando / Destino
    char *rd;       // Destino
    char *shamt;    // 
    char *funct;    // Función instrucciones R
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
int leerArchivoInstrucciones();
void leerArchivoControl();
