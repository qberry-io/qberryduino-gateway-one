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

//  Description: "Messaging.cpp" is a helper class that includes
//  functions to create appropriate messages for server using
//  declared version in the local variable named PROTOCOL_VERSION.

class BatteryMessageFactory
{
  private:
    int lineI;
    int i;
    String t;

    char PROTOCOL_VERSION[6] = "1.0.0";

    const char MARKER = '$';
    const char SPLITTER = '|';

    char CURR[5] = "BATT";

    const byte MESSAGE_TYPE_KEY = 11;
    const byte DEV_ID_KEY = 12;
    const byte SECRET_KEY = 13;
    const byte DEV_MODEL_KEY = 14;
    const byte PROTOCOL_VERSION_KEY = 15;

    const int BATT_START_INDEX = 111;
    const byte BATT_LINES_LENGTH = 3;

    // Creates message based on given message.
    // (This is the last step of preparing a message to send to
    // the server.)
    String message(String msg);

    // Creates partition for given value.
    String keyval(int key, char val[]);

    // Creates partition for given value.
    String keyval(int key, String val);

  public:

    // Creates ready to send "CURR" message for Battery with given
    // parameters.
    String create(char devId[],
                    char secret[],
                    char devModel[],
                    String battData[]);
};

