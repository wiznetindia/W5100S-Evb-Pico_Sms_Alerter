/*
  DHCP-based IP printer
  This sketch uses the DHCP extensions to the Ethernet library
  to get an IP address via DHCP and print the address obtained.
  using an Arduino Wiznet Ethernet shield.
  Circuit:
   Ethernet shield attached to pins 10, 11, 12, 13
  created 12 April 2011
  modified 9 Apr 2012
  by Tom Igoe
  modified 02 Sept 2015
  by Arturo Guadalupi
 */

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

//if DHCP fails, use a static IP
// within proveder's router LAN!!!
IPAddress ip(192, 168, 0, 177); //ENTER YOUR IP ADDRESS HERE!!

// Initialize the Ethernet client library
EthernetClient client;

//thingspeak serverTS
char serverTS[] = "api.thingspeak.com";

//API key for the Thingspeak ThingHTTP already configured
const String apiKey = "OUX962D22SIGFJAT";

//the RECIPIENT phone number the message should be sent to
const String sendToNumber = "+918147888734";
//
// digital pins
/* Arduino uses digital pins 10, 11, 12, and 13 (SPI) 
   to communicate with the W5100 on the ethernet shield.
   These pins cannot be used for general i/o. 
   
*/
int sensor = 26;              // the pin that the sensor is atteched to
bool flood = false;            
int val = 0;
// 
// output pins to visualize 
// important states:
int networkOK = 19;           // green LED
int networkDown = 16;         // RED LED
int smsSent = 14;             // Yellow LED
int sentCount=0;

bool etherNet = false;
 //

void setup() {
  // You can use Ethernet.init(pin) to configure the CS pin
  //Ethernet.init(10);  // Most Arduino shields
  //Ethernet.init(5);   // MKR ETH shield
  //Ethernet.init(0);   // Teensy 2.0
  //Ethernet.init(20);  // Teensy++ 2.0
  //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
  //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet
    Ethernet.init(17);  // WIZnet W5100S-EVB-Pico

   pinMode(sensor, INPUT);    // initialize sensor as an input'
   pinMode(networkOK, OUTPUT);
   pinMode(networkDown, OUTPUT);
   pinMode(smsSent, OUTPUT);
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  // connect the device to wired LAN
  Ethernet_init();
}

void loop() {
  if ( etherNet == false )
  {
     Serial.println("Check Ethernet...");
     return;
  }
  //
  // device is on the network
  // continue
   val = digitalRead(sensor);   // read sensor value
   Serial.println(val);
   delay(1000);
   // check if the sensor is HIGH
   if (val == HIGH) 
   {           
     // flood occured!
     // send SMS right away

     // send up to 2 text messages!
     if (sentCount < 2)
     {
        sendSMS(sendToNumber, "My basement is flooded!");
        delay(5000);
        sentCount += 1;
       
     }
     if (flood == false) {
       Serial.println("Basement is flooded!"); 
       flood = true;        
     } 
         
  }// val testing
}
//------------------------------------------------------------
//
void sendSMS(String number,String message)
{
  // Make a TCP connection to remote host
  if (client.connect(serverTS, 80))
  {
    Serial.print("connected to ");
    Serial.println(client.remoteIP());
    // Make a HTTP request:
    client.println("GET /apps/thinghttp/send_request?api_key=OUX962D22SIGFJAT&number=+918147888734&message=%27my%20Basement%20is%20flooded%27");
    client.println("Host: api.thingspeak.com");
    client.println("Connection: close");
    client.println();
  }
  else
  {
    Serial.println(F("Connection failed"));
  } 

  String reply ="";
  // Check for a response from the server, and route it
  // out the serial port.
  while (client.connected())
  {
    if ( client.available() )
    {
      char c = client.read();
      Serial.print(c);
      //-------------------------------------------
      reply = String(reply + c);
      if(reply.indexOf("><DateSent/><") > 0)
      { smsSent = HIGH; }
             
      if (reply.length() > 400)
      { reply="";  }  
      //--------------------------------------------------    
    }
  }
  Serial.println();
  if(smsSent == HIGH)
  { Serial.println("Text message sent successfully.");  }
  else
  {
     Serial.println("!!!!!!!!! no Text message sent");
     //Serial.println(reply);  
     Serial.println("==================");   
  }
  Serial.println();
  client.stop();
}

//---------------------------------------------------
//
void Ethernet_init()
{
    etherNet = true;
    //--------------------------------------------------
   //
    // check for Ethernet cable
    //
    
  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1); // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  } else {
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
}
