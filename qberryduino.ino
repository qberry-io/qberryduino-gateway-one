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

#include "MainSerial.h"
#include "Led.h"
#include "Modem.h"
#include "Messaging.h"
#include "CGNSS.h"

Led _led;
MainSerial _mainSerial;
Modem _modem;
Messaging _messaging = Messaging();
CGNSS _cgnss = CGNSS();

// Definitions of Server
char SERVER_ADDRES [] = "37.48.83.216";
const PROGMEM int TCP_PORT = 23101;
char PASSWORD[] = "123456";

// Definitions of APN
const PROGMEM String APN_NAME = "internet";
char APN_USER [] = "";
char APN_PASS [] = "";

// Definitions of development / maintenance stuff
const PROGMEM boolean DEBUG_MODE = true;
const PROGMEM int SERIAL_BAUD_RATE = 9600;

// Definitions of device
const PROGMEM byte DEVICE_IDENTITY_LENGTH = 19;
char DEVICE_IDENTITY_PREFIX[] = "90";
char DEVICE_IDENTITY[DEVICE_IDENTITY_LENGTH];
char DEVICE_MODEL[] = "qbdone";

// Definitions of leds
const PROGMEM byte LED_PINS_LENGTH = 4;
byte LED_PINS[LED_PINS_LENGTH] = { 5, 4, 3, 2 };

// Definitions of modem
const PROGMEM byte MODEM_RX_PIN = 8;
const PROGMEM byte MODEM_TX_PIN = 7;
const PROGMEM int MODEM_BAUD_RATE = 9600;

const PROGMEM int CURR_INTERVAL = 15000;

// Current State
int i; // Used in loops only
unsigned long now = 0;
unsigned long lastCurrTime = 0;

void(* reset) (void) = 0;

void initSerial() {
  Serial.begin(SERIAL_BAUD_RATE);
}

void setup() {
  if (DEBUG_MODE) {
    _mainSerial.init(SERIAL_BAUD_RATE);
    //_mainSerial.println(F("*** Debug mode enabled ***"));
  }
  _led.init(LED_PINS, LED_PINS_LENGTH, _mainSerial);
  _led.indicateStarting();
  _led.indicatePoweredOn();
  _modem.init(MODEM_RX_PIN, MODEM_TX_PIN, MODEM_BAUD_RATE, APN_NAME, APN_USER, APN_PASS, _led, _mainSerial);

  if (!_modem.connectToTCP(SERVER_ADDRES, TCP_PORT)) {
    reset();
    return;
  }

  (String(DEVICE_IDENTITY_PREFIX) + String(_modem.getImei())).toCharArray(DEVICE_IDENTITY, DEVICE_IDENTITY_LENGTH);
  _modem.sendMessage(_messaging.hello(DEVICE_IDENTITY, PASSWORD, DEVICE_MODEL));

}

void loop() {

  now = millis();
  if (now > (lastCurrTime + CURR_INTERVAL)) {
    lastCurrTime = millis();

    // Get CGNSS data, parse it, create curr message and send.
    if (!_modem.sendMessage(_messaging.currCGNS(DEVICE_IDENTITY, PASSWORD, DEVICE_MODEL, _cgnss.parseNMEAData(_modem.getCGNSSData())))) {
      reset();
    }

    //  delay(1000);

    // Get Batt data, parse it, create curr message and send.
    if (!_modem.sendMessage(_messaging.currBatt(DEVICE_IDENTITY, PASSWORD, DEVICE_MODEL, _cgnss.parseBatt(_modem.getBatteryStat())))) {
      reset();
    }

    // check for incoming sms
    // check for incoming tcp packets
  }
}
