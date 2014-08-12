```

MM    MM iii                      bb      lll         
MMM  MMM       cccc rr rr   oooo  bb      lll uu   uu 
MM MM MM iii cc     rrr  r oo  oo bbbbbb  lll uu   uu 
MM    MM iii cc     rr     oo  oo bb   bb lll uu   uu 
MM    MM iii  ccccc rr      oooo  bbbbbb  lll  uuuu u 
                                                      
                                                
```

Microblu OS allows you to connect and control your Arduino via the Octoblu Meshblu (formerly SkyNet.im) open source IoT platform and API.

Microblu OS supports Arduino ethernet or wifi shields (or any other device that properly implements the Client interface)
 * http://arduino.cc/en/Main/ArduinoEthernetShield
 * http://arduino.cc/en/Main/ArduinoBoardEthernet
 * http://arduino.cc/en/Main/ArduinoWiFiShield
 * https://www.sparkfun.com/products/12071
 * https://pinocc.io/
 * https://www.spark.io/

##Videos
* https://www.youtube.com/watch?v=oQzWKPER_ic
* https://www.youtube.com/watch?v=ZJNlqZXbrbM

##Install 

First you need a valid UUID and Token from Skynet. Copy and paste the following into a terminal window, and put the resulting UUID and TOKEN in your sketch.

```bash
curl -X POST -d "type=firmwareController&payloadOnly=true&name=Arduino" http://skynet.im/devices
```
You'll need this repo. 
* Find the Download Zip button on the right ->
* Unarchive and rename the resulting folder to remove any invalid characters like -
* In Arduino go to Sketch->Import Library->Add Library and choose the main folder you renamed

You'll also need our fork of the MQTT PubSubClient Library
* Go to https://github.com/jacobrosenthal/pubsubclient and find the Download Zip button on the right.
* Unarchive the folder
* In Arduino go to Sketch->Import Library->Add Library and choose the *****PubSubClient SUB FOLDER****

###Install Wifi 

These are instructions for Arduino brand wifi
* http://arduino.cc/en/Main/ArduinoWiFiShield

The first thing you should do is see if your shield and network work by using the standard wifi test at
File->Examples->WIFI->WiFiWebClient. 

Put your connection details in and make sure it gets a connection to google that looks like this:
https://gist.github.com/jacobrosenthal/1dc81eef411392f1de71

If you've never updated your Wifi shields firmware, you'll see a message to update your firmware. Please do:
http://arduino.cc/en/Hacking/WiFiShieldFirmwareUpgrading

Now you can open microblu_wifi example at File->Examples->microblu_mqtt.

Add your UUID and TOKEN from before.

Last don't forget to change out your wifi or other networking credentials here too. 

Upload away. You can open the Arduino Serial Terminal at 9600  to see your connection status.

As we go forward remember NOT to mess with wifi's pins (7, 10, 11, 12, 13 and 4 if using SD card)

###Install Ethernet 

These are instructions for Arduino brand ethernet shields and boards
* http://arduino.cc/en/Main/ArduinoEthernetShield
* http://arduino.cc/en/Main/ArduinoBoardEthernet

Open microblu_eth example at File->Examples->microblu_mqtt.

Add your UUID and TOKEN from before.

It might be wise to alter the stock MAC address. If you ever have two of these on the same network you'll have trouble otherwise.

Upload away. You can open the Arduino Serial Terminal at 9600 to see your connection status.

As we go forward, remember NOT to mess with ethernet's unavailable pins (10, 11, 12, 13 and 4 if using SD card)

###Install CC3000 

These are instructions for any board using a CC3000 chip regardless of manufacturer. We prefer Sparkfun:
* https://www.sparkfun.com/products/12071
* http://www.adafruit.com/products/1491

The only library we know of that properly implements the Arduino client library is Sparkfun's so matter which shield you have, donwnload and install their library as before:
https://github.com/sparkfun/SFE_CC3000_Library/

The first thing you should do is see if your shield and network work by using the standard wifi test at
File->Examples->SFE_CC3000_Library->PingTest. 

Put your connection details. You'll also have to change the pins to match whatever shield you have. The default pin setup is for sparkfun. If you hava adafruit you might use:
```
#define CC3000_INT      3   // Needs to be an interrupt pin (D2/D3)
#define CC3000_EN       5   // Can be any digital pin
#define CC3000_CS       10  // Preferred is pin 10 on Uno
```

And make sure it gets a connection to sparkfun that looks like this:
XXX

It it does, we're all good. Open microblu_cc3000 example at File->Examples->microblu_mqtt.

Add your UUID and TOKEN from before.

Don't forget to change out your pins and wifi or other networking credentials here too. 

Upload away. You can open the Arduino Serial Terminal at 9600  to see your connection status.

As we go forward, remember NOT not to mess with cc3000's unavailable pins (11, 12, 13 and whatever you set above)

One note about the cc3000 is it is a VERY big library. We've had to make a few changes. The sketch no longer supports capabilty query. Most likely that doesn't mean anything to you so don't worry about it.

###Install Spark 

These are instructions for a Spark Core:
* https://www.spark.io

The Spark does NOT uitlize Arduino. Unless you're an advanced user this is very difficult until we can get all the libraries we need in the Spark online IDE. Follow the directions below, but you can also see a working example in our experimental branch at:
https://github.com/jacobrosenthal/core-firmware/tree/skynet-mqtt-firmata

Follow the instructions on their site to custom build:
https://github.com/spark/core-firmware

Also requires our fork of firmata https://github.com/jacobrosenthal/arduino/tree/Spark

And Teensy's pgmspace.h https://github.com/jacobrosenthal/core-firmware/blob/skynet-mqtt-firmata/inc/pgmspace.h

Once you can successfully custom build, you need to dump all the cpp files in /src and all the h files in /inc. Replace application.cpp with this file

Add your UUID and TOKEN from before.

Upload away. You can open the Arduino Serial Terminal at 9600  to see your connection status.


##USE

Now you can use [Nodeblu Designer](http://app.octoblu.com/design "Nodeblu") or [Node.js](https://www.npmjs.org/package/skynet-serial "Node.js") to command and control your Arduino.


LICENSE
-------

(LGPL License)

Copyright (c) 2014 Octoblu <info@octoblu.com>

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
