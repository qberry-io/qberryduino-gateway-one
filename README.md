
# Qberryduino One v.1

"Qberryduino One" is an open source IOT Gateway developed for bringing telemetry-kind data to TCP Socket server over GPRS. 

It can be used as a gateway (Home Automation projects for example) as well as stand-alone Vehicle / Asset Tracker.

If wanted to use as a basic Vehicle / Asset Tracker, it's ready to use. No development needed.

## Getting Started

These instructions will get you a copy of the project up and running on your development environment.

### Prerequisites
The hardwares needed to use this solution.
* 1 * Arduino Mini Pro 8 MHz, 3.3v with Atmega328P (or higher version of Arduino)
* 1 * [Adafruit Fona 808 Version 2 Shield](https://www.adafruit.com/product/2636)
* 1 * USB to TTL Adaptor (Compatible with 3,3v)
* 3 * LEDs
	* Red
	* Yellow
	* Blue
* 3 * 250 ohm resistors
* 1* GPS Antenna (Compatible with Fona 808)
* 1* GSM Antenna (Compatible with Fona 808)
* 1* Battery (Compatible with Fona 808)
* 1* active GPRS enabled Simcard

## Installation
### Hardware installation

Here is a list of hardware and their connections step by step with preferred cable colors.
*	Red LED
	* (+) → Pin 5 (Red)  _(With a 250 ohm resistor)_
	* (-) → GND (Black)
*	Yellow LED
	*	(+) → Pin 4 (Yellow)  _(With a 250 ohm resistor)_
	*	(-) → GND (Black)
*	Blue LED
	*	(+) → Pin 2 (Blue)  _(With a 250 ohm resistor)_
	*	(-) → GND (Black)
*	Fona 808
	*	5v -> Pin 5v (Red)
	*	GND -> GND (Black)
	*	RX -> Pin 7 (Orange)
	*	TX -> Pin 8 (Brown)
*	USB to TTL adapter > Arduino
	*	

### Notice for the USB to TTL Adapter and its voltage value
Please be sure that the adapter provides the same voltage with the Arduino that you will use.
For example: If you will use an "Arduino Mini Pro 8 MHz, 3.3v with Atmega328P". you need to be sure it provides 3.3v output.

### Some configuration on code
There are two blocks of definitions needed to be configured in "qberryduino.ino". These are the informations of the target TCP Socket server and APN configurations of the current SIM line.
```
// Definitions of the target TCP Socket server.
char SERVER_ADDRES [] = "37.48.83.216";
const PROGMEM int TCP_PORT = 23101;

// This is not a password for accessing the
// TCP Socket Server.
// It lets you filter illegal posts. You can block
// them in your TCP Socket server, if you want.
// If you will use it on a common platform like qberry.io,
// it's strongly recommended you to change this passcode.
char PASSWORD[7] = "B23a56";
```
```
// Definitions of APN.
// NOTICE: To get your APN information, please refer to your Telecom
// company.
const PROGMEM String APN_NAME = "internet";
char APN_USER [] = "";
char APN_PASS [] = "";
```
### An important notice for Compiling and Uploading the Sketch
Please be sure that you're compiling for the right microcontroller.
For example: If you will use an "Arduino Mini Pro 8 MHz, 3.3v with Atmega328P" you need to be sure;
* "ATmega328P (3.3v, 8MHz)" is selected on "Arduino IDE > Tools > Processor"
* "Arduino Pro or Pro Mini" is selected on "Arduino IDE > Tools > Board"
* The right port is selected on "Arduino IDE > Tools > Port"



## Running for the first time!

All sets! And your TCP Socket server is ready to receive messages.
After uploading the code to your Arduino, please monitor it using Arduino IDE's built in Serial Monitor tool (Arduino IDE > Tools > Serial Monitor). The result looks like this:
```
Give an example
```


### Problems
Problem: It restarts recursively, when it comes to TCP Connection step.
Device restarts if the establishing a connection has failed. Please be sure;
* The APN information is correct,
* The target TCP Socket Server information is correct,
* The target TCP Socket Server is active and reachable over the firewall, IP table etc.

Problem: It restarts recursively, when it comes to Send step.
Device restarts if the established connection has droped and sending the message has failed. Please be sure,
* The target TCP Socket Server doesn't drop the connection.
* If you use a common platform like qberry.io, please be sure that the device is already defined to your account, licence is not expired and the password is correct. 


## Known issues and missing important functions
After the development, there are some technical issues as well as some missing functions showed themselves. They will be solved with the incoming versions.

* Memory leaks,
* Impossible to change the configurations remotely,
* A couple of dirty blocks of code.
* Missing comments / documentation on code.

## Versioning

Used [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/denizkanmaz/qberryduino-gateway-one/tags). 

## Authors

* **[Deniz Kanmaz](https://github.com/denizkanmaz)** - *Initial work* - [qberry.io](https://qberry.io)

## License

This project is licensed under the GNU General Public License v3 - see the [LICENSE.md](LICENSE.md) file for details.

NOTICE: This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.