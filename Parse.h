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

const PROGMEM byte LINES_LENGTH = 12;
static String s[LINES_LENGTH];

class Parse {
  private:
    int lineIndex = 0;
    int rawCharIndex = 0;
    int i;
  public:

    static void clear() {
      int i;
      for (i = 0; i < LINES_LENGTH; i++) {
        s[i] = "";
      }
    }


    static String* parseNMEAData2(char* rawNMEAData, char * rawBattData) {
      Serial.println("+++");
      Serial.println(rawBattData);
      Serial.println("+++");
      Serial.println("===");
      Serial.println(rawNMEAData);
      Serial.println("===");

      clear();

      int actualLineIndex = 0;
      int lineIndex = 0;
      int rawCharIndex = 0;


      for (rawCharIndex = 0; rawCharIndex < String(rawNMEAData).length(); rawCharIndex++) {

        if (String(rawNMEAData[rawCharIndex]) == ",") {
          //Serial.println("comma");
          lineIndex++;


          if (lineIndex == 1
              //|| lineIndex == 2
              || lineIndex == 3
              || lineIndex == 4
              || lineIndex == 5
              || lineIndex == 6
              || lineIndex == 7
              || lineIndex == 8
              || lineIndex == 14
              || lineIndex == 15
              || lineIndex == 16
             ) {
            actualLineIndex++;
          }

          continue;
        }



        if (lineIndex == 1
            //|| lineIndex == 2
            || lineIndex == 3
            || lineIndex == 4
            || lineIndex == 5
            || lineIndex == 6
            || lineIndex == 7
            || lineIndex == 8
            || lineIndex == 14
            || lineIndex == 15
            || lineIndex == 16
           ) {
          s[actualLineIndex] += String(rawNMEAData[rawCharIndex]);
          Serial.println(s[actualLineIndex]);
        }

        /*
                if (lineIndex == 0) {
                  // TODO: Try to find an efficient way.
                  s[lineIndex] = String(rawNMEAData[rawCharIndex]);
                  //Serial.println(s[lineIndex]);
                } else {
                  s[lineIndex] += String(rawNMEAData[rawCharIndex]);
                  //Serial.println(s[lineIndex]);
                }

        */


      }


      //////////////////////

      lineIndex = 0;

      for (rawCharIndex = 0; rawCharIndex < String(rawBattData).length(); rawCharIndex++) {

        if (String(rawBattData[rawCharIndex]) == ",") {
          //Serial.println("comma");
          lineIndex++;


          if (//lineIndex == 0
             lineIndex == 1
              || lineIndex == 2
              //|| lineIndex == 3
             ) {
            actualLineIndex++;
          }

          continue;
        }



        if (//lineIndex == 0
             lineIndex == 1
            || lineIndex == 2
           // || lineIndex == 3
           ) {
          s[actualLineIndex] += String(rawBattData[rawCharIndex]);
          Serial.println(s[actualLineIndex]);
        }

        /*
                if (lineIndex == 0) {
                  // TODO: Try to find an efficient way.
                  s[lineIndex] = String(rawNMEAData[rawCharIndex]);
                  //Serial.println(s[lineIndex]);
                } else {
                  s[lineIndex] += String(rawNMEAData[rawCharIndex]);
                  //Serial.println(s[lineIndex]);
                }

        */


      }

      return s;
    }
};
