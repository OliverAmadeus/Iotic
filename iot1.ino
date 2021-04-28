//Incluimos las librerias para la conexión WiFi y para hacer solicitudes HTTP.
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

//Declaramos los parámetros de la red WiFi, el usuario y la contraseña.
const char* ssid = "SATCO-01D0CA";
const char* password = "AEEAF7AD";

void setup()
{
//Iniciamos la comunicación serial con el ordenador a una velocidad de 115200 baudios  
Serial.begin(115200);

//Iniciamos la conexión WiFi
Serial.print("conectando a ");
Serial.println(ssid);
WiFi.begin(ssid, password);

//Mientras no se conecte al Wifi, que imprimima "Esperando para conectar"
while(WiFi.status() != WL_CONNECTED)
{
    delay(500);
    Serial.println("Esperando para conectar");

}
  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("IP address:");
  Serial.println(WiFi.localIP());
}
//Iniciamos el loop
void loop()
{
/*Si está conectado al WiFi, que cree el objeto "http" de la clase HTTPClient
se le pasa el url a donde se va a enviar la solicitud, el encabezado el tipo
de contenido tiene que ser "application....." para que acepte valores del tipo
parameter1=value1&parameter2=value2&para...., hay otros tipos como "plaintext/html"
que son un texto y formato html, luego se usa el método POST para hacer la 
solicitud, se cierra la conexión.*/
  if(WiFi.status() == WL_CONNECTED){

    HTTPClient http;
    http.begin("http://192.168.0.154/entrada_datos.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    int httpCode = http.POST("serie=777&temp=27.25");
    String payload = http.getString();

    Serial.println(httpCode);
    Serial.println(payload);
    http.end();
  }
  else{
 //Si se pierde la conexión WiFi que escriba "Error en WiFi connection"   
    Serial.println("Error in WiFi connection");
  }
//Ponemos un delay para que  consulte cada 5 segundos.
  delay(5000);
}
