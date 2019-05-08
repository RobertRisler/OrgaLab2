#include "LaboratorioOrga.h"

// ########## Variables globales ##########

// ##### Registros #####
// Todos los registros parten iniciados en cero, cambian sus valores durante la ejecucion.

// ## $zero ##
int $zero = 0;
// ## $at ##
int $at = 0;
// ## $v0 - $v1 ##
int $v0 = 0;
int $v1 = 0;
// ## $a0 - $a3
int $a0 = 0;
int $a1 = 0;
int $a2 = 0;
int $a3 = 0;
// ## $t0 - $t7 ##
int $t0 = 0;
int $t1 = 0;
int $t2 = 0;
int $t3 = 0;
int $t4 = 0;
int $t5 = 0;
int $t6 = 0;
int $t7 = 0;
// ## $s0 - $s7
int $s0 = 0;
int $s1 = 0;
int $s2 = 0;
int $s3 = 0;
int $s4 = 0;
int $s5 = 0;
int $s6 = 0;
int $s7 = 0;
// ## $t8 - $t9 ##
int $t8 = 0;
int $t9 = 0;
// ## $k0 - $k1 ##
int $k0 = 0;
int $k1 = 0;
// ## $gp ##
int $gp = 0;
// ## $sp ##
int $sp = 0;
// ## $fp ##
int $fp = 0;
// ## $ra ##
int $ra = 0;

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
int ALUOp = 0;
int MemWrite = 0;
int ALUSrc = 0;
int RegWrite = 0;

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

    ejecucion(memoriaInstrucciones);
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

void ejecucion(lista *memoriaIns)
{
    nodo *contadorPrograma = memoriaIns->inicio;
    
    return;
}