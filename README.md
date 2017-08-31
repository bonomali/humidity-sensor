
[![N|Solid](http://icon-icons.com/icons2/159/PNG/128/arduino_22429.png)](https://www.arduino.cc) [![N|Solid](http://embeddedcomputing.weebly.com/uploads/1/1/6/2/11624344/7821847_orig.png)](http://nodemcu.com)
# Humidity Sensor

Humidity sensor is a personal project to learn integration between ARDUINO, NodeMcu and SERVER using bluetooth and wifi communication.

## What does it do?

The purpose of this project is to build a vegetable garden that is self-sufficient. The environment should be smart enough to know when it needs to be watered, and a watering system has to be automatically activated in case of need.

## How does it works?
Every six hours the sensor sends information to server, that will process that.
The communication between then is made via Bluetooth connection.

## Hardware and Software

- Hardware: It is composed by an [Arduino Nano], a humidity-sensor and a bluetooth transmitter on the Humidity Sensor Part.
            The watering part is composed by an [NodeMcu] hardware and a water pump.
- Server: This is a `C` powered server that receives and process hardware information.

### Hardware Details
- [Arduino Uno]
- Humidity Sensor shield GC-58
- Bluetooth shield HC-05
- [NodeMcu]

Checkout the schematic under `/fritzing-project`
The Arduino program can be found under `/arduino/sensor/sensor.ino`. Just upload it to your hardware. By default it is configured to send data each six hours.
The NodeMcu program can be found under `/esp8266/watering/watering.ino`. Just upload it to your hardware. By default it is
configurated to the local ip 192.168.1.111

### Server Details
This server was built in `C` language to perform better. The server is also integrated with three tools:
* [IFTT Maker Applet] - A tool that allows you to POST anything, then integrate with all the other IFTTT applets.
* [ThingSpeak] - A service where you can send data and work with that in charts, or MathLab analysis.
* [Loggly] - A service where you can send LOG data and create alerts, or analysis.

The three services (and the watering system) can be activated/deactivated and configured in the `CONFIG.CFG` file.

By default, when server receives a new information from humidity-sensor, it posts the humidity percentage to ThingSpeak and sends a message to IFTTT Maker, that posts to my Facebook account with custom messages =).

It also checks if the plant needs water. In case is under 60% humidity, it will automatically water for 5 minutes.

**ATTENTION: Your host server machine should accept bluetooth connection and be in a local network**

#### Instalation & Run
```sh
$ cd humidity-sensor
$ make dep-linux
$ make server
$ ./bin/server
```
If you want to change some configuration, just stop the server, change the config you want, and simple run `$ ./bin/server` again.

### Todos

 - Expand server and Arduino program to work with more than one sensor.
 - Dockerize
 - Improve MAKEFILE


**Free Software**

   [Arduino UNO]: <https://www.arduino.cc/en/Main/ArduinoBoardUno>
   [IFTT Maker Applet]: <https://ifttt.com/maker_webhooks>
   [ThingSpeak]: <http://thingspeak.com/>
   [Loggly]: <http://loggly.com/>
   [NodeMcu]: <http://nodemcu.com/index_en.html>
