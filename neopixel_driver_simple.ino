#include <FastLED.h>

#define LED_PIN 2
#define NUM_LEDS 255    // trying max leds
#define BRIGHTNESS 255  // max brightness
#define LED_TYPE WS2811
#define COLOR_ORDER RGB  // this works for the string I bought.
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 30  //30 enough for the human eye it just a light

long oilRigMillis = 0;  //independent blink time
byte oilRigStep = 0;

long dualLightMillis = 0;  //independent blink time
byte dualLightStep = 0;

void setup() {
  /* for debugging when you get it working you can comment out all LED_BUILTIN lines and all Serial lines or leave in it doesn't matter in this sketch */
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);


  //boilder plate code for FastLED
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);


  //show a rainbow over all 256 lights 256 times how ever long that is
  //we turn this on we want to see it works right away
  for (int k = 0; k < 2; k++) {
    for (int j = 0; j < 255; j++) {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(i - (j * 8), BRIGHTNESS, BRIGHTNESS); /* The higher the value 4 the less fade there is and vice versa */
      }
      FastLED.show();
      delay(2); /* Change this to our hearts desire, the lower the value the faster your colors move (and vice versa) */
    }
  }

  //all lights off at start
  for (int k = 0; k < NUM_LEDS; k++) {
    leds[k] = CRGB(0, 0, 0);
  }
  FastLED.show();

  //this is start time for the oilRig and dual light tower
  long m = millis();
  oilRigMillis = m;
  dualLightMillis = m;
}

void loop() {
  long m = millis();  //this is the current time
  bool show = false;  //this controls when we call show.
  //oil rig processing 3 blinks Red Green Blue then pause repeat every 3 seconds
  if (m > oilRigMillis) {
    show = true;  //right here we've got something to show.
    Serial.print("millis ");
    Serial.print(m);
    Serial.print(" oilRigMillis ");
    Serial.print(oilRigMillis);
    Serial.print(" Oil Light Step ");
    Serial.print(oilRigStep);
    switch (oilRigStep) {
      case 0:  //on red
        Serial.println(" blink red");
        digitalWrite(LED_BUILTIN, HIGH);  //we can see it blink
        leds[0] = CRGB(200, 0, 0);
        oilRigMillis += 150;  //for this much time
        oilRigStep = 1;
        break;
      case 1:  //off
        Serial.println(" off");
        digitalWrite(LED_BUILTIN, LOW);  //we can see it blink
        leds[0].fadeToBlackBy(255);
        oilRigMillis += 150;  //for this much time
        oilRigStep = 2;
        break;
      case 2:  //on green
        Serial.println(" blink Green");
        digitalWrite(LED_BUILTIN, HIGH);  //we can see it blink
        leds[0] = CRGB(0, 200, 0);
        oilRigMillis += 150;  //for this much time
        oilRigStep = 3;
        break;
      case 3:  //off
        Serial.println(" off");
        digitalWrite(LED_BUILTIN, LOW);
        leds[0].fadeToBlackBy(255);
        oilRigMillis += 150;  //for this much time
        oilRigStep = 4;
        break;
      case 4:
        Serial.println(" blink blue");
        digitalWrite(LED_BUILTIN, HIGH);  //we can see it blink
        leds[0] = CRGB(0, 0, 200);
        oilRigMillis += 150;  //for this much time
        oilRigStep = 5;
        break;
      case 5:
        Serial.println(" off 2100");
        digitalWrite(LED_BUILTIN, LOW);
        leds[0].fadeToBlackBy(255);
        oilRigMillis += 2100;  //for this much time
        oilRigStep = 0;
        break;
    }
  }
  //tower dual
  if (m > dualLightMillis) {
    //on left 1 second
    //on right 1 second
    //on left 1 second
    //on right 1 second
    // repeat
    show = true;  //right here we've got something to show.
    Serial.print("millis ");
    Serial.print(m);
    Serial.print(" dualLightMillis ");
    Serial.print(dualLightMillis);
    Serial.print(" dual Light step ");
    Serial.print(dualLightStep);
    //BUILTIN follows the light 1
    switch (dualLightStep) {
      //case 4 is the same as step 0
      case 4:
        dualLightStep = 0;
      case 0:  //1 red  2 off
        Serial.println(" 1 red 2 off");
        digitalWrite(LED_BUILTIN, HIGH);  //we can see it blink
        leds[1] = CRGB(200, 0, 0);
        leds[2] = CRGB(0, 0, 0);
        break;
      case 1:  //1 off 2 red
        Serial.println(" 1 off 2 red");
        digitalWrite(LED_BUILTIN, LOW);  //we can see it blink
        leds[1] = CRGB(0, 0, 0);
        leds[2] = CRGB(200, 0, 0);
        break;
      case 2:  // 1 green 2 off
        Serial.println(" 1 Green 2 off");
        digitalWrite(LED_BUILTIN, HIGH);  //we can see it blink
        leds[1] = CRGB(0, 200, 0);
        leds[2] = CRGB(0, 0, 0);
        break;
      case 3:  //1 off 2 green
        Serial.println(" 1 off 2 Green");
        digitalWrite(LED_BUILTIN, LOW);  //we can see it blink
        leds[1] = CRGB(0, 0, 0);
        leds[2] = CRGB(0, 200, 0);
        break;
    }
    dualLightMillis += 1000;
    dualLightStep += 1;
  }
  if (show) {
    FastLED.show();
  }
}
