/**********************************************************
                Fast PWM Test Library
Written by Anonymous 
https://gist.github.com/anonymous/f5dc94881438846cf684#file-fastpwmtest-ino

Modified by Alexander Niskorodnov aka NailMan

**********************************************************

This Library used for ATMega32U4 IC only - Arduino Leonardo and Micro!

FOR OTHER MEGA328/2560 ARDUINAS USE THIS LIBRARY
http://code.google.com/p/arduino-pwm-frequency-library/downloads/list

**********************************************************
Demostrates the generation of high speed PWM
using timers 1 and 4
There are two pieces of code:
One for pins 9, 10 and 11 using TIMER 1
with frequencies up to 62kHz
Other for pins 6 and 13 using TIMER 4
with frequencies up to 187kHz
History:
  12/12/2014 - Version 1.0
  22/12/2014 - Adding a missing OCR4C value
  
***********************************************************/

/**********************************************************
   Fast PWM on pins 9,10,11 (TIMER 1)
   
   Do not use analogWrite to pins 9, 10 or 11 if using 
   this functions as they use the same timer.
   
   Those functions will probably conflict with the 
   servo library.
   
   Uses 5 PWM frequencies between 61Hz and 62.5kHz
   
**********************************************************/

#ifndef PWM_32U4_h
#define PWM_32U4_h 

// Frequency modes for TIMER1
#define PWM62k   1   //62500 Hz
#define PWM8k    2   // 7812 Hz
#define PWM1k    3   //  976 Hz
#define PWM244   4   //  244 Hz
#define PWM61    5   //   61 Hz

// Direct PWM change variables
#define PWM9   OCR1A
#define PWM10  OCR1B
#define PWM11  OCR1C

// Configure the PWM clock
// The argument is one of the 5 previously defined modes
void pwm91011configure(int mode);

// Set PWM to D9
// Argument is PWM between 0 and 255
void pwmSet9(int value);

// Set PWM to D10
// Argument is PWM between 0 and 255
void pwmSet10(int value);


// Set PWM to D11
// Argument is PWM between 0 and 255
void pwmSet11(int value);



/**********************************************************
   Fast PWM on pins 6, 13 (High Speed TIMER 4)
   
   Do not use analogWrite to pins 6 or 13 if using 
   this functions as they use the same timer.
   
   Those functions will conflict with the 
   MSTIMER2 library.
   Uses 7 PWM frequencies between 2930Hz and 187.5kHz
   
   Timer 4 uses a PLL as input so that its clock frequency
   can be up to 96MHz on standard Arduino Leonardo.
   We limit imput frequency to 48MHz to generate 187.5kHz PWM
   If needed, we can double that up to 375kHz
**********************************************************/

// Frequency modes for TIMER4
#define PWM187k 1   // 187500 Hz
#define PWM94k  2   //  93750 Hz
#define PWM47k  3   //  46875 Hz
#define PWM23k  4   //  23437 Hz
#define PWM12k  5   //  11719 Hz
#define PWM6k   6   //   5859 Hz
#define PWM3k   7   //   2930 Hz

// Direct PWM change variables
#define PWM6        OCR4D
#define PWM13      OCR4A

// Terminal count
#define PWM6_13_MAX OCR4C

// Configure the PWM clock
// The argument is one of the 7 previously defined modes
void pwm613configure(int mode);


// Set PWM to D6 (Timer4 D)
// Argument is PWM between 0 and 255
void pwmSet6(int value);


// Set PWM to D13 (Timer4 A)
// Argument is PWM between 0 and 255
void pwmSet13(int value);


/*************** ADDITIONAL DEFINITIONS ******************/

// Macro to converts from duty (0..100) to PWM (0..255)
#define DUTY2PWM(x)  ((255*(x))/100)

void pwmWrite9(int value);

void pwmWrite10(int value);

void pwmWrite11(int value);

void pwmWrite6(int value);

void pwmWrite13(int value);

#endif
