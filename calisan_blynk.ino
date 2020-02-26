#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

char auth[] = "laW-M6U_XhCwvvt4vZEQsY09zhlkNqL2"; // Kendi anahtarınızı buraya girin.


char ssid[] = "GPARK2"; //WiFi ID 
char pass[] = "08120202"; //WiFi Şifre


#define PIN_UPTIME V6   //SuperChart için sanal v6 pinini kullanıyoruz.
BLYNK_READ(PIN_UPTIME)
{
  Blynk.virtualWrite(PIN_UPTIME, millis() / 1000); //Blynk app'ine v6 sanal porta yazdırma işlemini yapıyoruz. 
}

BlynkTimer timer;

#include <SoftwareSerial.h>

SoftwareSerial EspSerial(2, 3); // RX, TX   //ESP8266-01 haberleşmesi için yazdık.

// Your ESP8266 baud rate:
#define ESP8266_BAUD 115200

ESP8266 wifi(&Serial);

float temp;

void myTimerEvent()
{
  int analogValue = analogRead(A0); //Analog (A0) pininden veriyi LM35'den alıyoruz.
  float millivolts = (analogValue * 0.48828125); //Gelen analog verimizi Celcius cinsine çeviriyoruz.
  Blynk.virtualWrite(V5, millivolts); //Blynk'e V5 sanal pininden Gauge adlı göstergeye sıcaklık değerimizi Celcius olarak gönderiyoruz.
}


void setup()
{
 // Seri haberleşmeyi başlatıyoruz.
 Serial.begin(9600);
 delay(10);
 // ESP8266 BAUD ayarladık.
 Serial.begin(ESP8266_BAUD);
 delay(10);
 Blynk.begin(auth, wifi, ssid, pass); //Blynk ile haberleşme standartları verileri sağladık.
 timer.setInterval(1000L, myTimerEvent);
}


void loop()
{
 Blynk.run();
 timer.run();
}
