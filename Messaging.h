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

char VERSION[] = "1.0.0";
const PROGMEM char MARKER = '$';
const PROGMEM char SPLITTER = '|';
char HELLO[] = "hola";
char CURR[] = "curr";
const PROGMEM int CGNSS_START_INDEX = 211;
const PROGMEM int BATT_START_INDEX = 111;
const PROGMEM byte CGNSS_LINES_LENGTH = 8;
const PROGMEM byte BATT_LINES_LENGTH = 3;

const PROGMEM byte MESSAGE_TYPE_KEY = 11;
const PROGMEM byte DEV_ID_KEY = 12;
const PROGMEM byte PASS_KEY = 13;
const PROGMEM byte DEV_MODEL_KEY = 14;
const PROGMEM byte VERSION_KEY = 15;

class Messaging
{
  private:
    int lineI;
    int i;
    String t;

    String message(String msg) {
      return
        String(MARKER)
        + String(msg)
        + String(SPLITTER)
        + String(MARKER);
    }

    String keyval(int key, char val[]) {
      return
        String(SPLITTER)
        + String(key)
        + String(SPLITTER)
        + String(val);
    }

    String keyval(int key, String val) {
      return
        String(SPLITTER)
        + String(key)
        + String(SPLITTER)
        + val;
    }

  public:
    String hello(char devId[], char pass[], char devModel[]) {
      return
        message(
          keyval(MESSAGE_TYPE_KEY, HELLO)
          + keyval(DEV_ID_KEY, devId)
          + keyval(PASS_KEY, pass)
          + keyval(DEV_MODEL_KEY, devModel)
          + keyval(VERSION_KEY, VERSION)
        );
    }

    String currCGNS(char devId[], char pass[], char devModel[], String cgnsData[]) {

      t =   keyval(MESSAGE_TYPE_KEY, CURR)
            + keyval(DEV_ID_KEY, devId)
            + keyval(PASS_KEY, pass)
            + keyval(VERSION_KEY, VERSION);

      lineI = CGNSS_START_INDEX;
      for (i = 0; i < CGNSS_LINES_LENGTH; i++) {
        t += keyval(lineI, cgnsData[i]);
        lineI++;
      }
      return message(t);
    }

    String currBatt(char devId[], char pass[], char devModel[], String battData[]) {

      t =   keyval(11, CURR)
            + keyval(12, devId)
            + keyval(13, pass)
            + keyval(15, VERSION);

      lineI = BATT_START_INDEX;
      for (i = 0; i < BATT_LINES_LENGTH; i++) {
        t += keyval(lineI, battData[i]);
        lineI++;
      }
      return message(t);
    }
};

