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

//  Description: "Parsing.h" is a helper class that includes
//  functions to parse responses from the Modem.

class Parsing {
  private:

    static const PROGMEM byte LINES_LENGTH = 8;
    static const PROGMEM char SEPERATOR = ',';

    String s[LINES_LENGTH];
    byte actualLineIndex = 0;
    byte lineIndex = 0;
    int rawCharIndex = 0;

    boolean isInCGNSSIndexes(byte lineIndex);
    boolean isInBattIndexes(byte lineIndex);

  public:

    String* parseBatt(char * rawBattData);
    String* parseNMEAData(char* rawNMEAData);
    void clear();
};

