#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, PIN, NEO_GRB + NEO_KHZ800);
#define SSID "XXXXXXX"      //your wifi ssid here
#define PASS xxxxxxxx""   //your wifi wep key here
SoftwareSerial dbgSerial(10, 11); // RX, TX
char myChar;

uint32_t color = 0x000022;
void setup() {
  // Open serial communications for WiFi module:
  Serial.begin(115200);
  // Set time to wait for response strings to be found
  Serial.setTimeout(5000);
 dbgSerial.begin(19200); //can't be faster than 19200 for softserial
dbgSerial.println("ESP8266 LED Demo");
  delay(100);
  Serial.println("AT+RST");    
  if(Serial.find("ready"))
  {
    dbgSerial.println("Module is ready");
    delay(1000);
    //connect to the wifi
    boolean connected=false;
    for(int i=0;i<5;i++)
    {
      if(connectWiFi())
      {
        connected = true;
        break;
      }
    }
    if (!connected)
    {
      //die
      while(1);
    }
 
    delay(5000);
    //set the single connection mode
    Serial.println("AT+CIPMUX=1");
    delay(1000);
    dbgSerial.println("Starting TCP Server");
    Serial.println("AT+CIPSERVER=1,8266");
  }
  else
  {
    dbgSerial.println("Module didn't respond.");
    delay(100);
   
    //serial loop mode for diag
    while(1){
      while (dbgSerial.available()) {
        myChar = dbgSerial.read();
        Serial.print(myChar);
      }
 
      while (Serial.available()) {
        myChar = Serial.read();
        delay(10);
        dbgSerial.print(myChar);
      }
    }
  }
  dbgSerial.println("waiting for connection...");



strip.begin();
  strip.show(); // Initialize all pixels to 'off'
colorWipe(color,0);

}

void loop() {
  
  if (Serial.available()>0){
    if(Serial.find("LED")){
    setLED();
  }
  }

  
}
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}
void setLED(){

  int red = Serial.parseInt();
  int green = Serial.parseInt();
  int blue = Serial.parseInt();
  dbgSerial.print("LED set. Red: ");
  dbgSerial.print(red);
  dbgSerial.print(" Green ");
  dbgSerial.print(green);
  dbgSerial.print(" Blue ");
  dbgSerial.println(blue);
  colorWipe(strip.Color(red,green,blue),200);

}
boolean connectWiFi()
{
  Serial.println("AT+CWMODE=1");
  String cmd="AT+CWJAP=\"";
  cmd+=SSID;
  cmd+="\",\"";
  cmd+=PASS;
  cmd+="\"";
  dbgSerial.println(cmd);
  Serial.println(cmd);
  delay(2000);
  if(Serial.find("OK"))
  {
    dbgSerial.println("OK, Connected to WiFi.");
    return true;
  }
  else
  {
    dbgSerial.println("Can not connect to the WiFi.");
    return false;
  }            
}
