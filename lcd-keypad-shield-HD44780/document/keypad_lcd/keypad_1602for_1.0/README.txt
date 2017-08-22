README:

SainSmart LCD Shield for Arduino
Key Grab v0.2
Written by jacky
www.sainsmart.com
it'only usfuly in arduino version 1.0

Displays the currently pressed key on the LCD screen.

Key Codes (in left-to-right order):

None   - 0
Select - 1
Left   - 2
Up     - 3
Down   - 4
Right  - 5

Example Constructor: DFR_Key keypad;

keypad.getKey();
Grabs the current key.
Returns a non-zero integer corresponding to the pressed key,
  OR
Returns 0 for no keys pressed,
  OR
Returns -1 (sample wait) when no key is available to be sampled.

OPTIONAL
keypad.setRate(x);
Sets the sample rate at once every x milliseconds.
Default: 10ms
