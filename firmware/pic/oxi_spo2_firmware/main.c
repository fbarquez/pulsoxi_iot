#include "mcc_generated_files/mcc.h"
#include <math.h>
#include <builtins.h>                   // Incluimos librería para trabajar con funciones matemáticas.
#include <math.h>                       // Incluimos librería para trabajar con operaciones matemáticas.
#include "LCD2x16_Library.h"            // Incluimos librería para trabajar con pantalla LCD 16x2.

#define         RED         0           // Asignamos el nombre RED al pin 0.
#define         INFRARED    1           // Asignamos el nombre INFRARED al pin 1.
#define         SignalR     0           // Asignamos el nombre SignalR al pin 0.
#define         SignalIR    1           // Asignamos el nombre SignalIR al pin 1.

/* Variables y arreglos globales  ===================================================================================================
 ==================================================================================================================================*/
uint16_t    tiempo_espera=25;           // Variable que temporizará 25ms.
uint16_t    antR,actR,antIR,actIR;
uint16_t    periodo=0;
uint8_t     subida=0;
uint8_t     pico=0;
float       BPM=0;
float       BPM_prom=0;
float       ratioR, ratioIR;
float       ratio_promR, ratio_promIR;
float       ratio_total;
float       Spo2;
float       vmaxR=0,vminR=0,vmaxIR=0,vminIR=0;
uint8_t     Buffer_LCD[16];             // Arreglo que almacenará el valor numerico con formato a mostrar en la LCD.

/* Función principal  ==============================================================================================================
 ==================================================================================================================================*/
void main(void)
{
    SYSTEM_Initialize();
    ANSELB=0x00;                        // Deshabilitamos las entradas analógicas del puerto B.
    ANSELD=0x00;                        // Deshabilitamos las entradas analógicas del puerto D.
    TRISB=0x00;                         // Configuramos el puerto B como salida.
    TRISC=0x00;                         // Configuramos el puerto C como salida.
    TRISD=0x00;                         // Configuramos el puerto D como salida.
    LATB=0x00;                          // Inicialmente el puerto B estará a nivel bajo.
    Lcd_Init();                         // Llamamos a la fución de configuración de la pantalla LCD.
    Lcd_Clear();                        // Limpiamos la pantalla LCD.
    LATB|=(1<<RED);                     // Inicialmente el pin estará a nivel alto.
    LATB&=~(1<<INFRARED);               // Inicialmente el pin estará a nivel bajo.
    antR=ADC_GetConversion(SignalR);    // Leemos el canal analógico del circuito RED.
    __delay_ms(tiempo_espera);          // Retardo de tiempo.
    LATB&=~(1<<RED);                    // Pin estará a nivel bajo.
    LATB|=(1<<INFRARED);                // Pin estará a nivel alto.
    antIR=ADC_GetConversion(SignalIR);  // Leemos el canal analógico del circuito INFRARED.
    __delay_ms(tiempo_espera);          // Retardo de tiempo.
    
    while (1)                           // Bucle infinito.
    {
        LATB|=(1<<RED);                 // Inicialmente el pin estará a nivel alto.
        LATB&=~(1<<INFRARED);           // Inicialmente el pin estará a nivel bajo.
        actR=ADC_GetConversion(SignalR);// Leemos el canal analógico del circuito RED.
        __delay_ms(tiempo_espera);      // Retardo de tiempo.
        LATB&=~(1<<RED);                // Pin estará a nivel bajo.
        LATB|=(1<<INFRARED);            // Pin estará a nivel alto.
        actIR=ADC_GetConversion(SignalIR);// Leemos el canal analógico del circuito INFRARED.
        
        if(subida==0)
        {
            vminR=antR;
            vminIR=antIR;
        }
        if(actR>antR)
        {
            subida++;                   // Incrementamos en una unidad la variable.
            pico=0;
            if(subida>20)
            {
                subida=20;
            }
        }
        else
        {
            if(subida==20)
            {
                vmaxR=antR;
                vmaxIR=actIR;
            }
            pico=0;
            if(subida>12)
            {
                BPM=(60000/((float)periodo));
                BPM_prom=(BPM_prom)*0.7+(BPM*(1-0.7));
                if(vminR>0 && vmaxR>0 && vminIR>0 && vmaxIR>0)
                {
                   ratioR=abs(log((float)(vminR/vmaxR)));
                   ratioIR=abs(log((float)(vminIR/vmaxIR)));
                   ratio_promR=(ratio_promR*0.7)+(ratioR*(1-0.7));
                   ratio_promIR=(ratio_promIR*0.7)+(ratioIR*(1-0.7));
                   ratio_total=(ratio_promIR/ratio_promR);
                   Spo2=110-(25*ratio_total);
                }
                Lcd_Set_Cursor(1,1);
                sprintf(Buffer_LCD,"%04.2f BPM",BPM_prom);
                Lcd_Write_String(Buffer_LCD);
                Lcd_Set_Cursor(2,1);
                sprintf(Buffer_LCD,"%04.2f Spo2",Spo2);
                Lcd_Write_String(Buffer_LCD);
                periodo=0;
                pico=100;
                subida=0;
            }
        }
        
        antR=actR;
        antIR=actIR;
        __delay_ms(tiempo_espera);
        periodo=periodo+tiempo_espera;
    }
}