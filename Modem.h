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

#include "AT.h"
#include <SoftwareSerial.h>

// const PROGMEM unsigned int SS_BUFFER_SIZE = 8;
const PROGMEM byte DELAY_250 = 250;
const PROGMEM unsigned int DELAY_1000 = 1000;
const PROGMEM unsigned int DELAY_2000 = 2000;
const PROGMEM unsigned int DELAY_3000 = 3000;
const PROGMEM unsigned int DELAY_7000 = 7000;

class Modem
{
  private:
    Led ledManager;
    MainSerial mainSerial;
    AT at = AT();
    String ssBuffer;
    String apnName;
    char * apnUser;
    char * apnPassword;
    int i;
    char ichr;

    // TODO: Try to find another way.
    SoftwareSerial ss = SoftwareSerial(-1, -1);

    void clearSerial() {
      while ( ss.available() > 0) {
        ss.read();
      }
    }

    void clearBuffer() {
      ssBuffer = "";
    }

    String WriteLine(String message, int delayer) {
      clearSerial();
      clearBuffer();

      message = message; //+ "\r\n";
      ss.println(message);
      //char c = ss.read();
      printSent(message);
      delay(delayer);

      i = 0;
      while (ss.available() != 0) {
        ichr = ss.read();
        // printReceived((String)chr);
        if (ichr != '\r'
            && ichr != '\n'
            && ichr != '\0'
            && ichr != '\b'
            && ichr != '\a'
            && ichr != '\f'
            && ichr != '\t'
            && ichr != '\v') {
          ssBuffer = ssBuffer + ichr ;
          // ssBuffer[i] = ichr;
          i++;
        }
      }
      printReceived(ssBuffer);
      return ssBuffer;
    }

    void printReceived(String text) {
      mainSerial.println("MC < Modem: " + text);
    }

    void printSent(String text) {
      mainSerial.println("MC > Modem: " + text);
    }

  public:
    void init(byte rx,
              byte tx,
              int baudRate,
              String apnN,
              char apnUsername[],
              char apnPass[],
              Led lm,
              MainSerial ms) {

      apnName = apnN;
      apnUser = apnUsername;
      apnPassword = apnPass;

      // ssBuffer.reserve(SS_BUFFER_SIZE);

      ss = SoftwareSerial(rx, tx);
      ss.begin(baudRate);
      ledManager = lm;
      mainSerial = ms;
      delay(100);

      WriteLine(at.begin(), 1000);

      delay(500);
    }

    void connectToTCP(char address[], int port) {
      // WriteLine("", DELAY_500);
      // ss.write(0x1A);
      WriteLine(at.setResultMode(2), DELAY_250);
      delay(DELAY_250);
      ledManager.indicateConnecting();
      WriteLine(at.getImei(), DELAY_250);
      delay(DELAY_250);
      ledManager.indicateConnecting();
      WriteLine(at.closeTCP(), DELAY_250);
      delay(DELAY_250);
      ledManager.indicateConnecting();
      WriteLine(at.resetToFactoryDefault(), DELAY_2000);
      delay(DELAY_250);
      ledManager.indicateConnecting();
      WriteLine(at.resetIPSession(), DELAY_250);
      delay(DELAY_250);
      ledManager.indicateConnecting();
      WriteLine(at.enableGNSS(), DELAY_250);
      delay(DELAY_250);
      ledManager.indicateConnecting();
      //CGNSTST=0
      // WriteLine(at.setCGNSSequence("RMC"), 500);
      WriteLine(at.setCGNSSequence(), DELAY_250);
      delay(DELAY_250);
      ledManager.indicateConnecting();
      WriteLine(at.setConnectionModeSingle(), DELAY_250);
      delay(DELAY_7000);
      ledManager.indicateConnecting();
      WriteLine(at.setupPDPContext(apnName, apnUser, apnPassword), DELAY_2000);
      delay(DELAY_3000);
      ledManager.indicateConnecting();

      WriteLine(at.attachGPRS(), DELAY_3000);
      delay(DELAY_3000);
      ledManager.indicateConnecting();

      WriteLine(at.bringGPRSCalls(), DELAY_1000);
      delay(DELAY_3000);
      ledManager.indicateConnecting();
      WriteLine(at.getLocalIP(), DELAY_3000);
      delay(DELAY_250);
      ledManager.indicateConnecting();
      if (WriteLine(at.startTCPConnection(address, (String) port), DELAY_3000).lastIndexOf(F("CONNECT OK")) > 0) {
        ledManager.indicateConnected();
      } else {
        ledManager.indicateConnectionError();
      }
      delay(DELAY_250);

    }
};
