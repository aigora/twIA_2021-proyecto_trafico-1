#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "SerialClass/SerialClass.h"

#define N 6

//estructuras
typedef struct {
    int multas_rango1;
    int multas_rango2;
    int multas_resto;
}T_VELOCIDAD;

typedef struct {
    char coche[N];
    int num_multas_semaforo;
    T_VELOCIDAD velocidad;
    float sancion_semaforo;
    float sancion_velocidad;
}T_COCHE;

//funciones
void Semaforo(T_COCHE* coches, int n_coches);
void Velocidad(T_COCHE* coches, int n_coches);
void CalcularSanciones(T_COCHE* coches, int n_coches);
void CargaRadaresFichero(FILE* pf_multas, T_COCHE* coches, int n_coches);

//
int main(void)
{
    int contador_semaforo;
    contador_semaforo = 0;
    int contador_velocidad;
    contador_velocidad = 0;
    int opc, i;
    int n_coches;
    T_COCHE* v_coches;
    FILE* pf_multas;


  


    printf("¿Cuantos coches van a pasar en total?\n");
    scanf_s("%d", &n_coches);

    v_coches = (T_COCHE*)calloc(n_coches, sizeof(T_COCHE));
    if (v_coches == NULL) {
        printf("\n Error en la asignacion de memoria: ");
        free(v_coches);
    }

    v_coches->velocidad.multas_rango1 = 0;
    v_coches->velocidad.multas_rango2 = 0;
    v_coches->velocidad.multas_resto = 0;
    v_coches->num_multas_semaforo = 0;
    v_coches->sancion_velocidad = 0;
    v_coches->sancion_semaforo = 0;

   // pf_multas = fopen_s("datos.txt", "a");

    errno_t err;
    err = fopen_s(&pf_multas, "Multas.txt", "a");
    if (err == 0)
        printf("Abierto");
    else
        printf("N");

   

        Velocidad(v_coches, n_coches);
        Semaforo(v_coches, n_coches);
       
        do {
            printf("-----MENU-----\n");
            printf("Seleccione un opcion:\n");
            printf("1.Mostrar multas del semáforo");
            printf("2.Mostrar multas del radar de velocidad");
            printf("3.Calcular las sanciones y las multas a pagar");
            printf("4.Salir");  //cuando sales del programa se guardan los datos en el fichero;
            scanf_s("%c", &opc);
            fflush(stdin);
            switch (opc) {
            case'1': //Semaforo
                for (i = 0; i < n_coches; i++) {
                    if (v_coches->num_multas_semaforo != 0) {
                        contador_semaforo++;
                    }
                }
                printf("%d multas por semáforo", contador_semaforo);

                break;


            case'2':  //velocidad
                //for (i = 0; i < n_coches; i++) {
                    if (v_coches->velocidad.multas_rango1 != 0 || v_coches->velocidad.multas_rango2 != 0 || v_coches->velocidad.multas_resto != 0) {
                        contador_velocidad++;
                    }
               // }
                printf("%d multas por velocidad", contador_velocidad);

                break;


            case'3':  //Calcula que hay que pagar
                CalcularSanciones(v_coches, n_coches);
                //for (i = 0; i < n_coches; i++) {
                    printf("%d a pagar por multas de semáforo y %d por multas de velocidad", v_coches->sancion_semaforo, v_coches->sancion_velocidad);
               // }
                break;
            case'5':  //salir del programa y guarda fichero
                CargaRadaresFichero(pf_multas, v_coches, n_coches);
                printf("Bye");
                break;

            default:
                printf("La opcion seleccionada es incorrecta, introduzca otro numero\n");

            }
            // return 0;
        } while (opc != 5);

    }
if (pf_multas == NULL) {
    printf("Error al abrir los archivos");
    if (fclose(pf_multas) == NULL) {
        printf("Cerrado\n");
    }

}




        
        


void Velocidad(T_COCHE* coches, int n_coches) {
    int i = 0, uno, dos, vel;
   
    printf("Introduzca los dos valores del sensor\n");
    scanf_s("%d %d", &uno, &dos);
    vel = uno - dos;
        if (vel>90 && vel<100) {
            coches->velocidad.multas_rango1++;
        }
        else {
            if (vel >100 && vel <110) {
                coches->velocidad.multas_rango2++;
            }
            else {
                if (vel >110) {
                   coches->velocidad.multas_resto++;
                }
            }
        }
    
    fgets(&coches->coche[i], N, stdin);

}


void Semaforo(T_COCHE* coches, int n_coches)
{
    //int i;
   // for (i = 0; i < n_coches; i++) {
    if ("semaforo rojo y se lo salta") {
        coches->num_multas_semaforo++;
    }
    printf("\n Introduzca la matricula del coche correspondiente");
    fgets(coches->coche, N, stdin);
    // }
     //return 0;
}


void CalcularSanciones(T_COCHE* coches, int n_coches) {
    int i, j;
    // for (i = 0; i < n_coches; i++) {
    if (coches->num_multas_semaforo != 0) {
        coches->sancion_semaforo = coches->num_multas_semaforo * 100.5; //multa de semaforo 100 euros
    }
    // }
    for (j = 0; j < n_coches; j++) {
        if (coches->velocidad.multas_rango1 != 0) {
            coches->sancion_velocidad = coches->velocidad.multas_rango1 * 50.5;
        }
        else {
            if (coches->velocidad.multas_rango2 != 0) {
                coches->sancion_velocidad = coches->velocidad.multas_rango1 * 60.5;
            }
            else {
                if (coches->velocidad.multas_resto != 0) {
                    coches->sancion_velocidad = coches->velocidad.multas_rango1 * 70.5;
                }
            }
        }
    }
}



    void CargaRadaresFichero(FILE * pf_multas, T_COCHE * coches, int n_coches) {
        int valor;
        int i;

        rewind(pf_multas);
        i = 0;
        do {
            valor = fprintf(pf_multas, "%s %d %d %d %d %f %f", &(coches->coche[i]), &(coches->num_multas_semaforo), &(coches->velocidad.multas_rango1), &(coches->velocidad.multas_rango2), &(coches->velocidad.multas_resto), &(coches->sancion_semaforo), &(coches->sancion_velocidad));
            if (valor == 7) {
                printf("\n%s %d %d %d %d %f %f", coches->coche[i], coches->num_multas_semaforo, coches->velocidad.multas_rango1, coches->velocidad.multas_rango2,coches->velocidad.multas_resto, coches->sancion_semaforo, coches->sancion_velocidad);
                i++;
            }
        } while (valor == 7);
        printf("\nSe han cargado %d radares en el vector de radares", i);
        return;
    }
