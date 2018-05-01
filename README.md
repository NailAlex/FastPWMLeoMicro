# FastPWM for Arduino Leonardo and Micro

## Use Timer1 and Timer4(fast timer) for custom PWM frequency setup(example for fan PWM control)

Written by Anonymous 
https://gist.github.com/anonymous/f5dc94881438846cf684#file-fastpwmtest-ino

Modified by Alexander Niskorodnov aka NailMan

License: MIT License
https://mit-license.org/ 


Download the latest version (version 1.1) here :
https://github.com/NailAlex/FastPWMLeoMicro


## HOW TO USE

For TIMER1

```c++
// Frequency modes for TIMER1
#define PWM62k   1   //62500 Hz
#define PWM8k    2   // 7812 Hz
#define PWM1k    3   //  976 Hz
#define PWM244   4   //  244 Hz
#define PWM61    5   //   61 Hz

void pwm91011configure(int mode);
```

Setup PWM value for Pin(9,10 or 11) with Timer1 after call pwm91011configure
```c++
void pwmSet9(int value);
void pwmSet10(int value);
void pwmSet11(int value);
```

Write PWM value for Pin (fast setup in loop)
```c++
void pwmWrite9(int value);
void pwmWrite10(int value);
void pwmWrite11(int value);
```

For TIMER4

```c++
// Frequency modes for TIMER4
#define PWM187k 1   // 187500 Hz
#define PWM94k  2   //  93750 Hz
#define PWM47k  3   //  46875 Hz
#define PWM23k  4   //  23437 Hz
#define PWM12k  5   //  11719 Hz
#define PWM6k   6   //   5859 Hz
#define PWM3k   7   //   2930 Hz

void pwm613configure(int mode);
```

Setup PWM value for Pin(6 or 13) with Timer4 after call pwm613configure
```c++
void pwmSet6(int value);
void pwmSet13(int value);
```

Write PWM value for Pin (fast setup in loop)
```c++
void pwmWrite6(int value);
void pwmWrite13(int value);
```


## WARNINGS

   Do not use analogWrite to pins 6 or 13 if using 
   this functions as they use the same timer.
   
   Those functions will conflict with the 
   MSTIMER2 library.

## History

(May 2018) v1.1 First release. 