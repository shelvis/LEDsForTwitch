void police(int duration)
{
    // TODO Licht schnell reinfaden
    int frequency = 4;

    int tickMax = (frequency * 2) * duration;

    for (int tick = 0; tick < tickMax; tick++)
    {
        for (int i = 0; i < NUM_LED; i++)
        {
            if (tick % 2 == 0 and i < (NUM_LED / 2))
            {
                led.setPixelColor(i, colorRed);
            }
            else if (tick % 2 == 1 and i >= (NUM_LED / 2))
            {
                led.setPixelColor(i, colorBlue);
            }
            else
            {
                led.setPixelColor(i, colorBlack);
            }
        }
        led.show();
        delay(1000 / (frequency * 2));
    }

    clearLEDs();
}

void colorWheel(uint32_t colorOne, uint32_t colorTwo, int duration)
{
    int stepsPerSecond = 90; // do x steps per second

    int tickMax = stepsPerSecond * duration / 2.5;
    for (int tick = 0; tick < tickMax; tick++)
    {
        for (int i = 0; i < NUM_LED; i++)
        {
            // *1 -> 3 LEDs
            // /2 -> 6 LEDs
            // /3 -> 9-12 LEDs
            if (cos((i - tick) / 3) > 0)
            {
                led.setPixelColor(i, colorOne);
            }
            else
            {
                led.setPixelColor(i, colorTwo);
            }
        }
        led.show();
        delay(1000 / stepsPerSecond);
    }

    clearLEDs();
}