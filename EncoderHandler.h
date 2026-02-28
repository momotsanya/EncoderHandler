#pragma once
#include <Arduino.h>

class EncoderHandler {
public:
    EncoderHandler(int pinA, int pinB, int pinButton);

    void begin();
    void tick();

    int getDirection();       // +1 = CW, -1 = CCW, 0 = no rotation
    bool isShortPressed();    // returns true once per short press
    bool isLongPressed();     // returns true once per long press

private:
    int _pinA, _pinB, _pinButton;
    int _lastStateA;

    enum ButtonState {IDLE, PRESSING, LONG_PRESS};
    ButtonState _buttonState;

    unsigned long _buttonPressTime;
    const unsigned long _longPressTime = 1000; // 1 second

    bool _shortPressDetected;
    bool _longPressDetected;

    int _rotation;
};
