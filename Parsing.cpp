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

//  Description: "Parsing.cpp" is a helper class that includes
//  functions to parse responses from the Modem.

#include "Arduino.h"
#include "Parsing.h"

// Returns whether the given index includes data we interest.
boolean Parsing::isInCGNSSIndexes(byte lineIndex) {
  return lineIndex == 1
         || lineIndex == 3
         || lineIndex == 4
         || lineIndex == 5
         || lineIndex == 6
         || lineIndex == 7
         || lineIndex == 8
         || lineIndex == 15;
}

// Returns whether the given index includes data we interest.
boolean Parsing::isInBattIndexes(byte lineIndex) {
  return
    lineIndex == 0
    || lineIndex == 1
    || lineIndex == 2;
}

// Clears the temprorary values.
void Parsing::clear() {
  for (int i = 0; i < LINES_LENGTH; i++) {
    s[i] = "";
  }
}

// Parses given Raw CBC response taken from the module.
String* Parsing::parseBatt(char * rawBattData) {

  clear();

  actualLineIndex = 0;
  lineIndex = 0;
  rawCharIndex = 0;

  for (rawCharIndex = 0;
       rawCharIndex < String(rawBattData).length();
       rawCharIndex++) {

    if (rawBattData[rawCharIndex] == SEPERATOR
        || (rawBattData[rawCharIndex] == 'O'
            && rawBattData[rawCharIndex + 1] == 'K')) {

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

// Parses given Raw CGNSINF response taken from the module.
// NOTICE: The raw message must be in "RMC" sequence.
String* Parsing::parseNMEAData(char* rawNMEAData) {

  clear();

  actualLineIndex = 0;
  lineIndex = 0;
  rawCharIndex = 0;

  for (rawCharIndex = 0;
       rawCharIndex < String(rawNMEAData).length();
       rawCharIndex++) {

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

