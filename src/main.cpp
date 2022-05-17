#include <Arduino.h>
#include <ESP8266WiFi.h> //https://github.com/esp8266/Arduino
#include <IRCClient.h>
#include <Adafruit_NeoPixel.h>
#include "config/wlan.h"
#include "config/twitch.h"

#define NUM_LED 300 // Anzahl der LEDs
#define LED_PIN 5   // Anschlusspin des LED-Streifens

#define ANIMATION_TIME 10000 // Dauer der Animation in Milisekunden (1000 = 1 Sekunde)

WiFiClient wiFiClient;
String ircChannel = "#" + twitchChannelName;
IRCClient client(IRC_SERVER, IRC_PORT, wiFiClient);

Adafruit_NeoPixel led(NUM_LED, LED_PIN, NEO_GRB + NEO_KHZ800);

#include "colors.h"
#include "helpers.h"
#include "strobe.h"
#include "effects.h"
#include "backgroundEffects.h"

void connectWifi()
{
  Serial.begin(115200);
  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
}

void sendTwitchMessage(String message)
{
  client.sendMessage(ircChannel, message);
}

void callback(IRCMessage ircMessage)
{
  // Serial.println("In CallBack");

  if (ircMessage.command == "PRIVMSG" && ircMessage.text[0] != '\001')
  {
    // Serial.println("Passed private message.");

    ircMessage.nick.toUpperCase();

    String message("<" + ircMessage.nick + "> " + ircMessage.text);
    // sendTwitchMessage("Found light command: " + ircMessage.text);

    // prints chat to serial
    Serial.println(message);
    // Effekt für Follows
    // if (ircMessage.text.indexOf("following") > -1 && ircMessage.nick == "STREAMLAB")
    // {
    //   FastLED.clear();
    //   z = 1;
    //   do
    //   {
    //     Serial.println(z);
    //     z++;
    //     fill_solid(leds, NUM_LEDS, CRGB(255, 0, 0));
    //     FastLED.show();
    //     delay(500);

    //     fill_solid(leds, NUM_LEDS, CRGB(0, 0, 255));
    //     FastLED.show();
    //     delay(500);
    //   } while (z < 10);
    //   FastLED.clear();
    //   FastLED.show();
    //   EVERY_N_MILLISECONDS(20)
    //   {
    //     pacifica_loop();
    //     FastLED.show();
    //   }
    // }

    // else
    if (ircMessage.text == "!licht")
    {
      sendTwitchMessage("Du kannst das Licht mit folgenden Befehlen steuern: Jeweils !strobo !stroborot !strobogrün !stroboblau !stroborosa !strobogelb !stroboorange !strobolila !stroboblauweiß !strobobunt !911 !blauweiß !gelbblau !rotweiß !grünrosa !grünlila !weiß !rot !grün !blau !rosa !gelb !orange !lila");
    }
    else if (ircMessage.text == "!strobo" || ircMessage.text == "!stroboweiß")
    {
      strobe(colorWhite, colorBlack, 5);
    }
    else if (ircMessage.text == "!stroborot")
    {
      strobe(colorRed, colorBlack, 5);
    }
    else if (ircMessage.text == "!strobogrün")
    {
      strobe(colorGreen, colorBlack, 5);
    }
    else if (ircMessage.text == "!stroboblau")
    {
      strobe(colorBlue, colorBlack, 5);
    }
    else if (ircMessage.text == "!stroborosa")
    {
      strobe(colorRose, colorBlack, 5);
    }
    else if (ircMessage.text == "!strobogelb")
    {
      strobe(colorYellow, colorBlack, 5);
    }
    else if (ircMessage.text == "!stroboorange")
    {
      strobe(colorOrange, colorBlack, 5);
    }
    else if (ircMessage.text == "!strobolila")
    {
      strobe(colorPurple, colorBlack, 5);
    }
    else if (ircMessage.text == "!stroboblauweiß")
    {
      strobe(colorBlue, colorWhite, 5);
    }
    else if (ircMessage.text == "!strobobunt")
    {
      strobeColorful(5);
    }
    else if (ircMessage.text == "!police" || ircMessage.text == "!911")
    {
      police(5);
    }
    else if (ircMessage.text == "!blauweiß")
    {
      colorWheel(colorBlue, colorWhite, 5);
    }
    else if (ircMessage.text == "!gelbblau")
    {
      colorWheel(colorYellow, colorBlue, 5);
    }
    else if (ircMessage.text == "!rotweiß")
    {
      colorWheel(colorRed, colorWhite, 5);
    }
    else if (ircMessage.text == "!grünrosa")
    {
      colorWheel(colorGreen, colorRose, 5);
    }
    else if (ircMessage.text == "!grünlila")
    {
      colorWheel(colorGreen, colorPurple, 5);
    }
    else if (ircMessage.text == "!weiß")
    {
      colorWheel(colorWhite, colorBlack, 5);
    }
    else if (ircMessage.text == "!rot")
    {
      colorWheel(colorRed, colorBlack, 5);
    }
    else if (ircMessage.text == "!grün")
    {
      colorWheel(colorGreen, colorBlack, 5);
    }
    else if (ircMessage.text == "!blau")
    {
      colorWheel(colorBlue, colorBlack, 5);
    }
    else if (ircMessage.text == "!rosa")
    {
      colorWheel(colorRose, colorBlack, 5);
    }
    else if (ircMessage.text == "!gelb")
    {
      colorWheel(colorYellow, colorBlack, 5);
    }
    else if (ircMessage.text == "!orange")
    {
      colorWheel(colorOrange, colorBlack, 5);
    }
    else if (ircMessage.text == "!lila")
    {
      colorWheel(colorPurple, colorBlack, 5);
    }
    else if (ircMessage.text == "!effectRainbow")
    {
      setEffectToRainbow();
    }
    else if (ircMessage.text == "!effectDefault")
    {
      setEffectToDefault();
    }
    return;
  }
}

void setup()
{
  led.begin();           // Einrichten des LED-Outputs
  led.setBrightness(64); // Maximale Helligkeit
  led.clear();
  led.show();

  connectWifi();

  // Initialise IRC
  client.setCallback(callback);

  // Start with rainbow effect
  setEffectToRainbow();
}

// Liefert Rotwert (0-255) für die LED an der jeweiligen Stelle zurück.
int getR(int index)
{
  return 0;
}

// Liefert Grünwert (0-255) für die LED an der jeweiligen Stelle zurück.
int getG(int index)
{
  return ((float)index / NUM_LED) * 255;
}

// Liefert Blauwert (0-255) für die LED an der jeweiligen Stelle zurück.
int getB(int index)
{
  return 255 - ((float)index / NUM_LED) * 255;
}

// Spielt die Aktivierungs-Animation ab.
void turnOn()
{
  int delayTime = (ANIMATION_TIME / NUM_LED);
  for (int i = 0; i < NUM_LED; i++)
  {
    led.setPixelColor(i, getR(i), getG(i), getB(i));
    led.show();
    delay(delayTime);
  }
}

// Deaktiviert die LEDs mit Zeitverzögerung
void turnOff()
{
  int delayTime = (ANIMATION_TIME / NUM_LED);
  for (int i = 0; i < NUM_LED; i++)
  {
    led.setPixelColor(i, 0, 0, 0);
    led.show();
    delay(delayTime);
  }
}

void loop()
{
  // Try to connect to chat. If it loses connection try again
  if (!client.connected())
  {
    Serial.println("Attempting to connect to " + ircChannel);
    // Attempt to connect
    // Second param is not needed by Twtich
    if (client.connect(TWITCH_BOT_NAME, "", TWITCH_OAUTH_TOKEN))
    {
      client.sendRaw("JOIN " + ircChannel);
      Serial.println("connected and ready to rock");
      sendTwitchMessage("Die LEDs sind ready. Lasst das Geblinke beginnen!");
    }
    else
    {
      Serial.println("failed... try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
    return;
  }
  client.loop();
  updateBackgroundEffect();
}

// Lauflichter
//- 911
//- einzelne Farben

//
// Zufällig einzelne Punkte