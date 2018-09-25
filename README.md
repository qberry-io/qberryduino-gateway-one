# Qberryduino One v.1.0.0

"Qberryduino One" is an open source IOT Gateway developed for bringing telemetry-kind data to TCP Socket server over GPRS. 

It can be used as a gateway (Home Automation projects for example) as well as stand-alone Vehicle / Asset Tracker.

If wanted to use as a basic Vehicle / Asset Tracker, it's ready to use. No development needed.

## Prerequisites
The hardwares needed to use this solution.
* 1 * Arduino Mini Pro 16 MHz, 5v with Atmega328P (or equivalent version of Arduino)
* 1 * [Adafruit Fona 808 Version 2 Shield](https://www.adafruit.com/product/2636)
* 1 * USB to TTL Adaptor (Compatible with 3,3v)
* 1 * Red LED
* 1 * Yellow LED
* 1 *  Blue LED
* 3 * 220 ohm 5% resistors
* 1* GPS Antenna (uFL - 15x15 mm 1 dBi)
* 1* GSM Antenna (Compatible with Fona 808)
* 1* 3.7 V 950 mAh 25C Li-Po Battery
* 1* Active GPRS enabled Simcard

## Installation

These instructions will get you a copy of the project up and running on your development environment.

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

![enter image description here](https://lh3.googleusercontent.com/OZIM_0mFb-jgyUuYGuuslm1Z3meFcrUUe49EGT8yfN1WwXtKgSnmazm6Cj4eHPAh9LiuSCHu2iZd "The sketch of the circuit")

#### Notice for the PIN number of simcard
Please be sure that simcard doesn't protected with a PIN number. Fona 808 fails if the simcard has a PIN number.

#### Notice for the registration of Fona 808
Please be sure that IMEI number of Fona 808 is registered for your country.

#### Notice for the USB to TTL Adapter and its voltage value
Please be sure that the adapter provides the same voltage with the Arduino that you will use.
For example: If you will use an "Arduino Mini Pro 16 MHz, 5v with Atmega328P". you need to be sure it provides 5v output.

### Some configuration on code
There are two blocks of definitions needed to be configured in "qberryduino.ino". These are the informations of the target TCP Socket server and APN configurations of the current SIM line.
```
// Definitions of the target TCP Socket server.
char SERVER_ADDRES [] = "your_ip";
const PROGMEM int TCP_PORT = 13101;

// This is not a secret or password for accessing the
// TCP Socket Server.
// It lets you filter the illegal messages. Then, you can block
// them in your TCP Socket server.
// NOTICE: If you will use it on a common platform like qberry.io,
// it's strongly recommended you to change this secret key.
char SECRET[7] = "B23a56";
```
```
// Definitions of APN.
// NOTICE: To get your APN information, please refer to your Telecom
// company.
const PROGMEM String APN_NAME = "internet";
char APN_USER [] = "";
char APN_PASS [] = "";
```
#### An important notice for Compiling and Uploading the Sketch
Please be sure that you're compiling for the right microcontroller.
For example: If you will use an "Arduino Mini Pro 16 MHz, 5v with Atmega328P" you need to be sure;
* "ATmega328P (5v, 16MHz)" is selected on "Arduino IDE > Tools > Processor"
* "Arduino Pro or Pro Mini" is selected on "Arduino IDE > Tools > Board"
* The right port is selected on "Arduino IDE > Tools > Port"

### Common issues when the first runnings
Problem: It restarts recursively, when it comes to TCP Connection step.
Device restarts if the establishing a connection has failed. Please be sure;
* The APN information is correct,
* The target TCP Socket Server information is correct,
* The target TCP Socket Server is active and reachable over the firewall, IP table etc.

Problem: It restarts recursively, when it comes to Send step.
Device restarts if the established connection has droped and sending the message has failed. Please be sure,
* The target TCP Socket Server doesn't drop the connection.
* If you use a common platform like qberry.io, please be sure that the device is already defined to your account, licence is not expired and the password is correct. 

## Messaging Protocol
Please refer [Open Qberry Messaging Protocol]()

## Known issues and missing important functions
After the development, there are some technical issues as well as some missing functions showed themselves. They will be solved with the incoming versions.

* Impossible to change the configurations remotely,
* A couple of dirty blocks of code (Parsing.cpp for examle).
* Some missed comments / documentation on code.

## Versioning

Used [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/denizkanmaz/qberryduino-gateway-one/tags). 

## Authors

* **[Deniz Kanmaz (denizkanmaz@gmail.com)](https://github.com/denizkanmaz)** - *Initial work* - [qberry.io](https://qberry.io)

## License

This project is licensed under the GNU General Public License v3 - see the [LICENSE.md](LICENSE.md) file for details.

NOTICE: This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.