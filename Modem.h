//  Copyright (c) 2018-present, Deniz KANMAZ All rights reserved.
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

class Modem
{
  private:
  byte rx, tx;
  int baudRate;
  Led ledManager;
  public:
    void init(byte rx, byte tx, int baudRate, Led ledManager) {
      rx = rx;
      tx = tx;
      baudRate = baudRate;
      ledManager = ledManager;
    }
};
