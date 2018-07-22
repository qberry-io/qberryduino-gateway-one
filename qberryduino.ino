//  Copyright (c) 2018-present, Deniz Kanmaz. All rights reserved.
//  This source code is licensed under the GNU GENERAL PUBLIC
//  LICENCE V3. Use of this source code is governed by a license
//  that can be found in the LICENSE file.

//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  LICENSE file for more details.

//  You should have received a copy of the LICENSE file along with
//  this program. If not, see <http://www.gnu.org/licenses/>.

//  E-mail: denizkanmaz@gmail.com

//  Description: "Qberyduino One" is an open source IOT Gateway
//  developed for bringing telemetry-kind data to TCP Socket
//  server over GPRS.

//  Model: Qberyduino One
//  Version: 1.0.0

#include "MainSerial.h"
#include "LED.h"
#include "Modem.h"
#include "Messaging.h"
#include "Parsing.h"

// Definitions of necessary utilities.
LED _led;
MainSerial _mainSerial;
Modem _modem;
Messaging _messaging = Messaging();
Parsing _parsing = Parsing();

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

// Definitions of APN.
// NOTICE: To get your APN information, please refer to your
// Telecom company.
const PROGMEM String APN_NAME = "internet";
char APN_USER [] = "";
char APN_PASS [] = "";

// Definitions of development / maintenance stuffs
const PROGMEM boolean DEBUG_MODE = true;
const PROGMEM int SERIAL_BAUD_RATE = 9600;

// Definitions of device
const PROGMEM byte DEVICE_IDENTITY_LENGTH = 19;
char DEVICE_IDENTITY_PREFIX[] = "90";
char DEVICE_IDENTITY[DEVICE_IDENTITY_LENGTH];
char DEVICE_MODEL[] = "ONE";

// Definitions of leds
const PROGMEM byte LED_PINS_LENGTH = 4;
byte LED_PINS[LED_PINS_LENGTH] = { 5, 4, 3, 2 };

// Definitions of modem
const PROGMEM byte MODEM_RX_PIN = 8;
const PROGMEM byte MODEM_TX_PIN = 7;
const PROGMEM int MODEM_BAUD_RATE = 9600;

// Definitions of Intervals and Delays
const PROGMEM int CURR_INTERVAL = 15000;
const PROGMEM int STARTUP_DELAY = 5000;

// Current State
int i; // Used in loops only
unsigned long now = 0;
unsigned long lastCurrTime = 0;

// Resets the device.
void(* reset) (void) = 0;

// Sends the given String message to the server.
void sendToServer(String msg) {

  // Send the message to the server.
  if (_modem.sendToServer(msg)) {
    _led.indicateTCPSendSuccess();

  } else {

    _led.indicateDisconnected();
    _led.indicateTCPSendFailed();
    // Reset the device if the sending operation has failed.
    // (This happens when the established connection has
    // corrupted.)
    reset();
  }
}

void setup() {

  // Initialize the main serial if debug mode enabled.
  if (DEBUG_MODE) {
    _mainSerial.init(SERIAL_BAUD_RATE);
  }

  // Initialize LED indicators.
  _led.init(LED_PINS,
            LED_PINS_LENGTH);

  // Indicate for "Starting Up!".
  _led.indicateStarting();

  // Indicate for "Powered On".
  _led.indicatePoweredOn();

  // Give the modem some time.
  delay(STARTUP_DELAY);

  // Initilize the modem.
  _modem.init(MODEM_RX_PIN,
              MODEM_TX_PIN,
              MODEM_BAUD_RATE,
              APN_NAME, APN_USER,
              APN_PASS,
              _mainSerial);

  // Connect to TCP server..
  if (!_modem.connectToTCP(SERVER_ADDRES,
                           TCP_PORT)) {

    // Indicate establishing connection has failed.
    _led.indicateConnectionError();

    // reset the device if the establishing connection has
    // failed.
    reset();
    return;
  }

  // Indicate successfuly connected.
  _led.indicateConnected();

  // Set device identity using DEVICE_IDENTITY_PREFIX and
  // IMEI of the Modem.
  (String(DEVICE_IDENTITY_PREFIX)
   + String(_modem.getImei())).toCharArray(
     DEVICE_IDENTITY,
     DEVICE_IDENTITY_LENGTH);

  // Send a "HOLA" message to the server.
  sendToServer(_messaging.hola(DEVICE_IDENTITY,
                               PASSWORD,
                               DEVICE_MODEL));

  _parsing.clear();
  _modem.clearBuffer();
}

// 1-) Gets the current CGNSS data,
// 2-) Parses it,
// 3-) Creates "CURR" message for "CGNS"
// 4-) Sends it to the server.
void processToSendCurrentCGNSS() {
  sendToServer(_messaging.currCGNS(DEVICE_IDENTITY,
                                   PASSWORD,
                                   DEVICE_MODEL,
                                   _parsing.parseNMEAData(
                                     _modem.getCGNSSData())
                                  ));
  _parsing.clear();
  _modem.clearBuffer();
  delay(1000);
}

// 1-) Gets the current Battery data,
// 2-) Parses it,
// 3-) Creates "CURR" message for "Battery"
// 4-) Sends it to the server.
void processToSendCurrentBatteryStat() {
  sendToServer(_messaging.currBatt(DEVICE_IDENTITY,
                                   PASSWORD,
                                   DEVICE_MODEL,
                                   _parsing.parseBatt(
                                     _modem.getBatteryStat()
                                   )));
  _parsing.clear();
  _modem.clearBuffer();
  delay(1000);
}

void loop() {

  now = millis();

  // If it's time to send a "CURR" message...
  if (now > (lastCurrTime + CURR_INTERVAL)) {
    lastCurrTime = millis();

    // Process to send current CGNSS data to the server.
    processToSendCurrentCGNSS();

    // Process to send current Battery status to the server.
    processToSendCurrentBatteryStat();

    // Process to send whatever you want here :)
    // processMyLovelyData();
  }
}
