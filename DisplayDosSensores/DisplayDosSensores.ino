/*

Display lcd 2 sensores

Practicas CAN con módulo MCP2515  https://github.com/moytech

Este programa recibe la temperatura de dos sensores LM35. 
Se recibe por el protocolo CAN bus con ayuda del módulo MCP2515.
Se muestra en serial monitor y en un display con módulo I2C.

Autor: Moytech
github: https://github.com/moytech
Programa: Display lcd 2 sensores
Fecha: Julio 2024

*/

#include <SPI.h>
#include <mcp2515.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define CS 10
int temprec, id;

struct can_frame datareceive;
MCP2515 mcp2515(CS);

void setup() 
{
  Serial.begin(9600);                                             //iniciar serial monitor
  SPI.begin();                                                    //iniciar SPI
  mcp2515.reset();                                                //reset MCP2515
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);                      //configuración CAN bus
  mcp2515.setNormalMode();                                        //modo normal
  lcd.init();                                                     //iniciar lcd
  lcd.backlight();                                                //led lcd on
}

void loop() 
{
  if(mcp2515.readMessage(&datareceive)== MCP2515::ERROR_OK)
  {
    temprec= datareceive.data[0];                                 //temperatura
    id= datareceive.can_id;                                       //CAN id
    if(id== 0x11)                                                 //si el id
    {
      lcd.setCursor(0, 0);                                        //configuración lcd
      lcd.print("Sensor 1: ");
      lcd.print(temprec);
      lcd.print(" C");

      Serial.println("Temperatura del sensor 1: ");               //imprimir en serial monitor
      Serial.println(temprec);
    }

    if(id== 0x15)                                                 //si el id
    {
      lcd.setCursor(0, 1);                                        //configuración lcd
      lcd.print("Sensor 2: ");
      lcd.print(temprec);
      lcd.print(" C");

      Serial.println("Temperatura del sensor 2: ");               //imprimir en serial monitor
      Serial.println(temprec);
    }
  }
}
