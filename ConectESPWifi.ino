#include <ESP8266WiFi.h> //Libreria de ESP8266 para conectar a WiFi
#include "ThingSpeak.h" //Libreria de ThingSpeak, para comunicar con los servicios 

/*Se necesita una Red Wifi con seguridad WPA2-PSK*/


const char* ssid     = "LG-K200 9088"; // Nombre de la red a la que vas a conectar
const char* password = "scandaiot"; //Contraseña de la red a la que te vas a conectar




void setup() {

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
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

