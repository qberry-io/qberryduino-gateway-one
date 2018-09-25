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

//  Description: Please refer to "Modem.h".

#include "Modem.h"
#include "Arduino.h"

// Clears the serial buffer.
void Modem::clearSerial() {
  while (ss.available() > 0) {
    ss.read();
  }
}

// Prints given string to the MainSerial (For dubugging).
void Modem::printReceived(String text) {
  mainSerial.println(text);
}

// Prints given string to the MainSerial (For dubugging)
void Modem::printSent(String text) {
  mainSerial.println(text);
}

// Returns whether the given character is a special character.
boolean Modem::isSpecialChar(char chr) {
  return ichr == '\r'
         || ichr == '\n'
         || ichr == '\0'
         || ichr == '\b'
         || ichr == '\a'
         || ichr == '\f'
         || ichr == '\t'
         || ichr == '\v';
}

// Writes given message to the Modem over the Serial.
String Modem::write(String message, int delayer) {
  clearSerial();
  clearBuffer();

  ss.print(message);
  ss.write(0x1A);
  printSent(message);
  delay(delayer);

  i = 0;
  while (ss.available() != 0) {

    ichr = ss.read();
    if (!isSpecialChar(ichr)) {
      ssBuffer = (ssBuffer + ichr);
      i++;
    }

  }
  printReceived(ssBuffer);
  return ssBuffer;
}

// Writes given message to the Modem and leave a break
// over the Serial.
// TODO: Let them use WriteLine2!
String Modem::writeLine(String message, int delayer) {
  clearSerial();
  clearBuffer();

  ss.println(message);
  printSent(message);
  delay(delayer);

  i = 0;
  while (ss.available() != 0) {

    ichr = ss.read();
    // printReceived((String)chr);
    if (!isSpecialChar(ichr)) {
      ssBuffer = (ssBuffer + ichr);
      i++;
    }

  }
  printReceived(ssBuffer);
  return ssBuffer;
}

// Writes given message to the Modem and leave a break
// over the Serial.
char * Modem::writeLine2(String message, int delayer) {
  clearSerial();
  ss.println(message);
  printSent(message);
  delay(delayer);

  static char ssBuffer2 [SS_BUFFER_SIZE];

  i = 0;
  while (ss.available() != 0) {
    ichr = ss.read();
    if (!isSpecialChar(ichr)) {
      ssBuffer2[i] = ichr;
      i++;
    }
  }
  printReceived(ssBuffer2);
  return ssBuffer2;
}

// Initializes the object and gets the Modem ready for commands
// over the Serial.
void Modem::init(byte rx,
                 byte tx,
                 int baudRate,
                 String apnN,
                 char apnUsername[],
                 char apnPass[],
                 MainSerial ms) {

  apnName = apnN;
  apnUser = apnUsername;
  apnPassword = apnPass;

  // ssBuffer.reserve(SS_BUFFER_SIZE);

  ss = SoftwareSerial(rx, tx);
  ss.begin(baudRate);
  mainSerial = ms;
  delay(100);

  writeLine(at.begin(), DELAY_1000);
  writeLine(at.resetToFactoryDefault(), DELAY_2000);
  writeLine(at.begin(), DELAY_1000);
  writeLine(at.disableEcho(), DELAY_1000);

  delay(500);
}

// Clears the buffered data on MC's memory.
void Modem::clearBuffer() {
  ssBuffer = "";
}

// Gets the imei of the mobile terminal.
char* Modem::getImei() {
  return imei;
}

// Gets the current CGNSS data from the module.
char * Modem::getCGNSSData() {
  return writeLine2(at.getCGNSSData(), DELAY_60);
}

// Gets the current battery data from the module.
char * Modem::getBatteryStat() {
  return writeLine2(at.getBatteryStat(), DELAY_250);
}

// Makes a TCP connection to given address and port.
boolean Modem::connectToTCP(char address[], int port) {
  writeLine(at.setResultMode(2), DELAY_250);
  delay(DELAY_250);

  String(writeLine(
           at.getImei(),
           DELAY_250)).substring(0, 16)
  .toCharArray(imei, 16);

  delay(DELAY_250);
  writeLine(at.closeTCP(), DELAY_250);
  delay(DELAY_250);
  writeLine(at.resetIPSession(), DELAY_250);
  delay(DELAY_250);
  writeLine(at.enableGNSS(), DELAY_250);
  delay(DELAY_250);
  writeLine(at.setCGNSSequence(), DELAY_250);
  delay(DELAY_250);
  writeLine(at.setConnectionModeSingle(), DELAY_250);
  delay(DELAY_7000);
  writeLine(at.setupPDPContext(apnName,
                               apnUser,
                               apnPassword), DELAY_2000);
  delay(DELAY_3000);
  writeLine(at.attachGPRS(), DELAY_3000);
  delay(DELAY_3000);
  writeLine(at.bringGPRSCalls(), DELAY_1000);
  delay(DELAY_3000);
  writeLine(at.getLocalIP(), DELAY_3000);
  delay(DELAY_250);

  if (writeLine(at.startTCPConnection(address, (String) port),
                DELAY_3000).lastIndexOf(F("CONNECT OK")) > -1) {
    delay(DELAY_250);
    return true;
  } else {
    delay(DELAY_250);
    return false;
  }
}

// Sends given message to the server.
// NOTICE: The message must be formatted using "Messaging" utility.
// And the version of the "Parser" utility that running on the server
// must be supported the current version of protocol.
boolean Modem::sendToServer(String msg) {
  boolean success = writeLine(at.activateCIPSendMode(),
                              DELAY_1000)
                    .lastIndexOf(F("not allowed")) == -1;
  if (success) {
    write(msg, DELAY_250);
  }

  return success;
}

