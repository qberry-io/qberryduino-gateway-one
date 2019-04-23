//  Copyright (c) 2019-present, Deniz Kanmaz. All rights reserved.
//  This source code is licensed under the GNU GENERAL PUBLIC
//  LICENCE V3. Use of this source code is governed by a license
//  that can be found in the LICENSE file.

//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  LICENSE file for more details.

//  You should have received a copy of the LICENSE file along with
//  this program. If not, see <http://www.gnu.org/licenses/>.

//	Description: "RF.h" is a helper class that includes functions
//  to use functionalities of RF24L01 transeiver. More details,
//  refer to documentation of the wrapped library:
//  http://tmrh20.github.io/RF24/classRF24.html

#include <stdint.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "Arduino.h"

class RF
{
  private:
    int _rx;
    int _tx;
    uint64_t _pipe;

    RF24* _radio;

    char _currChars[32];
    unsigned long _beginMillis;
    String _currMessage;

  public:
    RF(int rx, int tx, uint64_t pipe);
    RF();
    void enableWriting();
    void disableWriting();
    void enableReading();
    void disableReading();
    
    // Reads the incoming messages comes throught
    // the pipe till the end character comes or
    // the time is out.
    String readTill(char endChar, int timeout);
    void write(String message);
    // void clearCurrentMessage();
};
