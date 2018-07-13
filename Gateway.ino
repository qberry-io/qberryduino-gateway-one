//  Copyright (c) 2018-present, Deniz KANMAZ  All rights reserved.
//  This source code is licensed under the GNU GENERAL PUBLIC
//  LICENCE V3. Use of this source code is governed by a license
//  that can be found in the LICENSE file.

//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  LICENSE file for more details.

//  You should have received a copy of the LICENSE file along with
//  with this program. If not, see <http://www.gnu.org/licenses/>.

//  E-mail: denizkanmaz@gmail.com

#include "MainSerial.h"
#include "Led.h"
#include "Modem.h"
/*
  serial.h
  leds.h
  messaging.h
  messagingTDOne.h
  tracking.h
  modem.h
*/


Led _led;
MainSerial _mainSerial;
Modem _modem;


// Definitions of development / maintenance stuff
const PROGMEM boolean DEBUG_MODE = true;
const PROGMEM int SERIAL_BAUD_RATE = 9600;

// Definitions of device
const char * DEVICE_MODEL = "";

// Definitions of leds
const PROGMEM byte LED_PINS_LENGTH = 4;
byte LED_PINS[LED_PINS_LENGTH] = { 5, 4, 3, 2 };

// Definitions of modem
const PROGMEM byte MODEM_RX_PIN = 8;
const PROGMEM byte MODEM_TX_PIN = 7;
const PROGMEM int MODEM_BAUD_RATE = 9600;

// Definitions of RF
// const byte RF_RX_PIN = 9;
// const byte RF_TX_PIN = 10;
// const uint64_t rfPipe = 0xE8E8F0F0E1LL;

// Current State
int i; // Used in loops only



void initSerial() {
  Serial.begin(SERIAL_BAUD_RATE);
}

void initModem() {
  _led.indicateConnecting();
  //step1();

  _led.indicateConnecting();
  //step2();

  _led.indicateConnecting();
  //step3();

  if (true) {
    _led.indicateConnected();
  } else {
    _led.indicateConnectionError();
  }
}



void setup() {
  if (DEBUG_MODE) {
    _mainSerial.init(SERIAL_BAUD_RATE);
    _mainSerial.println(F("*** Debug mode enabled ***"));
  }
  _led.init(LED_PINS, LED_PINS_LENGTH, _mainSerial);
  _led.indicateStarting();
  _led.indicatePoweredOn();
  _modem.init(MODEM_RX_PIN, MODEM_TX_PIN, MODEM_BAUD_RATE, _led);
}

void loop() {
  // put your main code here, to run repeatedly:

}
