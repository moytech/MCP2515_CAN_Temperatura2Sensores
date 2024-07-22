/*

Temperatura lm35 sensor1

Practicas CAN con módulo MCP2515  https://github.com/moytech

Este programa envía la temperatura de un sensor 1 LM35. 
Se envía por el protocolo CAN bus con ayuda del módulo MCP2515.
Se muestra en serial monitor y en un display con módulo I2C.

Autor: Moytech
github: https://github.com/moytech
Programa: Temperatura lm35 sensor1
Fecha: Julio 2024

*/

#include <SPI.h>
#include <mcp2515.h>

#define CS 10
int sensor1= A0;
int val1= 0;
float temp1;

struct can_frame datasend1;
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
  val1= analogRead(sensor1);                        //lectura de sensor
  temp1= ((val1* 5000.0) / 1024.0);                 //conversión a mV
  temp1= (temp1/ 10.0);                             //celsius
  datasend1.can_id= 0x11;                           //CAN can_id
  datasend1.can_dlc= 1;                             //1 byte
  datasend1.data[0]= (int) temp1;                   //temperatura en byte[0]
  mcp2515.sendMessage(&datasend1);                  //enviar datos

  Serial.println("Enviar temperatura sensor 1: ");  //imprimir en serial monitor
  Serial.println(datasend1.data[0]);

  delay(4000);                                      //esperar 5 seg.
}
