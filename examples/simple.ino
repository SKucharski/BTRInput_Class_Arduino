#include "BTRInput.h"

const byte LED_PIN = 13;
const byte BUTTON_PIN = 6;
const bool PULLUP_MODE = true;

BTRInput button(BUTTON_PIN, PULLUP_MODE);

void setup()
{
    button.setDebounceTime(50);
}

void loop()
{
    button.update();

    bool state = digitalRead(LED_PIN);

    if(button.isClicked())
        digitalWrite(LED_PIN, !state);
}
