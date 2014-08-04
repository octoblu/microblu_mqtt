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

Now you'll find File->Examples->SkynetClient

##Examples
Find full examples in the File->Examples->SkynetClient menu but generally, theres 3 ways to use: firmata, message api, data api.

###Firmata
Firmata is a common protocol that many apps are built on to control arduinos dynamically. You only program them once and then you can toggle pins, read data, move servo and much much more.  We've tunned firmata through Skynet over mqtt so now you can control your devices wirelessly around the world. First you need a UUID with its type set to 'firmwareController' 
```bash
curl -X POST -d "type=firmwareController&name=myController" http://skynet.im/devices
```
This tells Skynet to remove all skynet routing information from the packet and to only give the payload. Put that uuid and token into one of our skynetim_StandardFirmata examples along with any networking information, and you've got a skynet slave device waiting for instructions.

###Data API
For a simpler example, we can also just log data in Skynet to be retreived elsewhere later using the Data api:
```cpp

    //create a json string like "light":122
    //don't forget to escape those quotes!
    //here we grab whatever is hooked up to A0
    String messageString = "{\"light\":"+ String(int(analogRead(A0))) + "}";
    
    //housekeeping to turn our string into a character array
    char message[messageString.length()+1];
    messageString.toCharArray(message, messageString.length()+1);
  
    //Send away! The logging endpoint is called 'data'
    skynet.publish("data",message);

```
Now you can subscribe to your data elsewhere. See the api page for rest examples with Rest, Javascript, and more! http://skynet.im/#api

###Message API
Finally, you might like to have your arduino communicate with other skynet client somewhere in the world. You might log data, trigger a command -- it's completely up to you. When you create the skynet object you register a callback function to be called when Skynet receives a message for your device:
```cpp
//Lets send a message! give the destination and payload in a json object
//The message endpoint is called message, don't forget to escape those quotes!
skynet.publish("message"," "{\"devices\":\"XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX\",\"payload\":\"hi!\"}"");
```
We can receive messages too. When we connect we subscribe to *our own* UUID
```cpp
skynet.subscribe(XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX);
```
And we subscribe a callback function to be fired when we receive a message
```cpp
PubSubClient skynet(server, 1883, onMessage, client);

// handle incoming messages, well just print the topic
void onMessage(char* topic, byte* payload, unsigned int length) {
  Serial.println(topic);
}
```

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
