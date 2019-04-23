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

//  Description: "HolaMessageFactory" is a factory class that
//  includes a function to create "Handshake" message named "HOLA"
//  using the declared version in local variable named PROTOCOL_VERSION
//  located on the inherited class.

#include "MessageFactoryBase.h"

class HolaMessageFactory : private MessageFactoryBase
{
  private:

    const char HOLA[5] = "HOLA";

  public:

    // Creates ready to send "HOLA" message with given parameters.
    String create(char devId[],
                  char connectionId[],
                  char secret[],
                  char devModel[]);
};
