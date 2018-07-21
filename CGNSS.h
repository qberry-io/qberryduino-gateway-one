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

const PROGMEM byte LINES_LENGTH = 8;
const PROGMEM char SEPERATOR = ',';

class CGNSS {
  private:

    String s[LINES_LENGTH];
    byte actualLineIndex = 0;
    byte lineIndex = 0;
    int rawCharIndex = 0;

    boolean isInCGNSSIndexes(byte lineIndex) {
      return lineIndex == 1
             || lineIndex == 3
             || lineIndex == 4
             || lineIndex == 5
             || lineIndex == 6
             || lineIndex == 7
             || lineIndex == 8
             || lineIndex == 15;
    }

    boolean isInBattIndexes(byte lineIndex) {
      return
        lineIndex == 0
        || lineIndex == 1
        || lineIndex == 2;
    }

    void clear() {
      for (int i = 0; i < LINES_LENGTH; i++) {
        s[i] = "";
      }
    }

  public:

    String* parseBatt(char * rawBattData) {

      clear();

      actualLineIndex = 0;
      lineIndex = 0;
      rawCharIndex = 0;

      for (rawCharIndex = 0; rawCharIndex < String(rawBattData).length(); rawCharIndex++) {

        if (rawBattData[rawCharIndex] == SEPERATOR) {
          
          if (isInBattIndexes(lineIndex)) {
            actualLineIndex++;
          }

          lineIndex++;
          continue;
        }

        if (isInBattIndexes(lineIndex)) {
          if (lineIndex == 0) {
            if (rawCharIndex > 11) {
              s[actualLineIndex] += String(rawBattData[rawCharIndex]);
            }
          } else {
            s[actualLineIndex] += String(rawBattData[rawCharIndex]);
          }
        }
      }
      return s;
    }

    String* parseNMEAData(char* rawNMEAData) {

      clear();

      actualLineIndex = 0;
      lineIndex = 0;
      rawCharIndex = 0;

      for (rawCharIndex = 0; rawCharIndex < String(rawNMEAData).length(); rawCharIndex++) {

        if (rawNMEAData[rawCharIndex] == SEPERATOR) {
          if (isInCGNSSIndexes(lineIndex)) {
            actualLineIndex++;
          }

          lineIndex++;
          continue;
        }

        if (isInCGNSSIndexes(lineIndex)) {
          s[actualLineIndex] += String(rawNMEAData[rawCharIndex]);
        }
      }

      return s;
    }
};

