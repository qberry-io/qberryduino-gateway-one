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

//  Description: "Modem.h" is a class that includes functions to
//  manage Fona/Sim808 module.

#include <stdint.h>
#include "MainSerial.h"
#include "AT.h"
#include <SoftwareSerial.h>

class Modem
{
  private:

    static const unsigned int SS_BUFFER_SIZE = 108;
    const uint8_t DELAY_60 = 60;
    const  uint8_t DELAY_250 = 250;
    const  unsigned int DELAY_1000 = 1000;
    const  unsigned int DELAY_2000 = 2000;
    const  unsigned int DELAY_3000 = 3000;
    const  unsigned int DELAY_7000 = 7000;

    MainSerial mainSerial;
    AT at = AT();
    String ssBuffer;
    String apnName;
    char * apnUser;
    char * apnPassword;
    int i;
    char ichr;
    char imei[16];

    // TODO: Try to find another way for
    // initialization of ss.
    SoftwareSerial ss = SoftwareSerial(-1, -1);

    // Clears the serial buffer.
    void clearSerial();

    // Prints given string to the MainSerial (For dubugging).
    void printReceived(String text);

    // Prints given string to the MainSerial (For dubugging).
    void printSent(String text);

    // Returns whether the given character is a special character.
    bool isSpecialChar(char chr);

    // Writes given message to the Modem over the Serial.
    String write(String message, int delayer);

    // Writes given message to the Modem and leave a break
    // over the Serial.
    // TODO: Let them use WriteLine2!
    String writeLine(String message, int delayer);

    // Writes given message to the Modem and leave a break
    // over the Serial.
    char * writeLine2(String message, int delayer);

  public:

    // Initializes the object and gets the Modem ready for commands
    // over the Serial.
    void init(byte rx,
              byte tx,
              int baudRate,
              String apnN,
              char apnUsername[],
              char apnPass[],
              MainSerial ms);

    // Clears the buffered data on MC's memory
    void clearBuffer();

    // Gets the imei of the mobile terminal.
    char* getImei();

    // Gets the current CGNSS data from the module.
    char * getCGNSSData();

    // Gets the current battery data from the module.
    char * getBatteryStat();

    // Makes a TCP connection to given address and port.
    bool connectToTCP(char address[], int port);

    // Sends given message to the server.
    // NOTICE: The message must be formatted using "Messaging" utility.
    // And the version of the "Parser" utility that running on the server
    // must be supported the current version of protocol.
    bool sendToServer(String msg);
};
