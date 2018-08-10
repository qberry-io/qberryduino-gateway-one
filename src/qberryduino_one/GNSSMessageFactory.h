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

//  Description: "GNSSMessageFactory" is a factory class that
//  includes a function to create "Current State" message for GNSS
//  using the declared version in local variable named PROTOCOL_VERSION
//  located on the inherited class.

#include "MessageFactoryBase.h"

class GNSSMessageFactory : private MessageFactoryBase
{
  private:
   
    char CURR[5] = "GNSS";

    const int CGNSS_START_INDEX = 211;
    const byte CGNSS_LINES_LENGTH = 9;

  public:

    // Creates ready to send "CURR" message for CGNS with given
    // parameters.
    String create(char devId[],
                  char connectionId[],
                  String cgnsData[]);
};

