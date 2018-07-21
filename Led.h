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


#include <stdint.h>

class LED
{
  private:
  int SHORT = 100;
  int  LONG = 500;
    uint8_t ledPinsLength;
    uint8_t * ledPins;
    int i;

    // Gets the Red indicator pin.
    uint8_t getRedLedPin();

    // Gets the Yellow indicator pin.
    uint8_t getYellowLedPin();

    // Gets the Blue indicator pin.
    uint8_t getBlueLedPin();

    // Writes LOW to given pin number.
    void writeLow(uint8_t ledPin);

    // Writes HIGH to given pin number.
    void writeHigh(uint8_t ledPin);

  public:
  
    // Initializes the helper.
    void init(uint8_t * lPins, uint8_t lPinsLength);

    // Blinks all the indicators with an order from up to down.
    void indicateStarting();

    // Blinks the Yellow indicator only one time with a
    // SHORT interval.
    // .
    void indicateConnecting();

    // Blinks the Blue indicator only one time with a
    // SHORT interval.
    // .
    void indicateTCPSendSuccess();

    // Blinks the Red and the Blue indicator four times with a
    // LONG interval.
    // _ _ _ _
    void indicateTCPSendFailed();

    // Blinks the Red and the Yellow indicatators together
    // four times with a LONG interval.
    // _ _ _ _
    void indicateConnectionError();

    // Powers on Red indicators indefinitely.
    void indicatePoweredOn();

    // Powers on the Yellow indicator indefinitely.
    void indicateConnected();

    // Powers off the Yellow indicators indefinitely.
    void indicateDisconnected();
};

