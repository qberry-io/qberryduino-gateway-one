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

//  Description: "RandomString" is an helper class to generate
//  strings randomly.

//  NOTICE: Before using this library, be sure that the
//  "pseudo-random number generator" has been initialized in "setup()"
//  function of Arduino.
//  Example: "randomSeed(analogRead(0));"
//  For more about "randomseed", please refer to link shared below:
//  https://www.arduino.cc/reference/en/language/functions/random-numbers/randomseed/

#include "Arduino.h"
class RandomString
{
  public:
  // Generates a string randomly with given length.
  String generate(byte length);
};
