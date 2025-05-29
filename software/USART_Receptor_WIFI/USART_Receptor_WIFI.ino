/* ESP36 C6 MODO RECEPTOR Y WIFI
*/
#include "ThingSpeak.h"                       // Incluimos librería ThingSpeak para la comunicación con la WEB.
#include "WiFi.h"                             // Incluimos librería WiFi.
#include <LiquidCrystal.h>                    // Incluimos librería LCD.
LiquidCrystal lcd(12, 13, 9, 18, 19, 20);     // Pines de conexicón LCD RS,EN,D4,D5,D6,D7,

/* Vriables y arreglos globales */
char* ssid = "JorgeAPC2.4G";                  // SSID Nombre de la red (ROUTER).
char* password = "45126903@88";               // Contraseña de vuestro ROUTER.

unsigned long channelID =  2439669;           // ID de vuestro canal.
const char* WriteAPIKey = "XRNH44TK2W6ESGXA"; // Write API Key de vuestro canal.         
WiFiClient cliente;

/* Función principal y de configuración */
void setup()
{ 
  Serial.begin(9600);                         // Inicializamos la comunicación USART a 9600
  lcd.begin(16,2);                            // Inicializamos la LCD 16x2.
  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    lcd.setCursor(0,1);                       // Cursor fila, columna LCD.
    lcd.print(".");                           // Imprimimos en la LCD el valor de la variable.
  }
  lcd.println("WiFi Connected!");             // Imprimimos mensaje en la LCD.
  ThingSpeak.begin(cliente);                  // Inicializamos la comunicación con ThingSpeak.
}

/* Función buble infinito */
void loop()
{
  float dato1;                                // Variable de almacenamiento de dato transformado.
  dato1 = dato_salida();                      // Lectura del dato arreglado
  lcd.setCursor(0,1);                         // Cursor fila, columna LCD.
  lcd.print(dato1);                           // Imprimimos en la LCD el valor de la variable.
  ThingSpeak.setField (1,dato1);              // Enviamos el dato 1 por WiFi a ThingSpeak.
  //ThingSpeak.setField (2,uvIntensity);      // Enviamos el dato 2 por WiFi a ThingSpeak.
  ThingSpeak.writeFields(channelID,WriteAPIKey);// Para enviar los datos a ThingSpeak se necesita declarar el ID y el Key.
  delay(1000);                                // Retardo 1s. 
}

/* Función dato de salida */
float dato_salida()       
{       
  float dato_flotante = 0;                    // Constructor de dato enviado 
  char vector[20];                            // Variable de almacenamiento de dato leido por serial   
  int flag = 0;                               // Flag de entrada de bucle while
  
  while (flag == 0)                           // Bucle mientras el flag sea menor que 1
  {  
    if (Serial.available())                   // Lectura del puerto serial abierto
    {
      delay(100);                             // Retardo 100ms.
      int i = 0;                              // Variable auxiliar de construccion de vector
      while (Serial.available() > 0)          // Lectura mientras el buffer tenga valores.
      {
        char inByte = Serial.read();          // Variable de almacenamiento de entrada de datos
        vector[i] = inByte;                   // Vector de almacenamiento para construccion de dato
        i+=1;                                 // Incrementamos en una unidad la variable.
        flag=1;                               // Ponenos a 1 la variable.            
      }
      
      dato_flotante = atof(vector);           // Conversión del vector de char a float
      memset(vector, 0, sizeof(vector));      // Limpia los datos ingresados al vector
    }
  } 
  
  return dato_flotante;                       // Retorna el valor arreglado 
}
