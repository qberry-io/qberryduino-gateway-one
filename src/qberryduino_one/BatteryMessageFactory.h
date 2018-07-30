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

//  Description: "Messaging.cpp" is a helper class that includes
//  functions to create appropriate messages for server using
//  declared version in the local variable named PROTOCOL_VERSION.

#include "MessageFactoryBase.h"

class BatteryMessageFactory: private MessageFactoryBase
{
  private:
    
    char CURR[5] = "BATT";

    const int BATT_START_INDEX = 111;
    const byte BATT_LINES_LENGTH = 3;

  public:

    // Creates ready to send "CURR" message for Battery with given
    // parameters.
    String create(char devId[],
                  char connectionId[],
                  String battData[]);
};

