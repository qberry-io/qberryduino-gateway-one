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

//  Description: "Messaging.h" is a helper class that includes functions
//  to create appropriate messages for server using declared version in
//  the local variable named PROTOCOL_VERSION.



class Messaging
{
  private:
    int lineI;
    int i;
    String t;

    char PROTOCOL_VERSION[6] = "1.0.0";
    const char MARKER = '$';
    const char SPLITTER = '|';
    char HOLA[5] = "hola";
    char CURR[5] = "curr";
    const  int CGNSS_START_INDEX = 211;
    const  int BATT_START_INDEX = 111;
    const  byte CGNSS_LINES_LENGTH = 8;
    const  byte BATT_LINES_LENGTH = 3;

    const  byte MESSAGE_TYPE_KEY = 11;
    const  byte DEV_ID_KEY = 12;
    const  byte PASS_KEY = 13;
    const  byte DEV_MODEL_KEY = 14;
    const  byte PROTOCOL_VERSION_KEY = 15;

    String message(String msg);

    String keyval(int key, char val[]);

    String keyval(int key, String val);

  public:
    String hello(char devId[], char pass[], char devModel[]);

    String currCGNS(char devId[], char pass[], char devModel[], String cgnsData[]);

    String currBatt(char devId[], char pass[], char devModel[], String battData[]);
};

