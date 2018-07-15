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
const char MARKER = '$';
const char SPLITTER = '|';
char HELLO[] = "hello";
char CURR[] = "curr";
const int CGNSS_START_INDEX = 1001;




class Messaging
{
  private:
    int cgnsI;
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
          keyval(101, HELLO)
          + keyval(102, devId)
          + keyval(103, pass)
          + keyval(104, devModel)
          + keyval(105, VERSION)
        );
    }

    String curr(char devId[], char pass[], char devModel[], String cgnsData[]) {
      /*
        <GNSS run status>
        <Fix status>
        <UTC date & Time>
        <Latitude>
        <Longitude>
        <MSL Altitude>
        <Speed Over Ground>
        <Course Over Ground>
        <Fix Mode>
        <Reserved1>
        <HDOP>
        <PDOP>
        <VDOP>
        <Reserved2>
        <GNSS Satellites in View>
        <GNSS Satellites Used>
        <GLONASS Satellites Used>
        <Reserved3>
        <C/N0 max>
        <HPA>
        <VPA>
      */

      t =   keyval(101, CURR)
            + keyval(102, devId)
            + keyval(103, pass);
           // + keyval(104, devModel)
          //  + keyval(105, VERSION);


      cgnsI = CGNSS_START_INDEX;
      for (i = 0; i < 20; i++) {

       if (i == 1
            //|| i == 2
           || i == 3
          || i == 4
            // || i == 5
            // || i == 6
            //  || i == 7
            //  || i == 8
            //|| i == 14
            //|| i == 15
  //          || i == 16
            ) {
           t += keyval(cgnsI, cgnsData[i]);
        }

        // Serial.println(keyval(cgnsI, cgnsData[i]));
        cgnsI++;
      }
      Serial.println(message(t));
      return "";
    }
};

