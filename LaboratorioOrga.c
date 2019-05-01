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
int Regdst = 0;
int Jump = 0;
int Branch = 0;
int Memread = 0;
int Memtoreg = 0;
int Aluop = 0;
int Memwrite = 0;
int Alusrc = 0;
int Regwrite = 0;

// ########## Main ##########
int main() {
    menu();
    return 0;
}

// ########## Funciones ##########
void menu(){
    
}

void leerArchivoInstrucciones(){

}

void leerArchivoControl(){

}

