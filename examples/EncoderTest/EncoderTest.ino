#include <Arduino.h>
#include "../../EncoderHandler.h"

#define ENCODER_A  26
#define ENCODER_B  27
#define ENCODER_BTN 2

EncoderHandler encoder(ENCODER_A, ENCODER_B, ENCODER_BTN);

void setup() {
  Serial.begin(115200);
  encoder.begin();
  Serial.println("Encoder Test Started");
}

void loop() {
  encoder.tick();

  int dir = encoder.getDirection();
  if (dir == 1) Serial.println("CW Rotation");
  else if (dir == -1) Serial.println("CCW Rotation");

  if (encoder.isShortPressed()) Serial.println("Short Button Press");
  if (encoder.isLongPressed()) Serial.println("Long Button Press");

  delay(5);
}
