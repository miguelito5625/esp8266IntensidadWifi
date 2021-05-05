#include "ESP8266WiFi.h"

const int RSSI_MAX =-50;// define maximum strength of signal in dBm
const int RSSI_MIN =-100;// define minimum strength of signal in dBm

const int displayEnc=1;// set to 1 to display Encryption or 0 not to display

void setup() {
  Serial.begin(115200);
  Serial.println("Escaner intensidad Wifi");
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(2000);

  Serial.println("Inicializacion completada");
}

void loop() {
  Serial.println("Inicia escaneo");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("Termina escaneo");
  if (n == 0) {
    Serial.println("No se encontraron redes wifi");
  } else {
    Serial.print(n);
    Serial.println(" redes encontradas");
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(")");
      Serial.print(WiFi.SSID(i));// SSID

                  
      Serial.print(" " + WiFi.RSSI(i));//Signal strength in dBm  
      Serial.print("dBm (");

      
      Serial.print(dBmtoPercentage(WiFi.RSSI(i)));//Signal strength in %  
     Serial.print("% )"); 
      if(WiFi.encryptionType(i) == ENC_TYPE_NONE)
      {
          Serial.println(" <<***Abierta***>>");        
      }else{
          Serial.println();        
      }

      delay(10);
    }
  }
  Serial.println("");

  // Wait a bit before scanning again
  delay(5000);
  WiFi.scanDelete();  
}// loop


int dBmtoPercentage(int dBm)
{
  int quality;
    if(dBm <= RSSI_MIN)
    {
        quality = 0;
    }
    else if(dBm >= RSSI_MAX)
    {  
        quality = 100;
    }
    else
    {
        quality = 2 * (dBm + 100);
   }

     return quality;
}//dBmtoPercentage 