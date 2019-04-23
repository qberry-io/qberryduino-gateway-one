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

//  Description: Please refer to "RF.h".

#include "RF.h"
#include "Arduino.h"

RF::RF() {}
RF::RF(int rx
       , int tx
       , uint64_t pipe) {
  _rx = rx;
  _tx = tx;
  _pipe = pipe;
  _radio = new RF24(_rx, _tx); // CE, CSN
  _radio -> begin();
}

void RF::enableWriting() {
  _radio -> begin();
  _radio -> openWritingPipe(_pipe);
}

void RF::disableWriting() {
  // _radio -> closeWritingPipe(_pipe);
}

void RF::enableReading() {
  _radio -> begin();
  _radio -> openReadingPipe(0, _pipe);
  _radio -> setPALevel(RF24_PA_MIN);
  _radio -> startListening();
}

void RF::disableReading() {
  _radio -> closeReadingPipe(_pipe);
}

/*
void RF::clearCurrentMessage(){
  _currMessage = "";
}
*/

String RF::readTill(char endChar, int timeout) {

  _beginMillis = millis();
  _currMessage = "";
  
  int i = -1;

  do {
    while (_radio -> available() && (i == -1 || i == 0)) {
      _radio -> read(&_currChars, sizeof(_currChars));
      _currMessage.concat(_currChars);
      i = (String(_currChars).indexOf(String(endChar)));
    }

    // Serial.println(i);

  } while ((millis() - _beginMillis < timeout) && i == -1);

  return _currMessage;
}

void RF::write(String message) {
  int messageSize = message.length();
  Serial.println(message);
  message.concat(F(" "));
  for (int i = 0; i < messageSize; i = i + 31) {

    String part = message.substring(i, i + 32);
    char partChars[part.length()];
    part.toCharArray(partChars, part.length());

    _radio -> write(partChars, sizeof(partChars));

    Serial.println(partChars);
  }
}
