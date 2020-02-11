
/*
 * BTRInput.h
 *
 * Arduino library for inputs control
 *
 * This code is released ito the public domain
 *
 */

#ifndef BTRINPUT_H
#define BTRINPUT_H

#include <Arduino.h>

class BTRInput
{
public:

    BTRInput(byte input_pin, bool pullup = false);
    void setDebounceTime(unsigned long time_millis);
    bool isStateHigh();
    bool isStateLow();
    bool isTriggered();
    bool isReleased();
    bool isClicked();
    bool wasClicked();
    bool wasPressed();
    unsigned long getActiveStateTime();
    unsigned long getLastStateTime();
    void update();
    void reset();

private:

    byte pin;
    bool pullup;
    bool isInputHigh;
    bool stableHigh;
    bool prevStableHigh;
    bool clicked;
    bool pressed;
    unsigned long ctime;
    unsigned long debounce_time;
    unsigned long switch_time;
    unsigned long stab_time;
    unsigned long last_state_time;

};

#endif // BTRINPUT_H
