
//bibliotecas
#include <Stepper.h>
#include <Wire.h>
#include "RTClib.h"

//iniciando rtc
RTC_DS1307 rtc;

//Inciando motor
const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 6,9,10,11);

//variaveis para o relogio
int hora;
int minuto;
int segundo;

// variaveis para puxar do aplicativo
int horaA, minutoA, segundoA;

int horaB, minutoB, segundoB;

int horaC, minutoC, segundoC;

int quant;

void setup() {
  rtc.begin();              // Inicia o módulo RTC
  myStepper.setSpeed(5);    // Define a velocidade para 5 rpm:
  Serial.begin(9600);
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // seta a data para hora e dia da compialção
  
}

void loop() {
  DateTime now = rtc.now();
  //colocando as variaveis para pegar a hora do relogio
  hora = now.hour();
  minuto = now.minute();
  segundo = now.second();

  //Comparações do horario
  if((hora == horaA) && (minuto == minutoA) && (segundo == segundoA))
  {
    for(int i = 0; i < quant; i++) //for para o motor gira iguial a quantidade de quant inserida
    {
      myStepper.step(2048);
      Serial.println(i);
     }
     Serial.println("Alimentação concluida");
   }

   if((hora == horaB) && (minuto == minutoB) && (segundo == segundoB))
  {
    for(int i = 0; i < quant; i++)
    {
      myStepper.step(2048);
      Serial.println(i);
     }
     Serial.println("Alimentação concluida");
   }

   if((hora == horaC) && (minuto == minutoC) && (segundo == segundoC))
  {
    for(int i = 0; i < quant; i++) 
    {
      myStepper.step(2048);
      Serial.println(i);
     }
     Serial.println("Alimentação concluida");
   }

  // codigo para informar a hora completa
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  delay(1000);
  
}
