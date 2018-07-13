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

#include "avr/pgmspace.h"

class AT
{
  private:
    String mergeWithPrefix(String command) {
      return "AT+" + command;
    }

    String capsulateWithDoubleQuote(String val) {
      return "\"" + val + "\"";
    }
  public:
    String begin() {
      return F("AT");
    }



    // Configures the device for a single IP connection.
    // For more: http://m2msupport.net/m2msupport/atcipmux-start-up-multi-ip-connection/
    String setConnectionModeSingle() {
      return mergeWithPrefix(F("CIPMUX=0"));   // 0: Single, 1: Multi
    }


    // Sets result mode of errors.
    // mode 0: Nothing.
    // mode 1: Error code only.
    // mode 2: Error message only.
    String setResultMode(byte mode) {
      return mergeWithPrefix("CMEE=" + (String)mode);
    }

    // Returns the IMEI (International Mobile station Equipment Identity) of the mobile terminal.
    // For more: http://m2msupport.net/m2msupport/atcgsn-request-product-serial-number-identification/
    String getImei() {
      return mergeWithPrefix(F("CGSN"));
    }

    // Closes the TCP or UDP connection.
    String closeTCP() {
      return mergeWithPrefix(F("CIPCLOSE"));
    }

    // Resets the modem back to default factory settings.
    // Notice: This command should be followed by at least two seconds before the next command entered.
    String resetToFactoryDefault() {
      return F("ATZ");
    }

    // Closes GPRS PDP context.
    // For more: http://m2msupport.net/m2msupport/atcipshut-deactivate-gprs-pdp-context/
    String resetIPSession() {
      return mergeWithPrefix(F("CIPSHUT"));
    }

    // Turns on GNSS power in Simcom modules
    // For mode: http://m2msupport.net/m2msupport/at-cgnspwr-gnss-power-control/
    String enableGNSS() {
      return mergeWithPrefix(F("CGNSPWR=1"));
    }

    // Turns off GNSS power in Simcom modules
    // For mode: http://m2msupport.net/m2msupport/at-cgnspwr-gnss-power-control/
    String disableGNSS() {
      return mergeWithPrefix(F("CGNSPWR=0"));
    }

    // Defines the last NMEA sentence that parsed.
    // “GGA” refer to ”GPGGA” or "GLGGA" or "GNGGA"
    // “GSA” refer to ”GPGSA” or "GLGSA" or "GNGSA"
    // “GSV" refer to ”GPGSV” or "GLGSV" or "GNGSV"
    // “RMC” refer to ”GPRMC” or "GLRMC" or "GNRMC"
    String setCGNSSequence() {
      return mergeWithPrefix(F("CGNSSEQ=\"RMC\""));
    }

    // Set the apn, user name and password for the PDP context.
    // For more: http://m2msupport.net/m2msupport/atcstt-satrt-task-and-set-apn-username-and-password/
    String setupPDPContext(String apnName, String apnUsername, String apnPassword) {
      // return mergeWithPrefix("CSTT=" + capsulateWithDoubleQuote(F("APN")) + "," + capsulateWithDoubleQuote(apnUsername) + "," + capsulateWithDoubleQuote(apnPassword));
      return mergeWithPrefix("CSTT=" + capsulateWithDoubleQuote(apnName) + "," + capsulateWithDoubleQuote(apnUsername) + "," + capsulateWithDoubleQuote(apnPassword));
    }

    // Brings the GPRS or CSD call depending on the configuration previously set by the AT+CSTT command.
    // For more: http://m2msupport.net/m2msupport/atciicr-bring-up-gprs-or-circuit-switch-connection/
    String bringGPRSCalls() {
      return mergeWithPrefix(F("CIICR"));
    }

    // Returns the local IP address.
    // It is imperative the the PDP context must have been activated before to get the IP address.
    // For more: http://m2msupport.net/m2msupport/atcifsr-get-local-ip-address/
    String getLocalIP() {
      return mergeWithPrefix(F("CIFSR"));
    }

    // Performs a GPRS Attach.
    // The device should be attached to the GPRS network before a PDP context can be established.
    String attachGPRS() {
      return mergeWithPrefix(F("CGATT=1"));
    }

    String startTCPConnection(String address, String port) {
      return mergeWithPrefix("CIPSTART=" + capsulateWithDoubleQuote(F("TCP")) + "," + capsulateWithDoubleQuote(address) + "," + capsulateWithDoubleQuote(port));
    }
};
