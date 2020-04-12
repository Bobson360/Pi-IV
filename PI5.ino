
#include <Adafruit_NeoPixel.h>

#include <WiFi.h>
#include <PubSubClient.h>

#define TOPICO_SUBSCRIBE_LED    "topico_liga_desliga_led_bobson278"
#define ID_MQTT                 "esp32_mqtt"

#ifdef __AVR__
 #include <avr/power.h> 
#endif

#ifdef ESP32
  #define PIN        2 
#elif ESP8266
  #define PIN        D0
#else 
  #define PIN        6
#endif


#define NUMPIXELS 150 // Total de led na fita

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 250 // Time (in milliseconds) to pause between pixels

const char* SSID = "PeCRo_2.4"; // SSID / nome da rede WI-FI que deseja se conectar
const char* PASSWORD = "Pedro@2017"; // Senha da rede WI-FI que deseja se conectar

//Variáveis e objetos globais
WiFiClient espClient; // Cria o objeto espClient
PubSubClient MQTT(espClient); // Instancia o Cliente MQTT passando o objeto espClient
 
/* Prototypes */
void initWiFi(void);
void initMQTT(void);
void mqtt_callback(char* topic, byte* payload, unsigned int length);
void reconnectMQTT(void);
void reconnectWiFi(void);
void VerificaConexoesWiFIEMQTT(void);
int count = 0;
void setup() {

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  Serial.begin(115200);
}
boolean red = false;


int intRed = 0;
int intGreen = 0;
int intBlue = 0;

void loop() {
//  pixels.clear(); // Set all pixel colors to 'off'

   int ledloop = NUMPIXELS -1;
   
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
    
//    Serial.println("Acendendo o pixel " + (String)i);
//    Serial.println("Valor do count " + (String)count);
//    for(int j = ledloop; j >= count; j--){
//      
//        pixels.setPixelColor(j, pixels.Color(0, 150, 0));
//        pixels.show();
//        delay(10);
//        pixels.setPixelColor(j, pixels.Color(0, 0, 0));
//        delay(10);
//    }
    
    pixels.setPixelColor(i, pixels.Color(intRed, count, 0));
//  delay(DELAYVAL);
    pixels.show();   // Send the updated pixel colors to the hardware.
  }
//    for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
//      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
//    pixels.show();   // Send the updated pixel colors to
//    }
    Serial.print(count);
    Serial.print(" ");
    Serial.println(intRed);
    count++;
    if(count == 255){
      red = true;
    }
    if(red)
      intRed++;
  }
  
