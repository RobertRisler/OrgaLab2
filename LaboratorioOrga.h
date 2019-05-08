#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructuras
typedef struct Nodo
{
    char *ins;          // add, sub, and, etc...
    char *rs;           // Primer operando
    char *rt;           // Segundo operando / registro destino
    char *rd;           // Registro destino
    char *label;        // Etiqueta para instrucciones beq / j
    char *offset;       // Dato para lw / sw
    char *immediate;    // Valor para instrucción addi
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
lista guardarInstrucciones(char *nombre, lista memoriaIns);
void limpiarLinea(char *string);
void removerComa(char *string, char basura);
void imprimirMemoriaInstrucciones(lista memoriaIns);