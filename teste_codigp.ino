#include <Stepper.h>
#include <Wire.h>
#include "RTClib.h"

const int stepsPerRevolution = 64;;
Stepper myStepper(stepsPerRevolution, 6, 9, 10, 11);

int hora;
int minuto;
int segundo;

int horaA = 22;
int minutoA = 3;
int segundoA = 30;

int quant = 2;

RTC_DS1307 rtc;

void setup () {

  rtc.begin();              // Inicia o módulo RTC
  myStepper.setSpeed(5);    // Define a velocidade para 5 rpm:
  Serial.begin(9600);
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // UNCOMMENT TO SET TIME & DATE TO THAT AT COMPILATION.;

}

void loop () {
DateTime now = rtc.now();

hora = now.hour();
minuto = now.minute();
segundo = now.second();

if((hora == horaA) && (minuto == minutoA) && (segundo == segundoA)){
Serial.println("Alimentando");
for (int i = 0; i < quant; i++){
myStepper.step(64);
Serial.println(i);
}

}

Serial.print(now.day(), DEC);
Serial.print('/');
Serial.print(now.month(), DEC);
Serial.print('/');
Serial.print(now.year(), DEC);
Serial.print(' ');
Serial.print(now.hour(), DEC);
Serial.print(':');
Serial.print(now.minute(), DEC);
Serial.print(':');
Serial.print(now.second(), DEC);
Serial.println();

Serial.println();
delay(1000);
}
