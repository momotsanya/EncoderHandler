#pragma once
#include <Arduino.h>

class EncoderHandler {
public:
    EncoderHandler(int pinA, int pinB, int pinButton);

    void begin();
    void tick();

    int getDirection();       // +1 = CW, -1 = CCW, 0 = no movement
    bool isShortPressed();
    bool isLongPressed();

private:
    int _pinA, _pinB, _pinButton;

    enum ButtonState {IDLE, PRESSING, LONG_PRESS};
    ButtonState _buttonState;

    unsigned long _buttonPressTime;
    const unsigned long _longPressTime = 1000;

    bool _shortPressDetected;
    bool _longPressDetected;

    int _rotation;

    uint8_t _lastEncoded;
    int _encoderStepCounter;   // counts partial transitions

    // lookup table for quadrature
    int8_t _encoderTable[16] = {0, -1, 1, 0,
                                1, 0, 0, -1,
                               -1, 0, 0, 1,
                                0, 1, -1, 0};
};
