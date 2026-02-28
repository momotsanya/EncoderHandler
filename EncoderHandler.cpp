#include "EncoderHandler.h"

EncoderHandler::EncoderHandler(int pinA, int pinB, int pinButton)
    : _pinA(pinA), _pinB(pinB), _pinButton(pinButton),
      _buttonState(IDLE),
      _buttonPressTime(0),
      _shortPressDetected(false),
      _longPressDetected(false),
      _rotation(0),
      _lastEncoded(0),
      _encoderStepCounter(0)
{}

void EncoderHandler::begin() {
    pinMode(_pinA, INPUT_PULLUP);
    pinMode(_pinB, INPUT_PULLUP);
    pinMode(_pinButton, INPUT_PULLUP);

    int MSB = digitalRead(_pinA);
    int LSB = digitalRead(_pinB);
    _lastEncoded = (MSB << 1) | LSB;
}

void EncoderHandler::tick() {
    // --- Handle rotation ---
    int MSB = digitalRead(_pinA);
    int LSB = digitalRead(_pinB);
    int encoded = (MSB << 1) | LSB;
    int sum = (_lastEncoded << 2) | encoded;

    int delta = _encoderTable[sum & 0x0F];
    _encoderStepCounter += delta;

    // Only trigger a step after 4 quadrature transitions
    if (_encoderStepCounter >= 4) {
        _rotation = 1;    // CW step
        _encoderStepCounter = 0;
    } else if (_encoderStepCounter <= -4) {
        _rotation = -1;   // CCW step
        _encoderStepCounter = 0;
    } else {
        _rotation = 0;    // not a full step yet
    }

    _lastEncoded = encoded;

    // --- Handle button ---
    int buttonState = digitalRead(_pinButton);
    unsigned long currentTime = millis();

    switch (_buttonState) {
        case IDLE:
            if (buttonState == LOW) {
                _buttonState = PRESSING;
                _buttonPressTime = currentTime;
                _shortPressDetected = false;
                _longPressDetected = false;
            }
            break;

        case PRESSING:
            if (buttonState == HIGH) {
                _shortPressDetected = true;
                _buttonState = IDLE;
            } else if (currentTime - _buttonPressTime >= _longPressTime) {
                _longPressDetected = true;
                _buttonState = LONG_PRESS;
            }
            break;

        case LONG_PRESS:
            if (buttonState == HIGH) {
                _buttonState = IDLE;
            }
            break;
    }
}

int EncoderHandler::getDirection() {
    int temp = _rotation;
    _rotation = 0; // reset after reading
    return temp;
}

bool EncoderHandler::isShortPressed() {
    if (_shortPressDetected) {
        _shortPressDetected = false;
        return true;
    }
    return false;
}

bool EncoderHandler::isLongPressed() {
    if (_longPressDetected) {
        _longPressDetected = false;
        return true;
    }
    return false;
}
