#include <Rotary.h>

#define ENABLE_PULLUPS 1

const int bt1 = 3;
const int bt2 = 2;
const int bt3 = 1;
const int bt4 = 0;

const int fxL = 5;
const int fxR = 4;

const int start = 8;

const int volLA = 12;
const int volLB = 11;
const int volRA = 10;
const int volRB = 9;

boolean bt1Last = false;
boolean bt2Last = false;
boolean bt3Last = false;
boolean bt4Last = false;

boolean fxLLast = false;
boolean fxRLast = false;

boolean startLast = false;
long buttonMillis[50];

Rotary rotaryLeft = Rotary(volLA, volLB);
Rotary rotaryRight = Rotary(volRA, volRB);

boolean keyboard(boolean last, boolean now, char c, int btn) {
  long m = millis();
  if (buttonMillis[btn] + 10 > m)
    return last;
  if (last == now)
    return last;
  buttonMillis[btn] = m;
  if (now) {
    Keyboard.press(c);
  } else {
    Keyboard.release(c);
  }
  return now;
}

void setup() { // initialize the buttons' inputs:
  pinMode(bt1, INPUT_PULLUP);
  pinMode(bt2, INPUT_PULLUP);
  pinMode(bt3, INPUT_PULLUP);
  pinMode(bt4, INPUT_PULLUP);
  
  pinMode(fxL, INPUT_PULLUP);
  pinMode(fxR, INPUT_PULLUP);
  
  buttonMillis[bt1] = 0;
  buttonMillis[bt2] = 0;
  buttonMillis[bt3] = 0;
  buttonMillis[bt4] = 0;
  buttonMillis[fxL] = 0;
  buttonMillis[fxR] = 0;
  buttonMillis[start] = 0;
//  pinMode(volLA, INPUT_PULLUP);
//  pinMode(volLB, INPUT_PULLUP);
//  pinMode(volRA, INPUT_PULLUP);
//  pinMode(volRB, INPUT_PULLUP);
  
  pinMode(start, INPUT_PULLUP);

  // initialize mouse control:
  Mouse.begin();
  Keyboard.begin();
}

void loop() {
  int rl = rotaryLeft.process();
  int rr = rotaryRight.process();
  if (rl) {
    if (rl == DIR_CW) {
//      Mouse.move(40, 0);
      Keyboard.print('b');
    } else {
//      Mouse.move(-40, 0);
      Keyboard.print('a');
    }
  }
  if (rr) {
    if (rr == DIR_CW) {
//      Mouse.move(0, 40);
      Keyboard.print('d');
    } else {
//      Mouse.move(0, -40);
      Keyboard.print('c');
    }
  }  

  bt1Last = keyboard(bt1Last, digitalRead(bt1) == LOW, '1', bt1);
  bt2Last = keyboard(bt2Last, digitalRead(bt2) == LOW, '2', bt2);
  bt3Last = keyboard(bt3Last, digitalRead(bt3) == LOW, '3', bt3);
  bt4Last = keyboard(bt4Last, digitalRead(bt4) == LOW, '4', bt4);
  
  fxLLast = keyboard(fxLLast, digitalRead(fxL) == LOW, '5', fxL);
  fxRLast = keyboard(fxRLast, digitalRead(fxR) == LOW, '6', fxR);
  
  startLast = keyboard(startLast, digitalRead(start) == LOW, KEY_RETURN, start);
}


