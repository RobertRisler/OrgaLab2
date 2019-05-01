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
// correspondiente si es necesarios, sino durante la ejecucion de instrucciones.
// Se utilizan valores 0 o 1 normalmente, si el valor que presenta una linea de control es 2,
// indica que está en modo "Stuck-at-1".
    int RegDst = 0;
    int Jump = 0;
    int Branch = 0;
    int MemRead = 0;
    int MemtoReg = 0;
    int ALUOP = 0;
    int MemWrite = 0;
    int ALUSrc = 0;
    int RegWrite = 0;

// ########## Main ##########
int main() {
    menu();
    return 0;
}

// ########## Funciones ##########
void menu(){
    leerArchivoControl();
    return;
}

void leerArchivoInstrucciones(){
    char nombreArchivoInstrucciones[50];
    printf("Ingrese el nombre del archivo de instrucciones:\n");
    scanf("%s", nombreArchivoInstrucciones);
    FILE* pArchivo;
    pArchivo = fopen(nombreArchivoInstrucciones, "r");
    char linea[30];
    while(!feof(pArchivo)){
        fgets(linea, 30, pArchivo);
        printf("%s", linea);
    }
    fclose(pArchivo);
}

void leerArchivoControl(){
    char nombreArchivoControl[50];
    printf("Ingrese el nombre del archivo de control:\n");
    scanf("%s", nombreArchivoControl);

    FILE* pArchivo;
    pArchivo = fopen(nombreArchivoControl, "r");

    char nombreControl[30];
    char valorControl[2];
    while(!feof(pArchivo)){
        fscanf(pArchivo, "%s %s\n", nombreControl, valorControl);
        printf("%s - %s\n", nombreControl, valorControl);
        if (strcmp(nombreControl, "RegDst") == 0){
            if (strcmp(valorControl, "1")){
                RegDst = 1;
            }
        }
    }
    fclose(pArchivo);
    return;
}
