// ConexionSerieWired.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//


#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "SerialClass/SerialClass.h"

int main()
{
    Serial* Arduino; 
    char puerto[]="COM3";
    char BufferSalida[200];
    char BufferEntrada[200];
    int bytesRecibidos;
    int contador = 0;
    char secuencia[4];
    char max, *p;
    char min, *pm;
  
    p=&max;
    pm = &min;

    Arduino = new Serial((char *)puerto);
    while (Arduino->IsConnected())
    {
        printf("Arduino conectado\n");
        sprintf_s(secuencia, "%d", contador);
        strcpy_s(BufferSalida, "Este es el mensaje enviado por el puerto serie ");
        strcat_s(BufferSalida, secuencia);
        printf("Enviando %s\n",BufferSalida);
        Arduino->WriteData(BufferSalida, strlen(BufferSalida));
        contador++;
        if (contador == 1)
            Sleep(2000);
        else
            Sleep(2000);
        bytesRecibidos = Arduino->ReadData(BufferEntrada, sizeof(char)*199);
        if (bytesRecibidos != -1)
        {
            BufferEntrada[bytesRecibidos - 1] = '\0';

            max= 20;
            min = 1;

                printf("Recibidos %d bytes. Contenido: %s\n\n\n", bytesRecibidos, BufferEntrada);
              /*  if (BufferEntrada < p && BufferEntrada>pm) {
                    printf("Bucle\n");
                }
                
                */
        }
        else
            printf("No se ha recibido nada\n");
        Sleep(1000);
    }
}




