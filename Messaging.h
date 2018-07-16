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
char HELLO[] = "hola";
char CURR[] = "curr";
const int CGNSS_START_INDEX = 101;




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
          keyval(11, HELLO)
          + keyval(12, devId)
          + keyval(13, pass)
          + keyval(14, devModel)
          + keyval(15, VERSION)
        );
    }

    String curr(char devId[], char pass[], char devModel[], String cgnsData[]) {
      /*
        0: <GNSS run status>
        1: <Fix status>
        2: <UTC date & Time>
        3: <Latitude>
        4: <Longitude>
        5: <MSL Altitude>
        6: <Speed Over Ground>
        7: <Course Over Ground>
        8: <Fix Mode>
        9: <Reserved1>
        10: <HDOP>
        11: <PDOP>
        12: <VDOP>
        13: <Reserved2>
        14: <GNSS Satellites in View>
        15: <GNSS Satellites Used>
        16: <GLONASS Satellites Used>
        17: <Reserved3>
        18: <C/N0 max>
        19: <HPA>
        20: <VPA>
      */

      t =   keyval(11, CURR)
            + keyval(12, devId)
            + keyval(13, pass)
            // + keyval(14, devModel)
            + keyval(15, VERSION);


      cgnsI = CGNSS_START_INDEX;
      for (i = 0; i < 10; i++) {

        //if (i == 1
            //|| i == 2
       //     || i == 3
      //      || i == 4
     //       || i == 5
     //       || i == 6
     //       || i == 7
     //       || i == 8
            // || i == 14
           // || i == 15
           // || i == 16
   //        ) {
          t += keyval(cgnsI, cgnsData[i]);
  //      }

        // Serial.println(keyval(cgnsI, cgnsData[i]));
        cgnsI++;
      }
      Serial.println(message(t));
      return "";
    }
};

