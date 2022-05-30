// Conectar e receber informação do esp para o navegador

//Blibliotecas
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <Hash.h>
#include <FS.h>
#include <ESPAsyncWebServer.h>
#include <Stepper.h>
#include <Wire.h>
#include "RTClib.h"
#include "index_html.h"

//iniciando rtc
RTC_DS1307 rtc;

//D1 = 5 é SCL D2 = 4 é SDA

//pinos para o motor
#define IN1 13
#define IN2 15
#define IN3 14
#define IN4 12

//Inciando motor
const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, IN1,IN3,IN2,IN4);

//variaveis para o relogio
int hora;
int minuto;
int segundo;

//variavel do giro
int quant = 1;

//var navegador
int horaDois = 0;
int horaUm = 0;
int horaClient = 0;
int minutoClient = 0;

AsyncWebServer server(80);

// Conectar a Rede
const char* ssid = "Red";
const char* password = "12345678";

const char* PARAM_INT = "inputIntH";
const char* PARAM_INT2 = "inputIntM";

//const char index_html[] PROGMEM = R"=====(

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

String readFile(fs::FS &fs, const char * path){
  Serial.printf("Reading file: %s\r\n", path);
  File file = fs.open(path, "r");
  if(!file || file.isDirectory()){
    Serial.println("- empty file or failed to open file");
    return String();
  }
  Serial.println("- read from file:");
  String fileContent;
  while(file.available()){
    fileContent+=String((char)file.read());
  }
  file.close();
  Serial.println(fileContent);
  return fileContent;
}

void writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Writing file: %s\r\n", path);
  File file = fs.open(path, "w");
  if(!file){
    Serial.println("- failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Serial.println("- file written");
  } else {
    Serial.println("- write failed");
  }
  file.close();
}

// Replaces placeholder with stored values
String processor(const String& var){
  //Serial.println(var);
  if(var == "inputIntH"){
    return readFile(SPIFFS, "/inputIntH.txt");
  }
  else if(var == "inputIntM"){
    return readFile(SPIFFS, "/inputIntM.txt");
  }
  return String();
}

void setup() {
  rtc.begin();              // Inicia o módulo RTC
  myStepper.setSpeed(5);    // Define a velocidade para 5 rpm:
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // seta a data para hora e dia da compialção
  
  Serial.begin(115200);
  #ifdef ESP32
    if(!SPIFFS.begin(true)){
      Serial.println("An Error has occurred while mounting SPIFFS");
      return;
    }
  #else
    if(!SPIFFS.begin()){
      Serial.println("An Error has occurred while mounting SPIFFS");
      return;
    }
  #endif

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed!");
    return;
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Send web page with input fields to client
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  // Send a GET request to <ESP_IP>/get?inputString=<inputMessage>
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    
    // GET inputString value on <ESP_IP>/get?inputString=<inputMessage>
    if (request->hasParam(PARAM_INT)) {
      inputMessage = request->getParam(PARAM_INT)->value();
      writeFile(SPIFFS, "/inputIntH.txt", inputMessage.c_str());
    }
    // GET inputInt value on <ESP_IP>/get?inputInt=<inputMessage>
    else if (request->hasParam(PARAM_INT2)) {
      inputMessage = request->getParam(PARAM_INT2)->value();
      writeFile(SPIFFS, "/inputIntM.txt", inputMessage.c_str());
    }
    else {
      inputMessage = "Nada enviado";
    }
    Serial.println(inputMessage);
    request->send(200, "text/text", inputMessage);
  });
  server.onNotFound(notFound);
  server.begin();
}

void loop() {
  
  DateTime now = rtc.now();
  //colocando a hora atual para a hora do relogio
  hora = now.hour();
  minuto = now.minute();
  segundo = now.second();*/
  
  //variaves do navegador
  horaClient = readFile(SPIFFS, "/inputIntH.txt").toInt();
  minutoClient = readFile(SPIFFS, "/inputIntM.txt").toInt(); 
  horaUm = horaClient + 3;
  horaDois = horaClient - 3;

  Serial.print("Horas Client: ");
  Serial.println(horaClient);
  Serial.print("Minutos do Cliente: ");
  Serial.println(minutoClient);
  Serial.print("H2: ");
  Serial.println(horaDois);
  Serial.print("H1: ");
  Serial.println(horaUm);
  delay(1000); 
  
  //Comparações do horario
  if((hora == horaClient) && (minuto == minutoClient) && (segundo == 00))
  {
    for(int i = 0; i < quant; i++) //for para o motor gira iguial a quantidade de quant inserida
    {
      myStepper.step(2048);
      Serial.println(i);
     }
     Serial.println("Alimentação concluida");
   }

   if((hora == horaUm) && (minuto == minutoClient) && (segundo == 00))
  {
    for(int i = 0; i < quant; i++)
    {
      myStepper.step(2048);
      Serial.println(i);
     }
     Serial.println("Alimentação concluida");
   }

   if((hora == horaDois) && (minuto == minutoClient) && (segundo == 00))
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
