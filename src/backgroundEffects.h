enum Pattern
{
    BLUE_WHITE,
    RED_WHITE,
    WHITE,
    RAINBOW_CYCLE
};

Pattern activePattern;
int actualTick;
unsigned long nextUpdate;

void colorWheelNonBlocking(uint32_t colorOne, uint32_t colorTwo)
{
    int stepsPerSecond = 30; // do x steps per second

    for (int i = 0; i < NUM_LED; i++)
    {
        // *1 -> 3 LEDs
        // /2 -> 6 LEDs
        // /3 -> 9-12 LEDs
        if (cos((i - actualTick) / 3) > 0)
        {
            led.setPixelColor(i, colorOne);
        }
        else
        {
            led.setPixelColor(i, colorTwo);
        }
    }
    led.show();

    actualTick++;
    nextUpdate = millis() + (1000 / stepsPerSecond);
}

uint32_t Wheel(byte WheelPos)
{
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85)
    {
        return led.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    else if (WheelPos < 170)
    {
        WheelPos -= 85;
        return led.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
    else
    {
        WheelPos -= 170;
        return led.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    }
}

// Update the Rainbow Cycle Pattern
void RainbowCycleNonBlocking()
{
    int stepsPerSecond = 30;

    for (int i = 0; i < NUM_LED; i++)
    {
        led.setPixelColor(i, Wheel(((i * 256 / NUM_LED) + actualTick) & 255));
    }
    led.show();

    actualTick++;
    nextUpdate = millis() + (1000 / stepsPerSecond);
}

void updateBackgroundEffect()
{
    if (millis() >= nextUpdate) // time to update
    {
        switch (activePattern)
        {
        case RAINBOW_CYCLE:
            RainbowCycleNonBlocking();
            break;
        case RED_WHITE:
            colorWheelNonBlocking(colorRed, colorWhite);
            break;
        case WHITE:
            colorWheelNonBlocking(colorWhite, colorBlack);
            break;
        default:
            colorWheelNonBlocking(colorBlue, colorWhite);
            break;
        }
    }
}

void setEffectToRainbow()
{
    activePattern = RAINBOW_CYCLE;
    actualTick = NUM_LED;
    nextUpdate = 0;
}

void setEffectToBlueWhite()
{
    activePattern = BLUE_WHITE;
    actualTick = 0;
    nextUpdate = 0;
}

void setEffectToRedWhite()
{
    activePattern = RED_WHITE;
    actualTick = 0;
    nextUpdate = 0;
}

void setEffectToWhite()
{
    activePattern = WHITE;
    actualTick = 0;
    nextUpdate = 0;
}