
#include "images.h"
#include "player.h"

#define DEBUG

#define LATCH_PIN  9  // ST_CP of 74HC595 (12)
#define CLOCK_PIN  14  // SH_CP of 74HC595 (11)
#define DATA_PIN  16  // DS of 74HC595 (14)

#define MATRIX_COUNT  2
#define MATRIX_ROWS  8

#define PIR_PIN  8
#define SPEAKER_PIN  7

byte data[MATRIX_COUNT][MATRIX_ROWS];

Player player(SPEAKER_PIN);

bool pir = false;
int melodyCountdown = 1000; // Countdown to next melody (in frames)
int image_0_Countdown = 0; // Countdown to next image (in frames)
int image_1_Countdown = 0; // Countdown to next image (in frames)

#ifdef DEBUG
  // Serial output
  int serial_putchar(char c, FILE *) {
    Serial.write(c);
    return 0;
  };
  FILE serial_out = {0};
#endif

void setupInterrupts() {
  // disable all interrupts
  noInterrupts();

  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0; // Timer1 counter
  int PRESCALER = 1024;
  int FREQUENCY = 200;
  #ifdef DEBUG_MATRIX
    PRESCALER = 8;
    FREQUENCY = 1;  
  #endif

  //                        prescaler
  //                               |   frequency
  //                               |    |
  //                               v    v
  // compare match register 16MHz/64/2000Hz
  OCR1A   = 16000000 / PRESCALER / FREQUENCY - 1;
  TCCR1B |= (1 << WGM12);  // CTC mode

  switch (PRESCALER) {
    case    1:  TCCR1B &= ~(1 << CS12); TCCR1B &= ~(1 << CS11); TCCR1B |=  (1 << CS10); break; // 001
    case    8:  TCCR1B &= ~(1 << CS12); TCCR1B |=  (1 << CS11); TCCR1B &= ~(1 << CS10); break; // 010
    case   64:  TCCR1B &= ~(1 << CS12); TCCR1B |=  (1 << CS11); TCCR1B |=  (1 << CS10); break; // 011
    case  256:  TCCR1B |=  (1 << CS12); TCCR1B &= ~(1 << CS11); TCCR1B &= ~(1 << CS10); break; // 100
    case 1024:  TCCR1B |=  (1 << CS12); TCCR1B &= ~(1 << CS11); TCCR1B |=  (1 << CS10); break; // 101
    default:    TCCR1B &= ~(1 << CS12); TCCR1B &= ~(1 << CS11); TCCR1B &= ~(1 << CS10); break; // 000
  }

  TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt

  // enable all interrupts
  interrupts();
}

void interrupt() {
  byte value = 0;
  for(int row = 0; row < MATRIX_ROWS; row++) {
    for(int matrix = 0; matrix < MATRIX_COUNT; matrix++) {
      value = data[matrix][row];

      #ifdef DEBUG_MATRIX
        printf_P(PSTR("matrix: %d, row: %d, value: %d -> "), 
          matrix, row, value);
        Serial.print(value, BIN);
      #endif

      // select row
      shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, B00000001 << row);
      // write byte to it
      shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, ~value);

      #ifdef DEBUG_MATRIX
        printf_P(PSTR("\n\r"));
      #endif
    }
    // send to display
    digitalWrite(LATCH_PIN, LOW);
    digitalWrite(LATCH_PIN, HIGH);
  }
}

ISR( TIMER1_COMPA_vect ) {
  interrupt();
}

void clear() {
  #ifdef DEBUG
    printf_P(PSTR("---- clear ---- \n\r"));
  #endif
  for(int row = 0; row < MATRIX_ROWS; row++) {
    for(int matrix = 0; matrix < MATRIX_COUNT; matrix++) {
      data[matrix][row] = 0;
    }
  }
  delay(5);
}

void position_test(int speed) {
  #ifdef DEBUG
    printf_P(PSTR("---- position_test ---- \n\r"));
  #endif
  // position test
  for(int matrix = 0; matrix < MATRIX_COUNT; matrix++) {
    data[matrix][0] = B10000000;
  }
  delay(speed*5);
  for(int matrix = 0; matrix < MATRIX_COUNT; matrix++) {
    data[matrix][0] = B00000000;
  }
  delay(5);
}

void colshift_test(int speed) {
  #ifdef DEBUG
    printf_P(PSTR("---- colshift_test ---- \n\r"));
  #endif
  // col shift test
  for(int matrix = 0; matrix < MATRIX_COUNT; matrix++) {
    for(int i = 0; i < 8; i++) {
      byte value = B10000000>>i;
      for(int row = 0; row < MATRIX_ROWS; row++) {
        data[matrix][row] = value;  
      }
      delay(speed);
    }
    for(int i = 0; i < 8; i++) {
      data[matrix][i] = 0;
    }
  }
  delay(speed*2);
}

void rowshift_test(int speed) {
  #ifdef DEBUG
    printf_P(PSTR("---- rowshift_test ---- \n\r"));
  #endif
  // row shift test
  for(int row = 0; row < MATRIX_ROWS; row++) {
    for(int matrix = 0; matrix < MATRIX_COUNT; matrix++) {
      data[matrix][row] = B11111111;
    }
    delay(speed);
    for(int matrix = 0; matrix < MATRIX_COUNT; matrix++) {
      data[matrix][row] = 0;
    }
  }
  delay(speed*2);
}

void random_test(int speed) {
  #ifdef DEBUG
    printf_P(PSTR("---- random_test ---- \n\r"));
  #endif
  // random test
  for(int ctr1 = 0; ctr1 < speed*4; ctr1++) { 
    for(int matrix = 0; matrix < MATRIX_COUNT; matrix++) {
      int row = random(MATRIX_ROWS);
      data[matrix][row] = random(254);
    }
    delay(speed/10);
  }
  delay(speed*2);
}

void max_test(int speed) {
  #ifdef DEBUG
    printf_P(PSTR("---- max_test ---- \n\r"));
  #endif
  // max test
  for(int row = 0; row < MATRIX_ROWS; row++) {
    for(int matrix = 0; matrix < MATRIX_COUNT; matrix++) {
      data[matrix][row] = B11111111;
    }
  }
  delay(speed*10);
}

void test() {
  int speed = 40;
  position_test(speed);
  colshift_test(speed);
  rowshift_test(speed);
  random_test(speed);
  max_test(speed);
  clear();
}

void draw(int matrix, int image) {
  const int* image_ref = &images[image][0];
  for(int row = 0; row < MATRIX_ROWS; row++) {
    data[matrix][row] = pgm_read_byte_near(image_ref + row);
  }
  delay(5);
}

void setup() 
{
  #ifdef DEBUG
    // Configure serial output
    Serial.begin(9600);
    fdev_setup_stream(&serial_out, serial_putchar, NULL, _FDEV_SETUP_WRITE);
    stdout = stderr = &serial_out;
  #endif

  // Configure pins
  pinMode( LATCH_PIN, OUTPUT );
  pinMode( CLOCK_PIN, OUTPUT );
  pinMode( DATA_PIN, OUTPUT );

  // Configure timer
  setupInterrupts();

  // upload delay
  delay(250);

  // display test
  test();

  // Initialize PIR sensor
  pinMode(PIR_PIN, INPUT_PULLUP);
}

void loop()
{
  // update melody
  /*player.update();

  pir = digitalRead(PIR_PIN);

  if(melodyCountdown > 0)
    melodyCountdown--;
  if(melodyCountdown == 0 && pir) {
    melodyCountdown = random(10000, 50000);
    player.play();
  }*/

  if(image_0_Countdown > 0)
    image_0_Countdown--;
  if(image_0_Countdown == 0) { 
    image_0_Countdown = random(5000, 20000);
    draw(0, random(10, 17));
  }

  if(image_1_Countdown > 0)
    image_1_Countdown--;
  if(image_1_Countdown == 0) { 
    image_1_Countdown = random(5000, 20000);
    draw(1, random(10, 17));
  }
}

