/*
 * This sketch uses the 'blinkSlow' coroutine to blink the LED slowly.
 * The 'blinkFast' coroutine blinks the LED quickly.
 * The 'button' coroutine scans the D2 pin for a button press. Each time
 * the button is pressed, the blink mode cycles from "both", "fast" only,
 * to "slow" only, then "both" again.
 *
 * Communication between the coroutines happens through the 'blinkState' global
 * variable. See BlinkCustomCoroutine to see how this communication can happen
 * through methods on custom Coroutine classes.
 */

#include <AceRoutine.h>
using namespace ace_routine;

#ifdef LED_BUILTIN
  const int LED = LED_BUILTIN;
#else
  // Some ESP32 boards do not LED_BUILTIN, sometimes they have more than 1.
  const int LED = 5;
#endif

const int LED_ON = HIGH;
const int LED_OFF = LOW;
const int BUTTON_PIN = 2;

const int BLINK_STATE_BOTH = 0;
const int BLINK_STATE_FAST = 1;
const int BLINK_STATE_SLOW = 2;
int blinkState = BLINK_STATE_BOTH;

COROUTINE(blinkSlow) {
  COROUTINE_LOOP() {
    switch (blinkState) {
      case BLINK_STATE_BOTH:
      case BLINK_STATE_SLOW:
        Serial.print("S1 ");
        digitalWrite(LED, LED_ON);
        COROUTINE_DELAY(500);
        Serial.print("S1a ");

        Serial.print("S0 ");
        digitalWrite(LED, LED_OFF);
        COROUTINE_DELAY(500);
        Serial.print("S0a ");
        break;

      default:
        Serial.print("S ");
        COROUTINE_DELAY(1000);
    }
  }
}

COROUTINE(blinkFast) {
  COROUTINE_LOOP() {
    switch (blinkState) {
      case BLINK_STATE_BOTH:
      case BLINK_STATE_FAST:
        Serial.print("F1 ");
        digitalWrite(LED, LED_ON);
        COROUTINE_DELAY(300);
        Serial.print("F1a ");

        Serial.print("F0 ");
        digitalWrite(LED, LED_OFF);
        COROUTINE_DELAY(300);
        Serial.print("F0a ");
        break;

      default:
        Serial.print("F ");
        COROUTINE_DELAY(600);
    }
  }
}

COROUTINE(button) {
  static int buttonState;
  static int prevButtonState;

  COROUTINE_LOOP() {
    buttonState = digitalRead(BUTTON_PIN);
    if (prevButtonState == HIGH && buttonState == LOW) {
      // primitive debouncing
      COROUTINE_DELAY(20);
      buttonState = digitalRead(BUTTON_PIN);
      if (prevButtonState == HIGH && buttonState == LOW) {
        blinkState++;
        if (blinkState >= 3) {
          blinkState = 0;
        }
        if (blinkState == BLINK_STATE_BOTH) {
          Serial.println("both");
        } else if (blinkState == BLINK_STATE_FAST) {
          Serial.println("fast");
        } else if (blinkState == BLINK_STATE_SLOW) {
          Serial.println("slow");
        }
      }
    }
    prevButtonState = buttonState;
    COROUTINE_DELAY(20);
  }
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  while (!Serial); // Leonardo/Micro

  pinMode(LED, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  CoroutineScheduler::setup();
}

void loop() {
  CoroutineScheduler::loop();
}
