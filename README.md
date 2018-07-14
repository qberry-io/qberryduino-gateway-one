# Devices

- 1\* Arduino Mini Pro Atmega324 5.5V
- 1\* Adafruit Sim808

# Components

- 1\* Push button with 4 legs
- 4\* Led
  - Red: Power / Standbye
  - Yellow:  Connection status
  - Green: Package received
  - Blue: Package sent
- 1\* GPS Antenna
- 1\* GSM Antenna
- 1\* Battery

# Hardware Installation

**Power Connection**

Sensors are can be used with 9V 500ma adaptor or 9v battery. If adaptor and battery connected to device in the same time, adaptor will be used.

Note: Device doesn&#39;t charge the battery.

**Push button** _Reset_

(+) → 5 (Red) _(With 10k ohm resistor)_

(-) → GND (Black)

**Led (Red)** _Power On / Stand By_

(+) → 5 (Red) _(With 250 ohm resistor)_

(-) → GND (Black)

**Led (Yellow)** _Connected to the server_

(+) → 4 (Yellow) _(With 250 ohm resistor)_

(-) → GND (Black)

**Led (Green)** _Message Received_

(+) → 3 (Green) _(With 250 ohm resistor)_

(-) → GND (Black)

**Led (Blue)** _Message Sent_

(+) → 2 (Blue) _(With 250 ohm resistor)_

(-) → GND (Black)

**NRF24L01 RF Transceiver**

GND -&gt; GND (Black)

VCC -&gt; 3.3V (Red)

CE -&gt; 9 (Green)

CSN -&gt; 10 (Yellow)

SCK -&gt; 12 (Purple)

MOSI -&gt; 11 (Orange)

MISO -&gt; 12 (White)

IRQ -&gt; Empty

**Fona Sim808**

5v -&gt; 5v (Red)

GND -&gt; GND (Black)

RX -&gt; 7 (Orange)

TX -&gt; 8 (Brown)

# Messaging

**Special Characters**

**&quot;$&quot;** : Beginning or end of the message. (From tBerryduino to Server)

**&quot;|&quot;** : Splitter

Count of the pipe characters must be odd.

**Example:**

$|1|hello|3|5162829321|5|pa$$w0rd|7|tbdOne|9|1.0.1|$

**Keys &amp; Values**

Every value described with a key. This key always comes just before the value.

Example:

Key, Value

$|1|hello|3|5162829321|5|pa$$w0rd|7|tbdOne|9|1.0.1|$

**Keys**

Odd numbered keys: From Tberyduino to server.

Even numbered keys: From anywhere to Tberyduino.

**Key Table**

101: Type of message _(hello, curr, bye)_

102: Type of message

103: Device identity

105: Password

106: Password

107: Device model

109: Firmware version

110: Glonass Run Status

1002: GPS Fix Status

1004: Latitude

1006: Longtitude

1008: Altitude

1010: Speed in KM

1012: Course Over Ground

1014: Heat

1016: Humidity