#ifndef MELODY_H
#define MELODY_H

#include "pitches.h"

#define MELODIES  6

typedef struct PROGMEM {
  const int *notes;
  const int *beats;
  const int numNotes;
  const int tempo;
} melody_def;

// Beep
static const int PROGMEM 
beep_notes[] 				= { N_A5, N_E5, N_REST };
static const int PROGMEM
beep_beats[]  				= { 2,    2,    4 };
static const int PROGMEM
beep_tempo			 		= 50;

// "Jingle Bells" melody
static const int PROGMEM
jingleBells_notes[]  		= { N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_G5, 
				    			N_C5, N_D5, N_E5, N_F5, N_F5, N_F5, N_F5, N_F5, 
				    			N_E5, N_E5, N_E5, N_E5, N_D5, N_D5, N_E5, N_D5, 
								N_G5, N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, 
								N_G5, N_C5, N_D5, N_E5, N_F5, N_F5, N_F5, N_F5, 
								N_F5, N_E5, N_E5, N_E5, N_G5, N_G5, N_F5, N_D5, 
								N_C5 };
static const int PROGMEM
jingleBells_beats[] 		= { 4, 	  4,    8,    4,    4,    8,    4,    4, 
								4,    4,   16,    4,    4,    4,    4,    4, 
								4,    4,    4,    4,    4,    4,    4,    8, 
								8,    4,    4,    8,    4,    4,    8,    4, 
								4,    4,    4,   16,    4,    4,    4,    4, 
								4,    4,    4,    4,    4,    4,    4,    4, 
								16 };
static const int PROGMEM
jingleBells_tempo			= 60;

// "The first noel" melody
static const int PROGMEM
firstNoel_notes[] 			= { N_E4, N_D4, N_C4, N_D4, N_E4, N_F4, N_G4, N_A4, 
								N_B4, N_C5, N_B4, N_A4, N_G4, N_A4, N_B4, N_C5, 
								N_B4, N_A4, N_G4, N_A4, N_B4, N_C5, N_G4, N_F4,
								N_E4, N_E4, N_D4, N_C4, N_D4, N_E4, N_F4, N_G4, 
								N_A4, N_B4, N_C5, N_B4, N_A4, N_G4, N_A4, N_B4, 
								N_C5, N_B4, N_A4, N_G4, N_A4, N_B4, N_C5, N_G4, 
								N_F4, N_E4, N_E4, N_D4, N_C4, N_D4, N_E4, N_F4, 
								N_G4, N_C5, N_B4, N_A4, N_A4, N_G4, N_C5, N_B4, 
								N_A4, N_G4, N_A4, N_B4, N_C5, N_G4, N_F4, N_E4 };
static const int PROGMEM
firstNoel_beats[] 			= { 2, 	  2,    6,    2,    2,    2,    8,    2, 
								2,    4,    4,    4,    8,    2,    2,    4, 
								4,    4,    4,    4,    4,    4,    4,    4,
								8,    2,    2,    6,    2,    2,    2,    8, 
								2,    2,    4,    4,    4,    8,    2,    2, 
								4,    4,    4,    4,    4,    4,    4,    4, 
								4,    8,    2,    2,    6,    2,    2,    2, 
								8,    2,    2,    8,    4,   12,    4,    4,
								4,    4,    4,    4,    4,    4,    4,    8 };
static const int PROGMEM
firstNoel_tempo 			= 60;

// "What child is this" melody
static const int PROGMEM
whatChild_notes[] 			= { N_E4, N_G4, N_A4, N_B4, N_C5, N_B4, N_A4, N_FS4, 
								N_D4, N_E4, N_FS4, N_G4, N_E4, N_E4, N_DS4, N_E4, 
								N_FS4, N_B3, N_REST, N_E4, N_G4, N_A4, N_B4, N_C4, 
								N_B4, N_A4, N_FS4, N_D4, N_E4, N_FS4, N_G4, N_FS4, 
								N_E4, N_DS4, N_CS4, N_D4, N_E4, N_E4, N_REST, N_D5, 
								N_D5, N_C5, N_B4, N_A4, N_FS4, N_D4, N_E4, N_FS4, 
								N_G4, N_E4, N_E4, N_DS4, N_E4, N_FS4, N_DS4, N_B3, 
								N_REST, N_D5, N_D5, N_C5, N_B4, N_A4, N_FS4, N_D4, 
								N_E4, N_FS4, N_G4, N_FS4, N_E4, N_DS4, N_CS4, N_D4, 
								N_E4, N_E4 };
static const int PROGMEM
whatChild_beats[] 			= { 2,    4,    2,    3,    1,    2,    4,    2, 
	   							3,    1,    2,    4,    2,    3,    1,    2, 
	   							6,    2,    2,    2,    4,    2,    3,    1, 
	   							2,    4,    2,    3,    1,    2,    3,    1, 
	   							2,    3,    1,    2,    6,    4,    2,    6,
	   							3,    1,    2,    4,    2,    3,    1,    2, 
	   							4,    2,    3,    1,    2,    4,    2,    4, 
	   							2,    6,    3,    1,    2,    4,    2,    3, 
	   							1,    2,    3,    1,    2,    3,    1,    2, 
	   							6,    4 };
static const int PROGMEM
whatChild_tempo 			= 100;

// "R2D2" melody
static const int PROGMEM
r2d2_notes[] 				= { N_A6, N_G6, N_E6, N_C6, N_D6, N_B6, N_F6, N_C7,
                     			N_A6, N_G6, N_E6, N_C6, N_D6, N_B6, N_F6, N_C7 };
static const int PROGMEM
r2d2_beats[] 				= { 2,    2,    2,    2,    2,    2,    2,    2,
                               	2,    2,    2,    2,    2,    2,    2,    2 };
static const int PROGMEM
r2d2_tempo 					= 40;

// "Gangnam Style" melody
static const int PROGMEM
gangnam_notes[] 			= { N_A4, N_A4, N_C5, N_REST, N_A4, N_REST, N_E5, N_E5,
	  							N_E5, N_REST, N_D5, N_REST, N_D5, N_D5, N_E5, N_REST,
	  							N_REST, N_E5, N_E5, N_E5, N_E5, N_REST, N_REST, N_E5,
	  							N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_E5,
	  							N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_E5,
                				N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_E5,
                				N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_REST, 
                				N_REST, N_A4, N_A4, N_C5, N_C5, N_A4, N_REST, N_REST };
static const int PROGMEM
gangnam_beats[] 			= { 8,    8,    4,    8,    8,    4,    8,    8,
	  							4,    8,    8,    4,    8,    8,    4,    8,
	  							4,    8,    8,    8,    4,    8,    4,    8,
	  							8,    8,    8,    8,    8,    8,    8,    8,
								8,    8,    4,    4,    4,    4,    16,   16,
							    16,   16,   16,   16,   16,   16,   16,   16,
							    16,   16,   16,   16,   16,   16,   1,    1,
							    4,    8,    8,    8,    8,    4,    1,    4 };
static const int PROGMEM
gangnam_tempo 				= 40;


static const melody_def PROGMEM
melodies[MELODIES] = {
  // Beep
  {
    (int*)&beep_notes,
    (int*)&beep_beats,
    sizeof(beep_notes)/sizeof(int), 
    beep_tempo
  },
  // "Jingle Bells" melody
  {
    (int*)&jingleBells_notes,
    (int*)&jingleBells_beats,
    sizeof(jingleBells_notes)/sizeof(int), 
    jingleBells_tempo  	
  },
  // "The first noel" melody
  {
    (int*)&firstNoel_notes,
    (int*)&firstNoel_beats,
    sizeof(firstNoel_notes)/sizeof(int), 
    firstNoel_tempo  	
  },
  // "What child is this" melody
  {
    (int*)&whatChild_notes,
    (int*)&whatChild_beats,
    sizeof(whatChild_notes)/sizeof(int), 
    whatChild_tempo  	
  },
  // "R2D2" melody
  {
    (int*)&r2d2_notes,
    (int*)&r2d2_beats,
    sizeof(r2d2_notes)/sizeof(int), 
    r2d2_tempo  	
  },
  // "Gangnam Style" melody
  {
    (int*)&gangnam_notes,
    (int*)&gangnam_beats,
    sizeof(gangnam_notes)/sizeof(int), 
    gangnam_tempo  	
  }
};

#endif // __MELODY_H__