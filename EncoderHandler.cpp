#include "EncoderHandler.h"

EncoderHandler::EncoderHandler(int pinA, int pinB, int pinButton)
    : _pinA(pinA), _pinB(pinB), _pinButton(pinButton),
      _lastStateA(HIGH), _buttonState(IDLE),
      _buttonPressTime(0), _shortPressDetected(false),
      _longPressDetected(false), _rotation(0) {}

void EncoderHandler::begin() {
    pinMode(_pinA, INPUT_PULLUP);
    pinMode(_pinB, INPUT_PULLUP);
    pinMode(_pinButton, INPUT_PULLUP);
    _lastStateA = digitalRead(_pinA);
}

void EncoderHandler::tick() {
    // --- Handle rotation ---
    int stateA = digitalRead(_pinA);
    int stateB = digitalRead(_pinB);

    _rotation = 0;
    if (_lastStateA == LOW && stateA == HIGH) { // rising edge on A
        _rotation = (stateB == LOW) ? 1 : -1;
    }
    _lastStateA = stateA;

    // --- Handle button ---
    int buttonState = digitalRead(_pinButton);
    unsigned long currentTime = millis();

    switch (_buttonState) {
        case IDLE:
            if (buttonState == LOW) { // button pressed
                _buttonState = PRESSING;
                _buttonPressTime = currentTime;
                _shortPressDetected = false;
                _longPressDetected = false;
            }
            break;

        case PRESSING:
            if (buttonState == HIGH) { // released before long press
                _shortPressDetected = true;
                _buttonState = IDLE;
            } else if (currentTime - _buttonPressTime >= _longPressTime) {
                _longPressDetected = true; // trigger once
                _buttonState = LONG_PRESS;
            }
            break;

        case LONG_PRESS:
            if (buttonState == HIGH) { // wait for release
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
