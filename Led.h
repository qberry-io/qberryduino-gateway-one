//  Copyright (c) 2018-present, Deniz KANMAZ  All rights reserved.
//  This source code is licensed under the GNU GENERAL PUBLIC
//  LICENCE V3. Use of this source code is governed by a license
//  that can be found in the LICENSE file.

//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//	LICENSE file for more details.

//	You should have received a copy of the LICENSE file along with
//	with this program. If not, see <http://www.gnu.org/licenses/>.

//	E-mail: denizkanmaz@gmail.com


class Led
{
  private:
    MainSerial mainSerialManager;
  
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

  public:
    void init(byte * lPins, byte lPinsLength, MainSerial msManager) {
      ledPins = lPins;
      ledPinsLength = lPinsLength;
      mainSerialManager = msManager;
      
      for (i = 0; i < ledPinsLength; i++) {
        
        pinMode(ledPins[i], OUTPUT);
        digitalWrite(ledPins[i], LOW);
      }
    }

    void indicateStarting() {

      mainSerialManager.println("starting");

      for (i = 0; i < ledPinsLength; i++) {
        mainSerialManager.println((String)ledPins[i]);
        digitalWrite(ledPins[i], HIGH);
        delay(250);
        digitalWrite(ledPins[i], LOW);
        mainSerialManager.println((String)ledPins[i]);
      }

    }

    // Blinks Yellow indicators only one time.
    void indicateConnecting() {
      digitalWrite(getYellowLedPin(), HIGH);
      delay(250);
      digitalWrite(getYellowLedPin(), LOW);
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

