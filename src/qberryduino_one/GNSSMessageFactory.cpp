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

//  Description: Please refer to "Messaging.h".

#include "Arduino.h"
#include "GNSSMessageFactory.h"

// Creates ready to send "CURR" message for CGNS with given
// parameters.
String GNSSMessageFactory::create(char devId[],
                                  char connectionId[],
                                  String cgnsData[]) {

  t =   keyval(MESSAGE_TYPE_KEY, CURR)
        + keyval(DEV_ID_KEY, devId)
        + keyval(CONNECTION_ID_KEY, connectionId);

  lineI = CGNSS_START_INDEX;
  for (i = 0; i < CGNSS_LINES_LENGTH; i++) {
    // TODO: There should be a pre-defined default value...
    t += keyval(lineI, (cgnsData[i] == "" ? "0" : cgnsData[i]));
    lineI++;
  }
  return message(t);
}

