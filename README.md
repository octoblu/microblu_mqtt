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
You'll need this repo. 
* Find the Download Zip button on the right ->
* Rename the resulting folder to remove any invalid characters like - , and import the main folder via Arduino menu Sketch->Import Library->Add Library

You'll also need our fork of the MQTT PubSubClient Library
* Go to https://github.com/jacobrosenthal/pubsubclient and find the Download Zip button on the right.
* Import the PubSubClient sub folder via Arduino menu Sketch->Import Library->Add Library

Open one of the microblu examples at File->Examples->microblu_mqtt. You'll find examples for many different boards including cc3000, Spark, Arduino Ethernet and Wifi. Some of these may require you to install your manufacturer's library as well. See the example file.

Next you need a valid UUID and Token from Skynet. Copy and paste the following into a terminal window, and put the resulting UUID and TOKEN in your sketch.

```bash
curl -X POST -d "type=firmwareController&name=Arduino" http://skynet.im/devices
```

Last don't forget to change out your wifi or other networking credentials. Upload away. You can open the Arduino Serial Terminal at 9600  to see your connection status.


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
