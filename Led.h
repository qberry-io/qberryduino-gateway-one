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

class LED
{
  private:
    MainSerial mainSerial;
    byte ledPinsLength;
    byte * ledPins;
    int i;

    // Helpers
    byte getRedLedPin() {
      return ledPins[0];
    }

    byte getYellowLedPin() {
      return ledPins[1];
    }

    byte getBlueLedPin() {
      return ledPins[3];
    }

  public:
    void init(byte * lPins, byte lPinsLength, MainSerial ms) {
      ledPins = lPins;
      ledPinsLength = lPinsLength;
      mainSerial = ms;

      for (i = 0; i < ledPinsLength; i++) {

        pinMode(ledPins[i], OUTPUT);
        digitalWrite(ledPins[i], LOW);
      }
    }

    void indicateStarting() {

      for (i = 0; i < ledPinsLength; i++) {
        // mainSerialManager.println((String)ledPins[i]);
        digitalWrite(ledPins[i], HIGH);
        delay(250);
        digitalWrite(ledPins[i], LOW);
        // mainSerialManager.println((String)ledPins[i]);
      }
    }

    // Blinks Yellow indicators only one time.
    void indicateConnecting() {
      digitalWrite(getYellowLedPin(), HIGH);
      delay(250);
      digitalWrite(getYellowLedPin(), LOW);
      delay(250);
    }

    // Blinks the blue indicator only one time.
    void indicateTCPSendSuccess() {
      digitalWrite(getBlueLedPin(), HIGH);
      delay(500);
      digitalWrite(getBlueLedPin(), LOW);
      delay(500);
    }

    
    void indicateTCPSendFailed() {
      digitalWrite(getBlueLedPin(), HIGH);
      delay(250);
      digitalWrite(getBlueLedPin(), LOW);
      delay(250);
      digitalWrite(getBlueLedPin(), HIGH);
      delay(250);
      digitalWrite(getBlueLedPin(), LOW);
      delay(250);
    }

    // Powers on Red indicators indefinitely.
    void indicatePoweredOn() {
      digitalWrite(getRedLedPin(), HIGH);
    }

    // Powers on Yellow indicators indefinitely.
    void indicateConnected() {
      digitalWrite(getYellowLedPin(), HIGH);
    }

    // Powers off the yellow indicators indefinitely.
    void indicateDisconnected() {
      digitalWrite(getYellowLedPin(), LOW);
    }

    // Blinks Red and Yellow indicatators four times.
    void indicateConnectionError() {

      for (i = 0; i < 4; i++) {
        digitalWrite(getRedLedPin(), HIGH);
        digitalWrite(getYellowLedPin(), HIGH);
        delay(1000);
        digitalWrite(getRedLedPin(), LOW);
        digitalWrite(getYellowLedPin(), LOW);
        delay(250);
      }

    }
};

