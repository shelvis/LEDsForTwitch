void switchAllLEDsToOneColor(uint32_t color)
{
    // TODO: Kann weg, dafür gibt es fill
    // for (int i = 0; i < NUM_LED; i++)
    // {
    //     led.setPixelColor(i, color);
    // }
    led.fill(color);
    led.show();
}

void clearLEDs()
{
    led.clear();
    led.show();
}