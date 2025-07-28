#include <Wire.h>

#define buzzer A0

const uint16_t noteTable[] PROGMEM = {
    {note_table}
};
const int8_t compressedMelody[] PROGMEM = {
    {compressed_melody}
};
// logic below adjusted from https://github.com/robsoncouto/arduino-songs
int tempo = {tempo};
int wholenote = (60000 * 4) / tempo;
int notes = sizeof(compressedMelody) / 2;

void setup() {
    for (int i = 0; ; i += 2) {
        uint8_t noteIndex = pgm_read_byte(&compressedMelody[i]);
        if (noteIndex == 255) break;

        uint8_t duration = pgm_read_byte(&compressedMelody[i + 1]);
        uint16_t noteFreq = pgm_read_word(&noteTable[noteIndex]);
        int noteDuration;
        if (duration > 0) {
        noteDuration = wholenote / duration;
        } else {
        noteDuration = (wholenote / abs(duration)) * 1.5;
        }
        tone(buzzer, noteFreq, noteDuration * 0.9);
        delay(noteDuration);
        noTone(8);
  }
}

void loop() {
    
}