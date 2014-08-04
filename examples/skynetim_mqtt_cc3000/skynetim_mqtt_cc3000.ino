/*
 *                SSSSS  kk                            tt
 *               SS      kk  kk yy   yy nn nnn    eee  tt
 *                SSSSS  kkkkk  yy   yy nnn  nn ee   e tttt
 *                    SS kk kk   yyyyyy nn   nn eeeee  tt
 *                SSSSS  kk  kk      yy nn   nn  eeeee  tttt
 *                               yyyyy
 *
 * SkynetClient for http://skynet.im, OPEN COMMUNICATIONS NETWORK & API FOR
 * THE INTERNET OF THINGS.
 *
 * This sketch uses the MQTT library to connect to skynet. It sends a message
 * on successful connection and logs data every second.
 *
 * Requires our fork of the MQTT PubSubClient https://github.com/jacobrosenthal/pubsubclient
 * You can receive larger skynet messages by increasing MQTT_MAX_PACKET_SIZE in 
 * PubSubClient.h from 128 to something like 256
 *
 * Should work with any cc3000 shield or breakout like Adafruit or Sparkfun:
 * https://www.sparkfun.com/products/12071
 *
 * However no matter which you choose, we have a requirement on the Sparkfun
 * library: https://github.com/sparkfun/SFE_CC3000_Library/
 *
 * Remember not to mess with wifis's unavailable pins (look up on your manufacturers site)
 *
 * You will notice we're using F() in Serial.print. It is covered briefly on
 * the arduino print page but it means we can store our strings in program
 * memory instead of in ram.
 *
 */
 
#include <SPI.h>
#include <SFE_CC3000.h>
#include <SFE_CC3000_Client.h>
#include <PubSubClient.h>

// Pins
#define CC3000_INT      2   // Needs to be an interrupt pin (D2/D3) //Adafruit is 3
#define CC3000_EN       7   // Can be any digital pin //Adafruit is 5
#define CC3000_CS       10  // Preferred is pin 10 on Uno

// Constants
char ssid[] = "yournetworkname";     //  your network SSID (name)
char pass[] = "yourpassword";  // your WPA network password
unsigned int ap_security = WLAN_SEC_WPA2; // Security of network
unsigned int timeout = 30000;             // Milliseconds

char server[] = "skynet.im";

//Your UUID and token for skynet.im TODO where to get one
char UUID[]  = "XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX";
char TOKEN[] = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";

//another UUID well send a message to
char TOUUID[] = "XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX"; 

// Global Variables
SFE_CC3000 wifi = SFE_CC3000(CC3000_INT, CC3000_EN, CC3000_CS);
SFE_CC3000_Client client = SFE_CC3000_Client(wifi);
PubSubClient skynet(server, 1883, onMessage, client);

//we'll run this if anyone messages us
void onMessage(char* topic, byte* payload, unsigned int length) {

  // handle incoming messages, well just print it for now
  Serial.println(topic);
  for(int i =0; i<length; i++){
    Serial.print((char)payload[i]);
  }    
  Serial.println();
}

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);

  // Initialize CC3000 (configure SPI communications)
  if ( wifi.init() ) {
    Serial.println(F("CC3000 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during CC3000 init!"));
    while(1);
  }

}

void loop() {
  //we need to call loop for the mqtt library to do its thing and send/receive our messages
  if(skynet.loop()){
  
    //Lets log some data every time through the loop!
    //create a json string like "light":122
    //don't forget to escape those quotes!
    //here we grab whatever is hooked up to A0
    String messageString = "{\"light\":"+ String(int(analogRead(A0))) + "}";
    
    //housekeeping to turn our string into a character array
    char message[messageString.length()+1];
    messageString.toCharArray(message, messageString.length()+1);
  
    //Send away! The logging endpoint is called 'data'
    skynet.publish("data",message);
    
    //small delay here so we dont send too many mesages
    //but avoid delays and long running code, we need to let loop do its work!
    delay(1000);
  }else
  {
    //oops we're not connected yet or we lost connection
    Serial.println(F("connecting..."));

    // Sadly if we don't reinit it never reconnects
    if ( wifi.init() ) {
      Serial.println(F("CC3000 initialization complete"));
    } else {
      Serial.println(F("Something went wrong during CC3000 init!"));
      while(1);
    }

    //lets wait so we don't slam the router
    delay(10000);

    // attempt to connect to Wifi network:
    if(wifi.connect(ssid, ap_security, pass, timeout)) {

      // connect to skynet -- skynet doesnt use client so send empty client string and YOUR UUID and token
      if (skynet.connect("", UUID, TOKEN)){

        //success!
        Serial.println(F("connected"));

        //you need to subscribe to your uuid to get messages for you
        skynet.subscribe(UUID);
        
        //Lets send a message! give the destination and payload in a json object
        //{"devices":"XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX","payload":"hi!"}
        //don't forget to escape those quotes!
        //also note the wifi shield has a character limit of like 80 so stay below that
        String messageString = "{\"devices\":\"" + String(TOUUID) + "\",\"payload\":\"hi!\"}" ;
    
        //housekeeping to turn our string into a character array
        char message[messageString.length()+1];
        messageString.toCharArray(message, messageString.length()+1);
      
        //Send away! The device to device endpoint is called 'message'
        skynet.publish("message",message);
      }

    }else
    {
          Serial.print(F("couldnt connect to: "));
          Serial.println(ssid);
    }
  } 
}