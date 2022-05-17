#define STROBE_FREQUENCY 12 // Frequency of strobe in Hz

/**
 * @brief
 *
 * @param colorOne
 * @param colorTwo
 * @param duration Length of strobe in seconds
 */
void strobe(uint32_t colorOne, uint32_t colorTwo, int duration)
{
    int tickMax = (STROBE_FREQUENCY * 2) * duration;

    for (int tick = 0; tick < tickMax; tick++)
    {
        switch (tick % 2)
        {
        case 0:
            switchAllLEDsToOneColor(colorOne);
            break;
        default:
            switchAllLEDsToOneColor(colorTwo);
            break;
        }

        delay(1000 / (STROBE_FREQUENCY * 2));
    }

    clearLEDs();
}

void strobeColorful(int duration)
{
    int tickMax = (STROBE_FREQUENCY * 2) * duration;

    for (int tick = 0; tick < tickMax; tick++)
    {
        switch (tick % 5)
        {
        case 0:
            switchAllLEDsToOneColor(colorYellow);
            break;
        case 1:
            switchAllLEDsToOneColor(colorRed);
            break;
        case 2:
            switchAllLEDsToOneColor(colorGreen);
            break;
        case 3:
            switchAllLEDsToOneColor(colorOrange);
            break;
        case 4:
            switchAllLEDsToOneColor(colorBlue);
            break;
        default:
            switchAllLEDsToOneColor(colorRose);
            break;
        }

        delay(1000 / (STROBE_FREQUENCY * 2));
    }

    clearLEDs();
}