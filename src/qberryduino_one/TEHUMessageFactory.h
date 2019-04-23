//  Copyright (c) 2019-present, Deniz Kanmaz. All rights reserved.
//  This source code is licensed under the GNU GENERAL PUBLIC
//  LICENCE V3. Use of this source code is governed by a license
//  that can be found in the LICENSE file.

//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  LICENSE file for more details.

//  You should have received a copy of the LICENSE file along with
//  this program. If not, see <http://www.gnu.org/licenses/>.

//  Description: "TEHUMessageFactory" is a factory class that
//  includes a function to create "Current State" message for Tempereture
//  and Humidity using the declared version in local variable named
//  PROTOCOL_VERSION located on the inherited class.

#include "MessageFactoryBase.h"

class TEHUMessageFactory: private MessageFactoryBase
{
  private:

    const char CURR[5] = "TEHU";

    const int TEHU_START_INDEX = 311;
    const byte TEHU_LINES_LENGTH = 2;

  public:

    // Creates ready to send "CURR" message for Tempereture and
    // humidity with given parameters.
    String create(char devId[],
                  char connectionId[],
                  String tehuData[]);
};
