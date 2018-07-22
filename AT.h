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

//  Description: "AT.h" is a helper class that includes the
//  necessary AT commands.

#include "Arduino.h"
class AT
{
  private:

    // Returns given command string with "AT+" prefix.
    String ATCommand(String command);

    // Returns given command string in double quotes.
    String capsulateWithDoubleQuote(String val);
  public:

    // Implies that the communication between the device and the
    // application has been verified.
    // For more: http://m2msupport.net/m2msupport/at-command/
    String begin();

    // Configures the device for a single IP connection.
    // For more: http://m2msupport.net/m2msupport/atcipmux-start-up-multi-ip-connection/
    String setConnectionModeSingle();


    // Sets result mode of errors.
    // mode 0: Nothing.
    // mode 1: Error code only.
    // mode 2: Error message only.
    String setResultMode(byte mode);

    // Returns the IMEI of the mobile terminal.
    // For more: http://m2msupport.net/m2msupport/atcgsn-request-product-serial-number-identification/
    String getImei();

    // Closes the TCP or UDP connection.
    String closeTCP();

    // Resets the modem back to default factory settings.
    // Notice: This command should be followed by at least two
    // seconds before the next command entered.
    String resetToFactoryDefault();

    // Closes GPRS PDP context.
    // For more: http://m2msupport.net/m2msupport/atcipshut-deactivate-gprs-pdp-context/
    String resetIPSession();

    // Turns on GNSS power in Simcom modules
    // For mode: http://m2msupport.net/m2msupport/at-cgnspwr-gnss-power-control/
    String enableGNSS();

    // Turns off GNSS power in Simcom modules
    // For mode: http://m2msupport.net/m2msupport/at-cgnspwr-gnss-power-control/
    String disableGNSS();

    // Defines the last NMEA sentence that parsed.
    // “GGA” refer to ”GPGGA” or "GLGGA" or "GNGGA"
    // “GSA” refer to ”GPGSA” or "GLGSA" or "GNGSA"
    // “GSV" refer to ”GPGSV” or "GLGSV" or "GNGSV"
    // “RMC” refer to ”GPRMC” or "GLRMC" or "GNRMC"
    String setCGNSSequence();

    // Set the apn, user name and password for the PDP context.
    // For more: http://m2msupport.net/m2msupport/atcstt-satrt-task-and-set-apn-username-and-password/
    String setupPDPContext(String apnName, String apnUsername, String apnPassword);

    // Brings the GPRS or CSD call depending on the configuration
    // previously set by the AT+CSTT command.
    // For more: http://m2msupport.net/m2msupport/atciicr-bring-up-gprs-or-circuit-switch-connection/
    String bringGPRSCalls();

    // Returns the local IP address.
    // It is imperative the the PDP context must have been
    // activated before to get the IP address.
    // For more: http://m2msupport.net/m2msupport/atcifsr-get-local-ip-address/
    String getLocalIP();

    // Performs a GPRS Attach.
    // For more: https://m2msupport.net/m2msupport/atcgatt-ps-attach-or-detach/
    String attachGPRS();

    // Starts a TCP connection.
    // For more: https://m2msupport.net/m2msupport/atcipstart-start-up-tcp-or-udp-connection/
    String startTCPConnection(String address, String port);

    // For more: http://m2msupport.net/m2msupport/atcipsend-send-data-through-tcp-or-udp-connection/
    String activateCIPSendMode();

    String disableEcho();

    // Gets GNSS data.
    String getCGNSSData();

    // Gets battery status.
    // For more: http://m2msupport.net/m2msupport/atcbc-battery-charge/
    String getBatteryStat();
};
