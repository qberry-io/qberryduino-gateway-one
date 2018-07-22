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

#include "Modem.h"
#include "Arduino.h"

void Modem::clearSerial() {
  while (ss.available() > 0) {
    ss.read();
  }
}

void Modem::printReceived(String text) {
  mainSerial.println(text);
}

void Modem::printSent(String text) {
  mainSerial.println(text);
}

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

String Modem::write(String message, int delayer) {
  clearSerial();
  clearBuffer();

  ss.print(message);
  ss.write(0x1A);
  printSent(message);
  delay(delayer);

  i = 0;
  //Serial.println("$$$");
  while (ss.available() != 0) {

    ichr = ss.read();
    if (!isSpecialChar(ichr)) {
      ssBuffer = (ssBuffer + ichr);
      i++;
    }

  }
  //Serial.println("&&&");
  printReceived(ssBuffer);
  return ssBuffer;
}

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

void Modem::clearBuffer() {
  ssBuffer = "";
}

// Gets the imei of the mobile terminal.
char* Modem::getImei() {
  return imei;
}

// Gets CGNSS data from the module..
char * Modem::getCGNSSData() {
  //static char cgnssResp [256] = "";
  // WriteLine(at.getCGNSSData(), DELAY_60).toCharArray(cgnssResp, 256);
  return writeLine2(at.getCGNSSData(), DELAY_60);
  //return cgnssResp;
}

char * Modem::getBatteryStat() {
  return writeLine2(at.getBatteryStat(), DELAY_250);
}

// Makes a TCP connection to given address and port.
boolean Modem::connectToTCP(char address[], int port) {
  // WriteLine("", DELAY_500);
  // ss.write(0x1A);
  writeLine(at.setResultMode(2), DELAY_250);
  delay(DELAY_250);
  //ledManager.indicateConnecting();

  String(writeLine(at.getImei(), DELAY_250)).substring(0, 16).toCharArray(imei, 16);

  delay(DELAY_250);
  //ledManager.indicateConnecting();
  writeLine(at.closeTCP(), DELAY_250);
  delay(DELAY_250);
  //ledManager.indicateConnecting();
  writeLine(at.resetIPSession(), DELAY_250);
  delay(DELAY_250);
  //ledManager.indicateConnecting();
  writeLine(at.enableGNSS(), DELAY_250);
  delay(DELAY_250);
  //ledManager.indicateConnecting();
  //CGNSTST=0
  // WriteLine(at.setCGNSSequence("RMC"), 500);
  writeLine(at.setCGNSSequence(), DELAY_250);
  delay(DELAY_250);
  //ledManager.indicateConnecting();
  writeLine(at.setConnectionModeSingle(), DELAY_250);
  delay(DELAY_7000);
  //ledManager.indicateConnecting();
  writeLine(at.setupPDPContext(apnName, apnUser, apnPassword), DELAY_2000);
  delay(DELAY_3000);
  //ledManager.indicateConnecting();

  writeLine(at.attachGPRS(), DELAY_3000);
  delay(DELAY_3000);
  //ledManager.indicateConnecting();

  writeLine(at.bringGPRSCalls(), DELAY_1000);
  delay(DELAY_3000);
  //ledManager.indicateConnecting();
  writeLine(at.getLocalIP(), DELAY_3000);
  delay(DELAY_250);
  //ledManager.indicateConnecting();

  if (writeLine(at.startTCPConnection(address, (String) port), DELAY_3000).lastIndexOf(F("CONNECT OK")) > -1) {
    //ledManager.indicateConnected();
    delay(DELAY_250);
    return true;
  } else {
    //ledManager.indicateConnectionError();
    delay(DELAY_250);
    return false;
  }
}

boolean Modem::sendToServer(String msg) {
  boolean success = writeLine(at.activateCIPSendMode(), DELAY_1000).lastIndexOf(F("CIPSENDERROR")) == -1;
  if (success) {
    write(msg, DELAY_250);
  }

  return success;
}

