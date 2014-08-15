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

##Getting Started with Arduino

To use microblu you will need to installed the Arduino IDE and some required libraries.

Required Downloads:
* [Arduino IDE](http://arduino.cc/en/Main/Software)
* [microblu_mqtt Library](https://github.com/octoblu/microblu_mqtt/archive/master.zip)
* [PubSubClient Library](https://github.com/jacobrosenthal/pubsubclient/archive/master.zip)

Proceed after you have successfully installed the Arduino IDE 

###Installing Libraries

* Unzip the libraries you've just downloaded and rename the folder for each library removing anything like "- master"
* Open Arduino and go to Sketch->Import Library->Add Library and choose the main folders you renamed
* If you goto File->Examples you should see microblu_mqtt 
* Choose the example that corresponds to the shield you will be using before proceeding.

##Configuring your code

First you need a valid UUID and Token from Skynet. Copy and paste the following into a terminal window, and put the resulting UUID and TOKEN in your sketch.

NOTE: In windows use a terminal emulator such as CYGWIN

```bash
curl -X POST -d "type=firmwareController&payloadOnly=true&name=Arduino" http://skynet.im/devices
```

Ensure the following have been added to your sketch:
* UUID
* TOKEN
* WIFI Credentials (if using wifi shield)

Save this sketch and move on to the corresponding tutorial!

##Install Wifi 

These are instructions for Arduino brand wifi
* http://arduino.cc/en/Main/ArduinoWiFiShield

###Step 1 - Test your WIFI shield

Open the sketch:
File->Examples->WIFI->WiFiWebClient. 

Put your connection details in and make sure it gets a connection to google that looks like this:
* https://gist.github.com/jacobrosenthal/1dc81eef411392f1de71

####Firmware Update
If you've never updated your Wifi shields firmware, you'll see a message to update your firmware. Please do:
* http://arduino.cc/en/Hacking/WiFiShieldFirmwareUpgrading

###Step 2 - check configuration

Open microblu_wifi example at File->Examples->microblu_mqtt and **follow the "Configuring your Code" section above** if you haven't


Double check your wifi credentials!

Lastly
* Check Tools->Port and Tools->Board and make any neccesary changes
* Upload your code
* Open a serial monitor and listen in at 9600 baudrate (this is how your Arduino will tell you if something broke)

####Pins In use by Shield (Do not use these pins for anything else)

* 7, 10, 11, 12, 13 
* If the SD card is in use Pin 4 will also be unavailable.


##Install Ethernet 

These are instructions for Arduino brand ethernet shields and boards
* http://arduino.cc/en/Main/ArduinoEthernetShield
* http://arduino.cc/en/Main/ArduinoBoardEthernet

Open microblu_eth example at File->Examples->microblu_mqtt and **follow the "Configuring your Code" section above** if you haven't


It might be wise to alter the stock MAC address. If you ever have two of these on the same network you'll have trouble otherwise.

Lastly
* Check Tools->Port and Tools->Board and make any neccesary changes
* Upload your code
* Open a serial monitor and listen in at 9600 baudrate (this is how your Arduino will tell you if something broke)

####Pins In use by Shield (Do not use these pins for anything else)

* 10, 11, 12, 13
* If the SD card is in use Pin 4 will also be unavailable.

##Install CC3000 

These are instructions for any board using a CC3000 chip regardless of manufacturer. We prefer Sparkfun:
* https://www.sparkfun.com/products/12071
* http://www.adafruit.com/products/1491


####Install Dependency 
The only library we know of that properly implements the Arduino network client library for the CC3000 is Sparkfun's and as long as you have any shield that uses a CC3000, donwnload and install their library as before:
* [SFE_CC3000 Library](https://github.com/sparkfun/SFE_CC3000_Library/archive/master.zip)

###Test Connection

The first thing you should do is see if your shield and network work by using the standard wifi test at
File->Examples->SFE_CC3000_Library->PingTest. 

Put your connection details. You'll also have to change the pins to match whatever shield you have. The default pin setup is for sparkfun. If you have adafruit you might use:
```
#define CC3000_INT      3   // Needs to be an interrupt pin (D2/D3)
#define CC3000_EN       5   // Can be any digital pin
#define CC3000_CS       10  // Preferred is pin 10 on Uno
```

Open a serial monitor to 9600 Baudrate and check that you're connected (this may take a minute)

If it connects, we're all good. Open microblu_cc3000 example at File->Examples->microblu_mqtt.

**Follow the "Configuring your Code" section above. **

Don't forget to change out your pins and wifi or other networking credentials here too. 

Lastly
* Check Tools->Port and Tools->Board and make any neccesary changes
* Upload your code
* Open a serial monitor and listen in at 9600 baudrate (this is how your Arduino will tell you if something broke)

####Pins In use by Shield (Do not use these pins for anything else)

* 11, 12, 13 and any other pins you've set above.

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
