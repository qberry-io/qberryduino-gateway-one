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

class Messaging
{
  private:
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

  public:
    String hello(char devId[], char pass[], char devModel[]) {
      return
        message(
          keyval(1, HELLO)
          + keyval(3, devId)
          + keyval(5, pass)
          + keyval(7, devModel)
          + keyval(9, VERSION)
        );
    }
};

