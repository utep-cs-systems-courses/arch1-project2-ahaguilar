#ifndef warsBuzz_included
#define warsBuzz_included
#define a 436.05
#define cH 272.54
#define f 348.83
#define c 261.63
#define d 294.33
#define eb 313.96
#define e 327.03
#define fH 367.92
#define g 392.44                   // All notes in HERTZ
#define ab 418.60
#define bb 470.93
#define b 490.55
#define  d3    6803
#define  e3    6061
#define  f3    5714
#define  g3    5102
#define  a3    4545
#define  b3    4049
#define  c4    3816    // 261 Hz
#define  d4    3401    // 294 Hz
#define  e4    3030    // 329 Hz
#define  f4    2865    // 349 Hz
#define  g4    2551    // 392 Hz
#define  a4    2272    // 440 Hz
#define  a4s   2146
#define  b4    2028    // 493 Hz
#define  c5    1912    // 523 Hz
#define  d5    1706
#define  d5s   1608
#define  g5s   1204
#define  e5    1517    // 659 Hz
#define  f5    1433    // 698 Hz
#define  g5    1276
#define  a5    1136
#define  a5s   1073
#define  b5    1012
#define  c6    955
#define r 1                        //REST

void notes();
void state_advance();

#endif
