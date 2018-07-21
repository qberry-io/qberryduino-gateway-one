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

//  Description: "AT.cpp" is a helper class that includes the
//  necessary AT commands.


#include "Arduino.h"
#include "AT.h"

// Returns given command string with "AT+" prefix.
String AT:: ATCommand(String command) {
  return "AT+" + command;
}

// Returns given command string in double quotes.
String AT:: capsulateWithDoubleQuote(String val) {
  return "\"" + val + "\"";
}

// Implies that the communication between the device and the
// application has been verified.
// For more: http://m2msupport.net/m2msupport/at-command/
String AT:: begin() {
  return F("AT");
}

// Configures the device for a single IP connection.
// For more: http://m2msupport.net/m2msupport/atcipmux-start-up-multi-ip-connection/
String AT::setConnectionModeSingle() {
  return ATCommand(F("CIPMUX=0"));   // 0: Single, 1: Multi
}

// Sets result mode of errors.
// mode 0: Nothing.
// mode 1: Error code only.
// mode 2: Error message only.
String AT::setResultMode(byte mode) {
  return ATCommand("CMEE=" + (String)mode);
}

// Returns the IMEI (International Mobile station Equipment Identity) of the mobile terminal.
// For more: http://m2msupport.net/m2msupport/atcgsn-request-product-serial-number-identification/
String AT::getImei() {
  return ATCommand(F("CGSN"));
}

// Closes the TCP or UDP connection.
String AT::closeTCP() {
  return ATCommand(F("CIPCLOSE"));
}

// Resets the modem back to default factory settings.
// Notice: This command should be followed by at least two
// seconds before the next command entered.
String AT::resetToFactoryDefault() {
  return F("ATZ");
}

// Closes GPRS PDP context.
// For more: http://m2msupport.net/m2msupport/atcipshut-deactivate-gprs-pdp-context/
String AT::resetIPSession() {
  return ATCommand(F("CIPSHUT"));
}

// Turns on GNSS power in Simcom modules
// For mode: http://m2msupport.net/m2msupport/at-cgnspwr-gnss-power-control/
String AT::enableGNSS() {
  return ATCommand(F("CGNSPWR=1"));
}

// Defines the last NMEA sentence that parsed.
// “GGA” refer to ”GPGGA” or "GLGGA" or "GNGGA"
// “GSA” refer to ”GPGSA” or "GLGSA" or "GNGSA"
// “GSV" refer to ”GPGSV” or "GLGSV" or "GNGSV"
// “RMC” refer to ”GPRMC” or "GLRMC" or "GNRMC"
String AT::setCGNSSequence() {
  return ATCommand(F("CGNSSEQ=\"RMC\""));
}

// Set the apn, user name and password for the PDP context.
// For more: http://m2msupport.net/m2msupport/atcstt-satrt-task-and-set-apn-username-and-password/
String AT::setupPDPContext(String apnName, String apnUsername, String apnPassword) {
  // return ATCommand("CSTT=" + capsulateWithDoubleQuote(F("APN")) + "," + capsulateWithDoubleQuote(apnUsername) + "," + capsulateWithDoubleQuote(apnPassword));
  return ATCommand("CSTT=" + capsulateWithDoubleQuote(apnName) + "," + capsulateWithDoubleQuote(apnUsername) + "," + capsulateWithDoubleQuote(apnPassword));
}

// Brings the GPRS or CSD call depending on the configuration
// previously set by the AT+CSTT command.
// For more: http://m2msupport.net/m2msupport/atciicr-bring-up-gprs-or-circuit-switch-connection/
String AT::bringGPRSCalls() {
  return ATCommand(F("CIICR"));
}

// Returns the local IP address.
// It is imperative the the PDP context must have been activated before to get the IP address.
// For more: http://m2msupport.net/m2msupport/atcifsr-get-local-ip-address/
String AT::getLocalIP() {
  return ATCommand(F("CIFSR"));
}

// Performs a GPRS Attach.
// For more: https://m2msupport.net/m2msupport/atcgatt-ps-attach-or-detach/
String AT::attachGPRS() {
  return ATCommand(F("CGATT=1"));
}

// Starts a TCP connection.
// For more: https://m2msupport.net/m2msupport/atcipstart-start-up-tcp-or-udp-connection/
String AT::startTCPConnection(String address, String port) {
  return ATCommand("CIPSTART=" + capsulateWithDoubleQuote(F("TCP")) + "," + capsulateWithDoubleQuote(address) + "," + capsulateWithDoubleQuote(port));
}

// Sends data over the TCP or UDP.
// For more: http://m2msupport.net/m2msupport/atcipsend-send-data-through-tcp-or-udp-connection/
String AT::activateCIPSendMode() {
  return ATCommand(F("CIPSEND"));
}

// Gets GNSS data.
String AT::getCGNSSData() {
  return ATCommand(F("CGNSINF"));
}

// Gets battery status.
// For more: http://m2msupport.net/m2msupport/atcbc-battery-charge/
String AT::getBatteryStat() {
  return ATCommand(F("CBC"));
}
