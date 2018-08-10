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

//  Description: "MessageFactoryBase" is an abstract base class
//  that includes necessary functions and variables to create
//  appropriate messages for server using the version of
//  "Open Qberry Protocol" declared in the local variable named
//  PROTOCOL_VERSION.

#ifndef MessageFactoryBase_h
#define MessageFactoryBase_h

class MessageFactoryBase
{
  protected:
    int lineI;
    int i;
    String t;

    // The version of "Open Qberry Protocol"
    char PROTOCOL_VERSION[12] = "1.0.0-beta1";

    // The symbol of the beginning and the end of messages.
    const char MARKER = '$';

    // The symbol for splitting the keyvals.
    const char SPLITTER = '|';

    // Definitions of the header keys.
    const byte MESSAGE_TYPE_KEY = 11;
    const byte DEV_ID_KEY = 12;
    const byte CONNECTION_ID_KEY = 13;
    const byte SECRET_KEY = 14;
    const byte DEV_MODEL_KEY = 15;
    const byte PROTOCOL_VERSION_KEY = 16;

    // Creates message based on given message.
    // (This is the last step of preparing a message to send to
    // the server.)
    String message(String msg);

    // Creates partition for given value.
    String keyval(int key, char val[]);

    // Creates partition for given value.
    String keyval(int key, String val);

};
#endif
