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

//  Description: "LED.h" is a helper class that includes functions
//  for indication using LEDs.

const int PROGMEM SHORT = 100;
const int PROGMEM LONG = 500;

class LED
{
  private:
    MainSerial mainSerial;
    byte ledPinsLength;
    byte * ledPins;
    int i;

    // Gets the Red indicator pin.
    byte getRedLedPin() {
      return ledPins[0];
    }

    // Gets the Yellow indicator pin.
    byte getYellowLedPin() {
      return ledPins[1];
    }

    // Gets the Blue indicator pin.
    byte getBlueLedPin() {
      return ledPins[3];
    }

    // Writes LOW to given pin number.
    void writeLow(byte ledPin) {
      digitalWrite(ledPin, LOW);
    }

    // Writes HIGH to given pin number.
    void writeHigh(byte ledPin) {
      digitalWrite(ledPin, HIGH);
    }

  public:
  
    // Initializes the helper.
    void init(byte * lPins, byte lPinsLength, MainSerial ms) {
      ledPins = lPins;
      ledPinsLength = lPinsLength;
      mainSerial = ms;

      for (i = 0; i < ledPinsLength; i++) {
        pinMode(ledPins[i], OUTPUT);
        writeLow(ledPins[i]);
      }
    }

    // Blinks all the indicators with an order from up to down.
    void indicateStarting() {
      for (i = 0; i < ledPinsLength; i++) {
        writeHigh(ledPins[i]);
        delay(250);
        writeLow(ledPins[i]);
      }
    }

    // Blinks the Yellow indicator only one time with a
    // SHORT interval.
    // .
    void indicateConnecting() {
      writeHigh(getYellowLedPin());
      delay(SHORT);
      writeLow(getYellowLedPin());
    }

    // Blinks the Blue indicator only one time with a
    // SHORT interval.
    // .
    void indicateTCPSendSuccess() {
      writeHigh(getBlueLedPin());
      delay(SHORT);
      writeLow(getBlueLedPin());
    }

    // Blinks the Red and the Blue indicator four times with a
    // LONG interval.
    // _ _ _ _
    void indicateTCPSendFailed() {
      for (i = 0; i < 4; i++) {
        digitalWrite(getBlueLedPin(), HIGH);
        delay(LONG);
        digitalWrite(getBlueLedPin(), LOW);
        delay(LONG);
      }
    }

    // Blinks the Red and the Yellow indicatators together
    // four times with a LONG interval.
    // _ _ _ _
    void indicateConnectionError() {
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
    void indicatePoweredOn() {
      writeHigh(getRedLedPin());
    }

    // Powers on the Yellow indicator indefinitely.
    void indicateConnected() {
      writeHigh(getYellowLedPin());
    }

    // Powers off the Yellow indicators indefinitely.
    void indicateDisconnected() {
      writeLow(getYellowLedPin());
    }
};

