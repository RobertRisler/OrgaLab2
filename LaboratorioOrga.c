#include "LaboratorioOrga.h"

// ########## Variables globales ##########

// ##### Registros #####
// Todos los registros parten iniciados en cero, cambian sus valores durante la ejecucion.
// ## $zero ##
int zero = 0;
// ## $at ##
int at = 0;
// ## $v0 - $v1 ##
int v0 = 0;
int v1 = 0;
// ## $a0 - $a3
int a0 = 0;
int a1 = 0;
int a2 = 0;
int a3 = 0;
// ## $t0 - $t7 ##
int t0 = 0;
int t1 = 0;
int t2 = 0;
int t3 = 0;
int t4 = 0;
int t5 = 0;
int t6 = 0;
int t7 = 0;
// ## $s0 - $s7
int s0 = 0;
int s1 = 0;
int s2 = 0;
int s3 = 0;
int s4 = 0;
int s5 = 0;
int s6 = 0;
int s7 = 0;
// ## $t8 - $t9 ##
int t8 = 0;
int t9 = 0;
// ## $k0 - $k1 ##
int k0 = 0;
int k1 = 0;
// ## $gp ##
int gp = 0;
// ## $sp ##
int sp = 0;
// ## $fp ##
int fp = 0;
// ## $ra ##
int ra = 0;

// ##### Lineas de Control #####
// Todas las lineas parten iniciadas en 0, cambian sus valores al leer el archivo de entrada
// si es necesario, sino, cambian solamente durante la ejecucion de instrucciones.
// Se utilizan valores 0 o 1 normalmente, si el valor que presenta una linea de control es 2,
// indica que está en modo "Stuck-at-1".
int RegDst = 0;
int Jump = 0;
int Branch = 0;
int MemRead = 0;
int MemtoReg = 0;
int ALUOpIZQ = 0; // -> 00
int ALUOpDER = 0; //    00 <-
int MemWrite = 0;
int ALUSrc = 0;
int RegWrite = 0;

// ##### Memoria #####
// Arreglo utilizado como memoria para guardar o cargar datos con sw y lw respectivamente.
int memoria[1024];

// ##### Miscelaneo #####
// Puntero utilizado para la identificación de que ocurre un branch o un jump.
// Se cambia al nombre de la etiqueta que se busca cuando se da el caso, luego
// de encontrarla, se retorna el valor del puntero a NULL.
char *etiqueta = NULL;

// ########## Main ##########
int main()
{
    menu();
    return 0;
}

// ########## Funciones ##########
void menu()
{
    /*
    char nombreArchivoControl[50];
    printf("Ingrese el nombre del archivo de control:\n");
    scanf("%s", nombreArchivoControl);
    */
    leerArchivoControl("control.txt");

    /*
    char nombreArchivoInstrucciones[50];
    printf("Ingrese el nombre del archivo de instrucciones:\n");
    scanf("%s", nombreArchivoInstrucciones);
    */
    lista *memoriaInstrucciones = (lista *)malloc(sizeof(lista));
    memoriaInstrucciones->largo = 0;
    memoriaInstrucciones->inicio = NULL;
    guardarInstrucciones("instrucciones.txt", memoriaInstrucciones);

    ejecucionPrograma(memoriaInstrucciones);
    return;
}

void leerArchivoControl(char *nombre)
{
    FILE *pArchivo;
    pArchivo = fopen(nombre, "r");
    char nombreControl[30];
    char valorControl[2];
    while (!feof(pArchivo))
    {
        fscanf(pArchivo, "%s %s\n", nombreControl, valorControl);
        if (strcmp(nombreControl, "RegDst") == 0)
        {
            if (strcmp(valorControl, "1") == 0)
            {
                RegDst = 2;
            }
        }
        /*
        if (strcmp(nombreControl, "Jump") == 0)
        {
            if (strcmp(valorControl, "1") == 0)
            {
                Jump = 2;
            }
        }
        if (strcmp(nombreControl, "Branch") == 0)
        {
            if (strcmp(valorControl, "1") == 0)
            {
                Branch = 2;
            }
        }
        if (strcmp(nombreControl, "MemRead") == 0)
        {
            if (strcmp(valorControl, "1") == 0)
            {
                MemRead = 2;
            }
        }
        if (strcmp(nombreControl, "MemtoReg") == 0)
        {
            if (strcmp(valorControl, "1") == 0)
            {
                MemtoReg = 2;
            }
        }
        if (strcmp(nombreControl, "ALUOp") == 0)
        {
            if (strcmp(valorControl, "1") == 0)
            {
                ALUOp = 2;
            }
        }
        if (strcmp(nombreControl, "MemWrite") == 0)
        {
            if (strcmp(valorControl, "1") == 0)
            {
                MemWrite = 2;
            }
        }
        */
        if (strcmp(nombreControl, "ALUSrc") == 0)
        {
            if (strcmp(valorControl, "1") == 0)
            {
                ALUSrc = 2;
            }
        }
        if (strcmp(nombreControl, "RegWrite") == 0)
        {
            if (strcmp(valorControl, "1") == 0)
            {
                RegWrite = 2;
            }
        }
    }
    fclose(pArchivo);
    return;
}

void guardarInstrucciones(char *nombre, lista *memoriaIns)
{
    FILE *pArchivo;
    pArchivo = fopen(nombre, "r");

    char linea[50];
    while (!feof(pArchivo))
    {
        fgets(linea, 50, pArchivo);
        limpiarLinea(linea);

        char *token1, *token2, *token3, *token4;
        token1 = strtok(linea, " ");

        if (strcmp(token1, "add") == 0 || strcmp(token1, "sub") == 0 || strcmp(token1, "and") == 0 ||
            strcmp(token1, "or") == 0 || strcmp(token1, "slt") == 0)
        {
            token2 = strtok(NULL, " ");
            token3 = strtok(NULL, " ");
            token4 = strtok(NULL, " ");
            ingresarInstruccion(memoriaIns, 1, token1, token2, token3, token4);
        }
        else if (strcmp(token1, "lw") == 0 || strcmp(token1, "sw") == 0)
        {
            token2 = strtok(NULL, " ");
            token3 = strtok(NULL, " ");
            token4 = strtok(NULL, " ");
            ingresarInstruccion(memoriaIns, 2, token1, token2, token3, token4);
        }
        else if (strcmp(token1, "addi") == 0)
        {
            token2 = strtok(NULL, " ");
            token3 = strtok(NULL, " ");
            token4 = strtok(NULL, " ");
            ingresarInstruccion(memoriaIns, 3, token1, token2, token3, token4);
        }
        else if (strcmp(token1, "beq") == 0)
        {
            token2 = strtok(NULL, " ");
            token3 = strtok(NULL, " ");
            token4 = strtok(NULL, " ");
            ingresarInstruccion(memoriaIns, 4, token1, token2, token3, token4);
        }
        else if (strcmp(token1, "j") == 0)
        {
            token2 = strtok(NULL, " ");
            ingresarInstruccion(memoriaIns, 5, token1, token2, "placeholder", "placeholder");
        }
        else if (strchr(token1, ':') != NULL)
        {
            ingresarInstruccion(memoriaIns, 6, token1, "placeholder", "placeholder", "placeholder");
        }
    }
    fclose(pArchivo);
    return;
}

void ingresarInstruccion(lista *memoriaIns, int tipoIns, char *token1, char *token2, char *token3, char *token4)
{
    nodo *instruccion = (nodo *)malloc(sizeof(nodo));

    switch (tipoIns)
    {
    case 1: // add, sub, and, or, slt
        strcpy(instruccion->ins, token1);
        strcpy(instruccion->rd, token2);
        strcpy(instruccion->rs, token3);
        strcpy(instruccion->rt, token4);
        break;
    case 2: // lw, sw
        strcpy(instruccion->ins, token1);
        strcpy(instruccion->rt, token2);
        strcpy(instruccion->offset, token3);
        strcpy(instruccion->rs, token4);
        break;
    case 3: // addi
        strcpy(instruccion->ins, token1);
        strcpy(instruccion->rt, token2);
        strcpy(instruccion->rs, token3);
        strcpy(instruccion->immediate, token4);
        break;
    case 4: // beq
        strcpy(instruccion->ins, token1);
        strcpy(instruccion->rt, token2);
        strcpy(instruccion->rs, token3);
        strcpy(instruccion->label, token4);
        break;
    case 5: // j
        strcpy(instruccion->ins, token1);
        strcpy(instruccion->label, token2);
        break;
    case 6: // label
        strcpy(instruccion->ins, token1);
        break;
    default:
        free(instruccion);
        return;
    }

    instruccion->sgte = NULL;
    if (memoriaIns->largo == 0)
    {
        memoriaIns->inicio = instruccion;
        memoriaIns->largo = 1;
    }
    else
    {
        nodo *aux = memoriaIns->inicio;
        int j;
        for (j = 0; j < memoriaIns->largo - 1; j++)
        {
            aux = aux->sgte;
        }
        aux->sgte = instruccion;
        memoriaIns->largo++;
    }
    return;
}

void limpiarLinea(char *string)
{
    while (strchr(string, ',') != NULL)
    {
        removerComa(string, ',');
    }
    if (strchr(string, '(') != NULL)
    {
        char *aux;
        aux = strchr(string, '(');
        *aux = ' ';
    }
    if (strchr(string, ')') != NULL)
    {
        char *aux;
        aux = strchr(string, ')');
        *aux = ' ';
    }
    if (strchr(string, '\n') != NULL)
    {
        char *aux;
        aux = strchr(string, '\n');
        *aux = '\0';
    }
    return;
}

void removerComa(char *string, char basura)
{
    char *aux1, *aux2;
    for (aux1 = aux2 = string; *aux1 != '\0'; aux1++)
    {
        *aux2 = *aux1;
        if (*aux2 != basura)
        {
            aux2++;
        }
    }
    *aux2 = '\0';
    return;
}

void imprimirMemoriaInstrucciones(lista *memoriaIns)
{
    int i;
    printf("largo memoria: %d\n", memoriaIns->largo);
    nodo *aux = memoriaIns->inicio;
    for (i = 0; i < memoriaIns->largo; i++)
    {

        if (strcmp(aux->ins, "add") == 0 || strcmp(aux->ins, "sub") == 0 || strcmp(aux->ins, "and") == 0 ||
            strcmp(aux->ins, "or") == 0 || strcmp(aux->ins, "slt") == 0)
        {
            printf("%s %s, %s, %s\n", aux->ins, aux->rd, aux->rs, aux->rt);
        }
        else if (strcmp(aux->ins, "lw") == 0 || strcmp(aux->ins, "sw") == 0)
        {
            printf("%s %s, %s(%s)\n", aux->ins, aux->rt, aux->offset, aux->rs);
        }
        else if (strcmp(aux->ins, "addi") == 0)
        {
            printf("%s %s, %s, %s\n", aux->ins, aux->rt, aux->rs, aux->immediate);
        }
        else if (strcmp(aux->ins, "beq") == 0)
        {
            printf("%s %s, %s, %s\n", aux->ins, aux->rt, aux->rs, aux->label);
        }
        else if (strcmp(aux->ins, "j") == 0)
        {
            printf("%s %s\n", aux->ins, aux->label);
        }
        else if (strchr(aux->ins, ':') != NULL)
        {
            printf("%s\n", aux->ins);
        }
        aux = aux->sgte;
    }
    return;
}

void ejecucionPrograma(lista *memoriaIns)
{
    rellenarMemoria();
    int numeroCiclo = 0;
    nodo *contadorPrograma = memoriaIns->inicio;

    while (contadorPrograma != NULL)
    {
        numeroCiclo++;
        // Escribir número ciclo
        if (strchr(contadorPrograma->ins, ':') != NULL)
        {
            int operacion;
            modificarControl(contadorPrograma);
            ejecutarInstruccion(contadorPrograma);

            contadorPrograma = contadorPrograma->sgte;
        }
        else
        {
            numeroCiclo--;
            contadorPrograma = contadorPrograma->sgte;
        }
        imprimirControl();
        imprimirRegistros();
        printf("\n");
    }

    return;
}

void modificarControl(nodo *instruccion)
{
    if (strcmp(instruccion->ins, "add") == 0 || strcmp(instruccion->ins, "sub") == 0 || strcmp(instruccion->ins, "and") == 0 ||
        strcmp(instruccion->ins, "or") == 0 || strcmp(instruccion->ins, "slt") == 0) // Instruccion tipo R
    {
        if (RegDst != 2)
        {
            RegDst = 1;
        }
        Jump = 0;
        Branch = 0;
        MemRead = 0;
        MemtoReg = 0;
        ALUOpIZQ = 1;
        ALUOpDER = 0;
        MemWrite = 0;
        if (ALUSrc != 2)
        {
            ALUSrc = 0;
        }
        if (RegWrite != 2)
        {
            RegWrite = 1;
        }
    }
    else if (strcmp(instruccion->ins, "lw") == 0)
    {
        if (RegDst != 2)
        {
            RegDst = 0;
        }
        Jump = 0;
        Branch = 0;
        MemRead = 1;
        MemtoReg = 1;
        ALUOpIZQ = 0;
        ALUOpDER = 0;
        MemWrite = 0;
        if (ALUSrc != 2)
        {
            ALUSrc = 1;
        }
        if (RegWrite != 2)
        {
            RegWrite = 1;
        }
    }
    else if (strcmp(instruccion->ins, "sw") == 0)
    {
        /*
        if (RegDst != 2)
        {
            RegDst = 0;     // Don't care
        }
        */
        Jump = 0;
        Branch = 0;
        MemRead = 0;
        // MemtoReg = 0;    // Don't care
        ALUOpIZQ = 0;
        ALUOpDER = 0;
        MemWrite = 1;
        if (ALUSrc != 2)
        {
            ALUSrc = 1;
        }
        if (RegWrite != 2)
        {
            RegWrite = 0;
        }
    }
    else if (strcmp(instruccion->ins, "beq") == 0)
    {
        /*
        if (RegDst != 2)
        {
            RegDst = 0;     // Don't care
        }
        */
        Jump = 0;
        Branch = 1;
        MemRead = 0;
        // MemtoReg = 0;    // Don't care
        ALUOpIZQ = 0;
        ALUOpDER = 1;
        MemWrite = 0;
        if (ALUSrc != 2)
        {
            ALUSrc = 0;
        }
        if (RegWrite != 2)
        {
            RegWrite = 0;
        }
    }
    else if (strcmp(instruccion->ins, "addi") == 0)
    {
        if (RegDst != 2)
        {
            RegDst = 0;
        }
        Jump = 0;
        Branch = 0;
        MemRead = 0;
        MemtoReg = 0;
        ALUOpIZQ = 0;
        ALUOpDER = 0;
        MemWrite = 0;
        if (ALUSrc != 2)
        {
            ALUSrc = 1;
        }
        if (RegWrite != 2)
        {
            RegWrite = 1;
        }
    }
    else if (strcmp(instruccion->ins, "j") == 0)
    {
        /*
        if (RegDst != 2)
        {
            RegDst = 0;     // Don't care
        }
        */
        Jump = 0;
        // Branch = 0;      // Don't care
        MemRead = 0;
        // MemtoReg = 0;    // Don't care
        // ALUOpIZQ = 0;    // Don't care
        // ALUOpDER = 0;    // Don't care
        MemWrite = 0;
        /*
        if (ALUSrc != 2)
        {
            ALUSrc = 1;     // Don't care
        }
        */
        if (RegWrite != 2)
        {
            RegWrite = 1;
        }
    }

    // Escribir valores control
    return;
}

void ejecutarInstruccion(nodo *instruccion)
{
    if (strcmp(instruccion->ins, "add") == 0 || strcmp(instruccion->ins, "sub") == 0 || strcmp(instruccion->ins, "and") == 0 ||
        strcmp(instruccion->ins, "or") == 0 || strcmp(instruccion->ins, "slt") == 0)
    {
        if ((RegDst == 1 || RegDst == 2) && (ALUSrc == 0) && (RegWrite == 1 || RegWrite == 2))
        {
            if (strcmp(instruccion->ins, "add") == 0)
            {
                *obtenerReferencia(instruccion->rd) = obtenerDato(instruccion->rs) + obtenerDato(instruccion->rt);
            }
            else if (strcmp(instruccion->ins, "sub") == 0)
            {
                *obtenerReferencia(instruccion->rd) = obtenerDato(instruccion->rs) - obtenerDato(instruccion->rt);
            }
            else if (strcmp(instruccion->ins, "and") == 0)
            {
                if (obtenerDato(instruccion->rs) == obtenerDato(instruccion->rt))
                {
                    *obtenerReferencia(instruccion->rd) = obtenerDato(instruccion->rs);
                }
                else
                {
                    
                }
            }
            else if (strcmp(instruccion->ins, "or") == 0)
            {
                if (obtenerDato(instruccion->rs) == obtenerDato(instruccion->rt))
                {
                    *obtenerReferencia(instruccion->rd) = obtenerDato(instruccion->rs);
                }
                else
                {
                    
                }
            }
            else if (strcmp(instruccion->ins, "slt") == 0)
            {
                if (obtenerDato(instruccion->rs) < obtenerDato(instruccion->rt))
                {
                    *obtenerReferencia(instruccion->rd) = 1;
                }
                else
                {
                    *obtenerReferencia(instruccion->rd) = 0;
                }
            }
            // Escribir valores registros
        }
        else
        {
            // Escribir error
        }
    }
    else if (strcmp(instruccion->ins, "lw") == 0)
    {
        if ((RegDst == 0) && (ALUSrc == 1 || ALUSrc == 2) && (RegWrite == 1 || RegWrite == 2))
        {
            int direccion = (obtenerDato(instruccion->rs) + atoi(instruccion->offset)) / 4;
            *obtenerReferencia(instruccion->rt) = memoria[direccion];
            // Escribir valores registros
        }
        else
        {
            // Escribir error
        }
    }
    else if (strcmp(instruccion->ins, "sw") == 0)
    {
        if ((RegDst == 0 || RegDst == 1 || RegDst == 2) && (ALUSrc == 1 || ALUSrc == 2) && (RegWrite == 0))
        {
            int direccion = (obtenerDato(instruccion->rs) + atoi(instruccion->offset)) / 4;
            memoria[direccion] = obtenerDato(instruccion->rt);
            // Escribir valores registros
        }
        else
        {
            // Escribir error
        }
    }
    else if (strcmp(instruccion->ins, "addi") == 0)
    {
        if ((RegDst == 0) && (ALUSrc == 1 || ALUSrc == 2) && (RegWrite == 1 || RegWrite == 2))
        {
            *obtenerReferencia(instruccion->rt) = obtenerDato(instruccion->rs) + atoi(instruccion->immediate);
            // Escribir valores registros
        }
        else
        {
            // Escribir error
        }
    }
    else if (strcmp(instruccion->ins, "beq") == 0)
    {
        if ((RegDst == 0 || RegDst == 1 || RegDst == 2) && (ALUSrc == 1 || ALUSrc == 2) && (RegWrite == 0))
        {
            if (obtenerDato(instruccion->rt) == obtenerDato(instruccion->rs))
            {
                etiqueta = instruccion->label;
            }
            // Escribir valores registros
        }
        else
        {
            // Escribir error
        }
    }
    else if (strcmp(instruccion->ins, "j") == 0)
    {
        if ((RegDst == 0 || RegDst == 1 || RegDst == 2) && (ALUSrc == 0 || ALUSrc == 1 || ALUSrc == 2) && (RegWrite == 0))
        {
            etiqueta = instruccion->label;
            // Escribir valores registros
        }
        else
        {
            // Escribir error
        }
    }

    return;
}

int *obtenerReferencia(char *string)
{
    if (strcmp(string, "$zero") == 0)
    {
        return &zero;
    }
    else if (strcmp(string, "$at") == 0)
    {
        return &at;
    }
    else if (strcmp(string, "$v0") == 0)
    {
        return &v0;
    }
    else if (strcmp(string, "$v1") == 0)
    {
        return &v1;
    }
    else if (strcmp(string, "$a0") == 0)
    {
        return &a0;
    }
    else if (strcmp(string, "$a1") == 0)
    {
        return &a1;
    }
    else if (strcmp(string, "$a2") == 0)
    {
        return &a2;
    }
    else if (strcmp(string, "$a3") == 0)
    {
        return &a3;
    }
    else if (strcmp(string, "$t0") == 0)
    {
        return &t0;
    }
    else if (strcmp(string, "$t1") == 0)
    {
        return &t1;
    }
    else if (strcmp(string, "$t2") == 0)
    {
        return &t2;
    }
    else if (strcmp(string, "$t3") == 0)
    {
        return &t3;
    }
    else if (strcmp(string, "$t4") == 0)
    {
        return &t4;
    }
    else if (strcmp(string, "$t5") == 0)
    {
        return &t5;
    }
    else if (strcmp(string, "$t6") == 0)
    {
        return &t6;
    }
    else if (strcmp(string, "$t7") == 0)
    {
        return &t7;
    }
    else if (strcmp(string, "$s0") == 0)
    {
        return &s0;
    }
    else if (strcmp(string, "$s1") == 0)
    {
        return &s1;
    }
    else if (strcmp(string, "$s2") == 0)
    {
        return &s2;
    }
    else if (strcmp(string, "$s3") == 0)
    {
        return &s3;
    }
    else if (strcmp(string, "$s4") == 0)
    {
        return &s4;
    }
    else if (strcmp(string, "$s5") == 0)
    {
        return &s5;
    }
    else if (strcmp(string, "$s6") == 0)
    {
        return &s6;
    }
    else if (strcmp(string, "$s7") == 0)
    {
        return &s7;
    }
    else if (strcmp(string, "$t8") == 0)
    {
        return &t8;
    }
    else if (strcmp(string, "$t9") == 0)
    {
        return &t9;
    }
    else if (strcmp(string, "$k0") == 0)
    {
        return &k0;
    }
    else if (strcmp(string, "$k1") == 0)
    {
        return &k1;
    }
    else if (strcmp(string, "$gp") == 0)
    {
        return &gp;
    }
    else if (strcmp(string, "$sp") == 0)
    {
        return &sp;
    }
    else if (strcmp(string, "$fp") == 0)
    {
        return &fp;
    }
    else if (strcmp(string, "$ra") == 0)
    {
        return &ra;
    }
    else
    {
        return 0;
    }
}

int obtenerDato(char *string)
{
    if (strcmp(string, "$zero") == 0)
    {
        return zero;
    }
    else if (strcmp(string, "$at") == 0)
    {
        return at;
    }
    else if (strcmp(string, "$v0") == 0)
    {
        return v0;
    }
    else if (strcmp(string, "$v1") == 0)
    {
        return v1;
    }
    else if (strcmp(string, "$a0") == 0)
    {
        return a0;
    }
    else if (strcmp(string, "$a1") == 0)
    {
        return a1;
    }
    else if (strcmp(string, "$a2") == 0)
    {
        return a2;
    }
    else if (strcmp(string, "$a3") == 0)
    {
        return a3;
    }
    else if (strcmp(string, "$t0") == 0)
    {
        return t0;
    }
    else if (strcmp(string, "$t1") == 0)
    {
        return t1;
    }
    else if (strcmp(string, "$t2") == 0)
    {
        return t2;
    }
    else if (strcmp(string, "$t3") == 0)
    {
        return t3;
    }
    else if (strcmp(string, "$t4") == 0)
    {
        return t4;
    }
    else if (strcmp(string, "$t5") == 0)
    {
        return t5;
    }
    else if (strcmp(string, "$t6") == 0)
    {
        return t6;
    }
    else if (strcmp(string, "$t7") == 0)
    {
        return t7;
    }
    else if (strcmp(string, "$s0") == 0)
    {
        return s0;
    }
    else if (strcmp(string, "$s1") == 0)
    {
        return s1;
    }
    else if (strcmp(string, "$s2") == 0)
    {
        return s2;
    }
    else if (strcmp(string, "$s3") == 0)
    {
        return s3;
    }
    else if (strcmp(string, "$s4") == 0)
    {
        return s4;
    }
    else if (strcmp(string, "$s5") == 0)
    {
        return s5;
    }
    else if (strcmp(string, "$s6") == 0)
    {
        return s6;
    }
    else if (strcmp(string, "$s7") == 0)
    {
        return s7;
    }
    else if (strcmp(string, "$t8") == 0)
    {
        return t8;
    }
    else if (strcmp(string, "$t9") == 0)
    {
        return t9;
    }
    else if (strcmp(string, "$k0") == 0)
    {
        return k0;
    }
    else if (strcmp(string, "$k1") == 0)
    {
        return k1;
    }
    else if (strcmp(string, "$gp") == 0)
    {
        return gp;
    }
    else if (strcmp(string, "$sp") == 0)
    {
        return sp;
    }
    else if (strcmp(string, "$fp") == 0)
    {
        return fp;
    }
    else if (strcmp(string, "$ra") == 0)
    {
        return ra;
    }
    else
    {
        return 0;
    }
}

void rellenarMemoria()
{
	int i;
	for(i = 0; i < 1024; i++)
    {
		memoria[i] = 0;
	}
	return;
}

void imprimirControl()
{
    printf("RegDst: %d - ", RegDst);
    printf("Jump: %d - ", Jump);
    printf("Branch: %d - ", Branch);
    printf("MemRead: %d - ", MemRead);
    printf("MemtoReg: %d - ", MemtoReg);
    printf("ALUOpIZQ: %d - ", ALUOpIZQ);
    printf("ALUOpDER: %d - ", ALUOpDER);
    printf("MemWrite: %d - ", MemWrite);
    printf("ALUSrc: %d - ", ALUSrc);
    printf("RegWrite: %d\n", RegWrite);
}

void imprimirRegistros()
{
    printf("$zero = %d\n", zero);
    printf("$at = %d\n", at);
    printf("$v0 = %d\n", v0);
    printf("$v1 = %d\n", v1);
    printf("$a0 = %d\n", a0);
    printf("$a1 = %d\n", a1);
    printf("$a2 = %d\n", a2);
    printf("$a3 = %d\n", a3);
    printf("$t0 = %d\n", t0);
    printf("$t1 = %d\n", t1);
    printf("$t2 = %d\n", t2);
    printf("$t3 = %d\n", t3);
    printf("$t4 = %d\n", t4);
    printf("$t5 = %d\n", t5);
    printf("$t6 = %d\n", t6);
    printf("$t7 = %d\n", t7);
    printf("$s0 = %d\n", s0);
    printf("$s1 = %d\n", s1);
    printf("$s2 = %d\n", s2);
    printf("$s3 = %d\n", s3);
    printf("$s4 = %d\n", s4);
    printf("$s5 = %d\n", s5);
    printf("$s6 = %d\n", s6);
    printf("$s7 = %d\n", s7);
    printf("$t8 = %d\n", t8);
    printf("$t9 = %d\n", t9);
    printf("$k0 = %d\n", k0);
    printf("$k1 = %d\n", k1);
    printf("$gp = %d\n", gp);
    printf("$sp = %d\n", sp);
    printf("$fp = %d\n", fp);
    printf("$ra = %d\n", ra);
    return;
}