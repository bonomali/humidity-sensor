
[![N|Solid](http://jualarduinomurah.com/wp-content/uploads/2017/01/arduino_logo.png)](https://nodesource.com/products/nsolid)
# Humidity Sensor

Humidity sensor is a personal project to learn integration between ARDUINO and SERVER using bluetooth connection.

## What does it do?

The purpose of this project is to build a vegetable garden that is self-sufficient. The environment should be smart enough to know when it needs to be watered, and a watering can has to be automatically activated in case of need. For now the part of the irrigator project is still under development.

## How does it works?
The system is divided into two parts: Humidity sensor hardware and server.
- Hardware: It is composed by an [Arduino Uno] (will be reduced to a Nano version), a humidity-sensor and a bluetooth transmitter.
- Server: This is a `C` powered server that receives and process hardware information.

### Hardware Details
- [Arduino Uno]
- Humidity Sensor shield GC-58
- Bluetooth shield HC-05

Checkout the schematic under `/fritzing-project`
The Arduino program can be found under `/arduino/sensor/sensor.ino`. Just upload it to your hardware. By default it is configured to send data each six hours.

### Server Details
This server was built in `C` language to perform better. The server is also integrated with three tools:
* [IFTT Maker Applet] - A tool that allows you to POST anything, then integrate with all the other IFTTT applets.
* [ThingSpeak] - A service where you can send data and work with that in charts, or MathLab analysis.
* [Loggly] - A service where you can send LOG data and create alerts, or analysis.

The three services can be activated/deactivated and configured in the `CONFIG.CFG` file.

By default, when server receives a new information from humidity-sensor, it posts the humidity percentage to ThingSpeak and sends a message to IFTTT Maker, that posts to my Facebook account with custom messages =).

**ATTENTION: Your host server machine should accept bluetooth connection**

#### Instalation & Run
```sh
$ cd humidity-sensor
$ make server
$ ./bin/server
```
If you want to change some configuration, just stop the server, change the config you want, and simple run `$ ./bin/server` again.

### Todos

 - Expand server and Arduino program to work with more than one sensor.
 - Create customizable messages and ranges for IFTTT integration.
 - Build harware and software for the irrigation system.
 - Integrate irrigation service on server part.


**Free Software**

   [Arduino UNO]: <https://www.arduino.cc/en/Main/ArduinoBoardUno>
   [IFTT Maker Applet]: <https://ifttt.com/maker_webhooks>
   [ThingSpeak]: <http://thingspeak.com/>
   [Loggly]: <http://loggly.com/>
