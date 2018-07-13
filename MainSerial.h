//  Copyright (c) 2018-present, Deniz KANMAZ  All rights reserved.
//  This source code is licensed under the GNU GENERAL PUBLIC
//  LICENCE V3. Use of this source code is governed by a license
//  that can be found in the LICENSE file.

//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  LICENSE file for more details.

//  You should have received a copy of the LICENSE file along with
//  with this program. If not, see <http://www.gnu.org/licenses/>.

//  E-mail: denizkanmaz@gmail.com

class MainSerial
{
  private:
    int baudRate;
  public:
    void init(int baudRate) {
      baudRate = baudRate;
      Serial.begin(baudRate);
    }
    void println(String charsToPrint) {
      Serial.println(charsToPrint);
    }
};

