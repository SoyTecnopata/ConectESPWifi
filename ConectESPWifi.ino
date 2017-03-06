#include <ESP8266WiFi.h> //Libreria de ESP8266 para conectar a WiFi
#include <ThingSpeak.h> //Libreria de ThingSpeak, para comunicar con los servicios 

/*Se necesita una Red Wifi con seguridad WPA2-PSK*/
const char* ssid     = "LG-K200 9088"; // Nombre de la red a la que vas a conectar
const char* password = "scandaiot"; //Contraseña de la red a la que te vas a conectar


/*Se accede a estos datos en ThingSpeak > Channels > My Channels > "Nombre del Canal" > Data Import / Export*/
unsigned long myChannelNumber = 235719; //Channel ID [Sacado de ThingSpeak]
const char * myWriteAPIKey = "N07LKACOYSPDTB05"; //En API Request [Sacado de ThingSpeak]


void setup() {

  randomSeed(42); //Para prueba en el canal, semilla donde empieza el Random

  Serial.begin(9600); //Inicio de monitor Serial, !!!!Herramientas>Debug Port>"Serial"
  delay(10); //Espera

  /*Conexion a Red Wifi*/

  Serial.println();
  Serial.println();
  Serial.print("Connecting to "); //Desplegado en el monitor Serial
  Serial.println(ssid);  //Nombre de la red en la cual se va a conectar


  WiFi.begin(ssid, password); //Inicio de conexión mediante la libreria

  while (WiFi.status() != WL_CONNECTED) {//Revisa que no haya una conexión exitente
    delay(500); //Espera para conectar
    Serial.print("."); //Puntitos en el Serial
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


  /*Mandar información a ThingSpeak=TS*/
  // En cada canal de TS se pueden llenar hasta 8 campos diferentes
  ThingSpeak.writeField(myChannelNumber,   1 ,    prub  ,   myWriteAPIKey);
  //   ^     |     ^   |       ^       |   ^  |       ^      |    ^
  //Libreria | escribir| numero canal  |campo |valor a enviar| API KEY
  delay(20000); // La suscripción de ThingSpeak actual, acepta datos cada 15 segundo



}

