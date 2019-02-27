 #include "pitches.h"

// notes in the melody:
int melody[] = {
  NOTE_G6, NOTE_GS6, NOTE_A6, NOTE_AS6, NOTE_B6, 
};

int noteDurations[] = {
  6, 8, 8, 8, 4,};
void setup() {
  
  for (int thisNote = 0; thisNote < 25; thisNote++) {

    int noteDuration = 1000/noteDurations[thisNote];
    tone(4, melody[thisNote],noteDuration);

    int pauseBetweenNotes = noteDuration * 1.10;
    delay(pauseBetweenNotes);
    noTone(4);
  }
}
void loop() {
  // no need to repeat the melody.
}
