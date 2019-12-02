/* Copyright 2019, EETA 32 Prácticas Profesionalizantes
 * 
 * Alumno: Altamirano, Iván Alexis  
 *
 * All rights reserved.
 *
 * This file is part of "Proyecto Marbore".
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
/**
   SKETCH PARA MEDIR TEMPERATURA CON TERMOPAR Y MAX6675. MUESTRA EL RESULTADO
   DE LA MEDICION EN EL MONITOR SERIAL DE ARDUINO Y ADEMÁS LO DESPLIEGA EN UNA
   PANTALLA LCD DE 16X2.

   ESTE EJEMPLO USA LA LIBRERIA PARA EL MAX6675 DE ADAFRUIT.
*/
#include "LiquidCrystal.h"
#include "max6675.h"

// CONFIGURACION DE LOS PINES UTILIZADOS PARA LA COMUNICACIÓN CON EL MAX6675
#define CONFIG_TCGND_PIN      8   // ALIMENTACION GND
#define CONFIG_TCVCC_PIN      9   // ALIMENTACION VCC
#define CONFIG_TCSCK_PIN      10  // SPI SCK
#define CONFIG_TCCS_PIN       11  // SPI CS
#define CONFIG_TCDO_PIN       12  // SPI MISO

// CONSTRUCTOR PARA LA PANTALLA LCD 16X2
// AQUI SE CONFIGURAN LOS PINES PARA LA COMUNICACION CON LA PANTALLA
LiquidCrystal lcd(7 ,6 ,5 ,4 ,3 ,2 );// (rs, enable, d4, d5, d6, d7)
// OBJETO UTILIZADO PARA LA COMUNICACION CON EL MAX6675
MAX6675 thermocouple(CONFIG_TCSCK_PIN, CONFIG_TCCS_PIN, CONFIG_TCDO_PIN);

void setup() {
  // PREPARAR LA INTERFAZ SERIAL
  Serial.begin(9600);

  // IMPRIMR MENSAJE INICIAL A LA TERMINAL
  Serial.println(F("----------------------------------------------------"));
  Serial.println(F("      LA PEOR MISERIA ES CAER EN LA MODORRA DE       "));
  Serial.println(F("           NO HACER NADA PARA SALIR DE ELLA               "));
  Serial.println(F("----------------------------------------------------"));

  // USAR PINES DE ARDUINO PARA ALIMENTAR EL MODULO MAX6675
  pinMode(CONFIG_TCVCC_PIN, OUTPUT); digitalWrite(CONFIG_TCVCC_PIN, HIGH);
  pinMode(CONFIG_TCGND_PIN, OUTPUT); digitalWrite(CONFIG_TCGND_PIN, LOW);

  // INDICAMOS QUE TENEMOS CONECTADA UNA PANTALLA DE 16X2
  // IMPRIMIR MENSAJE INICIAL EN PANTALLA
  lcd.begin(40, 2);
  lcd.clear();
  lcd.print(F("            TERMOPAR ARDUINO"));
  lcd.setCursor(4, 1 );
  lcd.print(F("   PRACTICA PROFESIONALIZANTE"));

  // ESPERAR UN SEGUNDO
  delay(4000);
}

void loop() {
  // LEER EL TERMOPAR Y ALMACENAR EL VALOR EN UNA VARIABLE
  double t = thermocouple.readCelsius();

  // PRIMERO LIMPIAMOS LA PANTALLA Y LUEGO IMPRIMIMOS LA TEMPERATURA
  lcd.clear();
  lcd.print(F("        CONTROL DE TEMPERATURA"));
  lcd.setCursor( 15, 1 );
  lcd.print(t);

  // IMPRIMIR LA TEMPERATURA EN LA TERMINAL SERIAL
  Serial.print("C = ");
  Serial.println(t);

  // ESPERAR UN SEGUNDO ENTRE LAS LECTURAS
  delay(1000);
  }
 
