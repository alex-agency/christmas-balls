#ifndef PLAYER_H
#define PLAYER_H

#include "melody.h"

#define DEBUG

class Player
{
public:
  Player( int _pin ) {
    pin = _pin;
    // reset index
    noteIndex = 0;
    notePause = 0;
    time = 0;
  };

  void beep( uint8_t _beepCount ) {
    if( _beepCount <= 0 )
	  return;
	// set beep count
	beepCount = _beepCount-1;
	// play beep first time
	play(0);
  };

  void play( void ) {
    // play random
    play(random(1, MELODIES-1));
  };

  void play( int _melodyNum ) {
    // initialize speaker pin
    pinMode(pin, OUTPUT);
    numNotes = pgm_read_byte(&melodies[melodyNum].numNotes);
    // prevent new play if previous not ended
    if( noteIndex < numNotes ) 
      return;
    // check number
    if(_melodyNum < 0 || _melodyNum >= MELODIES)
      melodyNum = random(1, MELODIES-1);
    else
      melodyNum = _melodyNum;
    // reset index
    noteIndex = 0;
    notePause = 0;
    time = 0;

    #ifdef DEBUG
      printf_P(PSTR("PLAYER: Info: Play melody #%d with %d notes:\n\r"),
        melodyNum, numNotes);
    #endif
  };

  void update( void ) {
    // beep cycle
    if( beepCount > 0 && noteIndex >= numNotes ) {
      // play beep melody
      play(0);
      beepCount--;
    }
    // skip if it last note or pause between notes
    if( noteIndex >= numNotes || (millis() - time) < notePause ) {
      /*if(TCCR1B == 0 && TCCR1A == 0) {
        cli();
        TCCR1B |= (1 << WGM12);
        TCCR1B |=  (1 << CS12); 
        TCCR1B &= ~(1 << CS11); 
        TCCR1B |=  (1 << CS10);
        sei();
      }*/
      return;
    }
    // stop timer1
    //TCCR1B = 0; TCCR1A = 0;
    // play current note
    playNote();
    // change note cursor
    noteIndex++;
    time = millis(); 
  };

private:
  int pin;
  int beepCount;
  int melodyNum;
  int noteIndex;
  int notePause;
  unsigned long time;
  int numNotes;
 
  void playNote( void ) {
    noTone(pin);
    
    int tempo = pgm_read_word(&melodies[melodyNum].tempo);
    const int* notes = (int*)pgm_read_word(&melodies[melodyNum].notes);
    int note = pgm_read_word(&notes[noteIndex]);  
    int freq = note * 2;
    const int* beats = (int*)pgm_read_word(&melodies[melodyNum].beats);
    int beat = pgm_read_word(&beats[noteIndex]);
    int duration = tempo * beat;

    #ifdef DEBUG 
      printf_P(PSTR("PLAYER: Info: Note #%d, freq: %d*2, duration: %d*%d.\n\r"),
      	noteIndex, note, beat, tempo);
    #endif

    if (freq > 0) {
      tone(pin, freq, duration);
    }
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    notePause = duration + (duration * 0.30);
  };
};

#endif // __PLAYER_H__