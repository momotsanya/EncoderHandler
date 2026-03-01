# EncoderHandler

A simple Arduino class to handle **rotary encoders with push button**, supporting:

- Clockwise (CW) rotation
- Counterclockwise (CCW) rotation
- Short press button
- Long press button

## Usage

1. Add `EncoderHandler.h` and `EncoderHandler.cpp` to your Arduino project.
2. Include in your sketch:
3. Create  instance:
4. Call encoder.tick() in your loop().
5. Read encoder:
6. Test with example in examples/EncoderTest/EncoderTest.ino.

```cpp
#include "EncoderHandler.h"
3. Create instance:

EncoderHandler encoder(ENCODER_A, ENCODER_B, ENCODER_BTN);
encoder.begin();

4. Call encoder.tick() in your loop().

5. Read encoder:

int dir = encoder.getDirection();       // +1 = CW, -1 = CCW
if (encoder.isShortPressed()) { ... }   // short press
if (encoder.isLongPressed()) { ... }    // long press

6. Test with example in examples/EncoderTest/EncoderTest.ino.
