/*

Temperatura lm35 sensor2

Practicas CAN con módulo MCP2515  https://github.com/moytech

Este programa envía la temperatura de un sensor 2 LM35. 
Se envía por el protocolo CAN bus con ayuda del módulo MCP2515.
Se muestra en serial monitor y en un display con módulo I2C.

Autor: Moytech
github: https://github.com/moytech
Programa: Temperatura lm35 sensor2
Fecha: Julio 2024

*/

#include <SPI.h>
#include <mcp2515.h>

#define CS 10
int sensor2= A0;
int val2= 0;
float temp2;

struct can_frame datasend2;
MCP2515 mcp2515(CS);

void setup() 
{
  Serial.begin(9600);                               //iniciar serial monitor
  SPI.begin();                                      //iniciar SPI
  mcp2515.reset();                                  //reset MCP2515
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);        //configuración CAN bus
  mcp2515.setNormalMode();                          //modo normal
}

void loop() 
{
  val2= analogRead(sensor2);                        //lectura de sensor 2
  temp2= ((val2* 5000.0) / 1024.0);                 //conversión mV
  temp2= (temp2/ 10.0);                             //celsius
  datasend2.can_id= 0x15;                           //CAN id
  datasend2.can_dlc= 1;                             //1 byte
  datasend2.data[0]= (int) temp2;                   //temperatura en byte[0]
  mcp2515.sendMessage(&datasend2);                  //enviar datos

  Serial.println("Enviar temperatura de sensor 2: ");
  Serial.println(datasend2.data[0]);                 //imprimir en serial monitor

  delay(3000);                                      //esperar 3 seg. 
}
