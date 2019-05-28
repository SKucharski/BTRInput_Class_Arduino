#include "BTRInput.h"

BTRInput::BTRInput(byte input_pin, bool pullup)
{
    if(pullup) pinMode(input_pin, INPUT_PULLUP);
    else pinMode(input_pin, INPUT);

    pin = input_pin;

    isInputHigh = digitalRead(pin);
    stableHigh = isInputHigh;

    this->pullup = pullup;

    debounce_time = 20;
    switch_time = millis();
    last_state_time = 0;
    stab_time = millis();
}

void BTRInput::setDebounceTime(unsigned long time_millis)
{
    debounce_time = time_millis;
}

bool BTRInput::isStateHigh()
{
    return stableHigh;
}

bool BTRInput::isStateLow()
{
    return !stableHigh;
}

bool BTRInput::isTriggered()
{
    return ( stableHigh != pullup );
}

bool BTRInput::isReleased()
{
    return ( stableHigh == pullup );
}

bool BTRInput::isClicked()
{
    if(clicked) {
        clicked = false;

        return true;
    }

    return false;
}

unsigned long BTRInput::getActiveStateTime()
{
    if(stab_time > ctime)
        return ctime;

    return ( ctime - stab_time + debounce_time );
}

unsigned long BTRInput::getLastStateTime()
{
    return last_state_time;
}

void BTRInput::update()
{
    ctime = millis();
    if(switch_time > ctime)
        reset();

    if(isInputHigh != digitalRead(pin))
    {
        switch_time = ctime;
        isInputHigh = !isInputHigh;
    }
    else if(isInputHigh != stableHigh)
    {
        if(ctime - switch_time >= debounce_time)
        {
            if(stab_time > ctime)
                stab_time = ctime;

            last_state_time = ctime - stab_time + debounce_time;

            stab_time = ctime;

            stableHigh = isInputHigh;

            if(prevStableHigh != stableHigh)
            {
                if(isReleased())
                    clicked = true;
                else if(clicked && isTriggered())
                    clicked = false;

                prevStableHigh = stableHigh;
            }
        }
    }
}

void BTRInput::reset()
{
    isInputHigh = digitalRead(pin);
    stableHigh = isInputHigh;
    prevStableHigh = isInputHigh;

    ctime = millis();
    stab_time = ctime;
    last_state_time = 0;
    switch_time = ctime;
}
