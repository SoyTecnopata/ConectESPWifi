#include <ESP8266WiFi.h> //Libreria de ESP8266 para conectar a WiFi
#include <ThingSpeak.h> //Libreria de ThingSpeak, para comunicar con los servicios 
#include <SHT1X.h>

/*Se necesita una Red Wifi con seguridad WPA2-PSK*/
const char* ssid     = "TVBmobile"; // Nombre de la red a la que vas a conectar
const char* password = "scanda01"; //Contraseña de la red a la que te vas a conectar


/*Se accede a estos datos en ThingSpeak > Channels > My Channels > "Nombre del Canal" > Data Import / Export*/
unsigned long myChannelNumber = 237842; //Channel ID [Sacado de ThingSpeak]
const char * myWriteAPIKey = "I9YLJRBVDOK86VMY"; //En API Request [Sacado de ThingSpeak]

int status = WL_IDLE_STATUS;
WiFiClient  client;

float tempC = 0;
float tempF = 0;
float humidity = 0;
int current = 0;

SHT1x sht15(14, 16);



//__________________________
unsigned long previousMillis = 0;
const long interval = 20000;

void setup() {

  randomSeed(42); //Para prueba en el canal, semilla donde empieza el Random

  Serial.begin(9600); //Inicio de monitor Serial, !!!!Herramientas>Debug Port>"Serial"
  delay(10000); //Espera

  /*Conexion a Red Wifi*/

  Serial.println();
  Serial.println();
  Serial.print("Connecting to "); //Desplegado en el monitor Serial
  Serial.println(ssid);  //Nombre de la red en la cual se va a conectar

  WiFi.begin(ssid, password); //Inicio de conexión mediante la libreria

  ThingSpeak.begin(client);

  while (WiFi.status() == WL_CONNECTED) {//Revisa que no haya una conexión exitente
    delay(500); //Espera para conectar
    Serial.print("."); //Puntitos en el Serial
    status = WiFi.begin(ssid, password);

    // wait 10 seconds for connection:
    delay(10000);
  }

  /*Si la conexión fue exitosa*/
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); //Muestra la dirección IP de la red WiFi a la que está conectado
}


void loop() {
  unsigned long currentMillis = millis();
  /*Si la conexión fue exitosa*/
  /*Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP()); //Muestra la dirección IP de la red WiFi a la que está conectado*/


   //Valor Random generado entre 17 y 41


  readSensor();


  if (Serial.available() > 0)
  {
    current = Serial.parseInt();
  }
  else
  {
    current = random(17, 41);
    }

  printOut();


  if (currentMillis - previousMillis >= interval) {
    //reniciar el contador de milisegundos
    previousMillis = currentMillis;

    /*Mandar información a ThingSpeak=TS*/
    // En cada canal de TS se pueden llenar hasta 8 campos diferentes
    ThingSpeak.setField(1, tempC);
    ThingSpeak.setField(2, humidity);
    ThingSpeak.setField(3, current);
    ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

    Serial.println("//////////////////////////////////////////////////////////");
    Serial.println("/////////////////// Enviado a ThingSpeak /////////////////");
    printOut();
    Serial.println("//////////////////////////////////////////////////////////");


  }





}

void readSensor()
{
  // Read values from the sensor
  //Serial.print("Sensando");
  tempC = sht15.readTemperatureC();
  tempF = sht15.readTemperatureF();
  humidity = sht15.readHumidity();
  //Serial.print("Sensado listo");
}
//-------------------------------------------------------------------------------------------
void printOut()
{
  Serial.print("Temp = ");
  //Serial.print(tempF);
  //Serial.print("F, ");
  Serial.print(tempC, 5);
  Serial.print("C");
  Serial.print("          Humidity = ");
  Serial.print(humidity, 5);
  Serial.print("%");

  Serial.print("          Corriente = ");
  Serial.print(current);
  Serial.println("A");
}
