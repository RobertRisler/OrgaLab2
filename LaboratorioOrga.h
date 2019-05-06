#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructuras
typedef struct Nodo
{
    char ins[5];          // add, sub, and, etc...
    char rs[5];           // Primer operando
    char rt[5];           // Segundo operando / registro destino
    char rd[5];           // Registro destino
    char label[10];        // Etiqueta para instrucciones beq / j
    char offset[5];       // Dato para lw / sw
    char immediate[10];    // Valor para instrucción addi
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
lista guardarInstrucciones(char *nombre, int cantidadInstrucciones, int *arregloTipos, lista memoriaIns);
void imprimirMemoriaInstrucciones(lista memoriaIns);