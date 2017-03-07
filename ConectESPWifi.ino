#include <ESP8266WiFi.h> //Libreria de ESP8266 para conectar a WiFi
#include <ThingSpeak.h> //Libreria de ThingSpeak, para comunicar con los servicios 
#include <SHT1X.h>


/*Se necesita una Red Wifi con seguridad WPA2-PSK*/
<<<<<<< Updated upstream
const char* ssid     = "TVBmobile"; //Nombre de la red a la que vas a conectar
const char* password = "scanda01"; //Contraseña de la red a la que te vas a conectar
=======
const char* ssid     = "LG-K200 9088"; // Nombre de la red a la que vas a conectar
const char* password = "scandaiot"; //Contraseña de la red a la que te vas a conectar
>>>>>>> Stashed changes


/*Se accede a estos datos en ThingSpeak > Channels > My Channels > "Nombre del Canal" > Data Import / Export*/
unsigned long myChannelNumber = 237213; //Channel ID [Sacado de ThingSpeak]
const char * myWriteAPIKey = "9L0P9JF4KKDT6G9Q"; //En API Request [Sacado de ThingSpeak]

int status = WL_IDLE_STATUS;
WiFiClient  client;

//variables de temperatura
float tempC = 0;
float humidity = 0;

//crear instancia de la libreria de SHT10
SHT1x sht10(8, 9);


void setup() {

  randomSeed(42); //Para prueba en el canal, semilla donde empieza el Random

  Serial.begin(9600); //Inicio de monitor Serial, !!!!Herramientas>Debug Port>"Serial"
  delay(1000); //Espera

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

  /*Si la conexión fue exitosa*/
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); //Muestra la dirección IP de la red WiFi a la que está conectado


  int prub = random(17, 41); //Valor Random generado entre 17 y 41

  Serial.print("Valor de prueba: ");
  Serial.println(prub);
  readSensor();
  printOutTemp();

  /*Mandar información a ThingSpeak=TS*/
  // En cada canal de TS se pueden llenar hasta 8 campos diferentes
  ThingSpeak.writeField(myChannelNumber,   1 ,    prub  ,   myWriteAPIKey);
  //   ^     |     ^   |       ^       |   ^  |       ^      |    ^
  //Libreria | escribir| numero canal  |campo |valor a enviar| API KEY
  delay(20000); // La suscripción de ThingSpeak actual, acepta datos cada 15 segundo



}
void readSensor()
{
  // Read values from the sensor
  tempC = sht10.readTemperatureC();
  humidity = sht10.readHumidity();
}
//-------------------------------------------------------------------------------------------
void printOutTemp()
{
  Serial.print(" Temp = ");
  //Serial.print(tempF);
  //Serial.print("F, ");
  Serial.print(tempC);
  Serial.println("C");
  Serial.print(" Humidity = ");
  Serial.print(humidity);
  Serial.println("%");
}
