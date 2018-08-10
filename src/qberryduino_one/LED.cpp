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

//  Description: Please refer to "LED.h"
 
#include "LED.h"
#include "Arduino.h"

// Gets the Red indicator pin.
uint8_t LED::getRedLedPin() {
  return ledPins[0];
}

// Gets the Yellow indicator pin.
uint8_t LED::getYellowLedPin() {
  return ledPins[1];
}

// Gets the Blue indicator pin.
uint8_t LED::getBlueLedPin() {
  return ledPins[3];
}

// Writes LOW to given pin number.
void LED::writeLow(uint8_t ledPin) {
  digitalWrite(ledPin, LOW);
}

// Writes HIGH to given pin number.
void LED::writeHigh(uint8_t ledPin) {
  digitalWrite(ledPin, HIGH);
}

// Initializes the helper.
void LED::init(uint8_t * lPins, uint8_t lPinsLength) {
  ledPins = lPins;
  ledPinsLength = lPinsLength;

  for (i = 0; i < ledPinsLength; i++) {
    pinMode(ledPins[i], OUTPUT);
    writeLow(ledPins[i]);
  }
}

// Blinks all the indicators with an order from up to down.
void LED::indicateStarting() {
  for (i = 0; i < ledPinsLength; i++) {
    writeHigh(ledPins[i]);
    delay(250);
    writeLow(ledPins[i]);
  }
}

// Blinks the Yellow indicator only one time with a
// SHORT interval.
// .
void LED::indicateConnecting() {
  writeHigh(getYellowLedPin());
  delay(SHORT);
  writeLow(getYellowLedPin());
}

// Blinks the Blue indicator only one time with a
// SHORT interval.
// .
void LED::indicateTCPSendSuccess() {
  writeHigh(getBlueLedPin());
  delay(SHORT);
  writeLow(getBlueLedPin());
}

// Blinks the Red and the Blue indicator four times with a
// LONG interval.
// _ _ _ _
void LED::indicateTCPSendFailed() {
  for (i = 0; i < 4; i++) {
    writeHigh(getBlueLedPin());
    delay(LONG);
    writeLow(getBlueLedPin());
    delay(LONG);
  }
}

// Blinks the Red and the Yellow indicatators together
// four times with a LONG interval.
// _ _ _ _
void LED::indicateConnectionError() {
  for (i = 0; i < 4; i++) {
    writeHigh(getRedLedPin());
    writeHigh(getYellowLedPin());
    delay(LONG);
    writeLow(getRedLedPin());
    writeLow(getYellowLedPin());
    delay(LONG);
  }
}

// Powers on Red indicators indefinitely.
void LED::indicatePoweredOn() {
  writeHigh(getRedLedPin());
}

// Powers on the Yellow indicator indefinitely.
void LED::indicateConnected() {
  writeHigh(getYellowLedPin());
}

// Powers off the Yellow indicators indefinitely.
void LED::indicateDisconnected() {
  writeLow(getYellowLedPin());
}

