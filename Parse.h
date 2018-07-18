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


    
};
