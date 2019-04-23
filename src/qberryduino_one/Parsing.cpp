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

//  Description: Please refer to "Parsing.h".

/////////
// TODO: Refactor all the class.
/////////

#include "Arduino.h"
#include "Parsing.h"

// Returns whether the given index includes data we interest.
boolean Parsing::isInCGNSSIndexes(byte lineIndex) {
  return lineIndex == 1 // Fix Status
         || lineIndex == 3 // Latitude
         || lineIndex == 4 // Longtitude
         || lineIndex == 5 // MSL Altitude
         || lineIndex == 6 // Speed Over Ground
         || lineIndex == 7 // Course Over Ground
         || lineIndex == 8 // Fix Mode
         || lineIndex == 15 // GNSS Satellites Used
         || lineIndex == 16; // GLONASS Satellites in View
}

// Returns whether the given index includes data we interest.
boolean Parsing::isInBattIndexes(byte lineIndex) {
  return
    lineIndex == 0 // Charge Status
    || lineIndex == 1 // Battery Level (%)
    || lineIndex == 2; // Battery Voltage (mV)
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
        Serial.println(String(rawBattData[rawCharIndex]));
        if (rawCharIndex == 6) {
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

// https://stackoverflow.com/a/14824108
String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : F("");
}

// Parses given Raw CGNSINF response taken from the module.
// NOTICE: The raw message must be in "RMC" sequence.
String* Parsing::parseTEHURFData(String rawTEHURFData) {

  clear();

  //$|11|TEHU|12|123456789|13|RF|311|22.60|312|46.50|$

  s[0] = getValue(rawTEHURFData, '|', 4);
  s[1] = getValue(rawTEHURFData, '|', 8);
  s[2] = getValue(rawTEHURFData, '|', 10);
 
  /*
    StringSplitter ss = StringSplitter(rawTEHURFData, '|', 11);
    int count = ss.getItemCount();

    s[0] = ss.getItemAtIndex(4);
    s[1] = ss.getItemAtIndex(8);
    s[2] = ss.getItemAtIndex(10);

    Serial.println(s[0]);
    Serial.println(s[1]);
    Serial.println(s[2]);
  */
  /*
    for (int i = 0; i < count; i++) {
      //s[i] = ss.getItemAtIndex(i);

      Serial.println(ss.getItemAtIndex(i));
    }
  */

  return s;
}



/*
  int[] getCharIndexes(String data, char character) {
  int indexes[];
  for (int i = 0; i < data.length(); i++) {
    if (data.charAt(i) == character) {
      count++;
    }
  }
  return count;
  }







  int countSplitCharacters(String text, char splitChar) {
  int returnValue = 0;
  int index = -1;

  while (index > -1) {
    index = text.indexOf(splitChar, index + 1);

    if (index > -1) returnValue += 1;
  }

  return returnValue;
  }



  String* splitCommand(String text, char splitChar) {
  int splitCount = countSplitCharacters(text, splitChar);
  String returnValue[splitCount];
  int index = -1;
  int index2;

  for (int i = 0; i < splitCount - 1; i++) {
    index = text.indexOf(splitChar, index + 1);
    index2 = text.indexOf(splitChar, index + 1);

    if (index2 < 0) index2 = text.length() - 1;
    returnValue[i] = text.substring(index, index2);
  }

  return returnValue;
  }


*/
