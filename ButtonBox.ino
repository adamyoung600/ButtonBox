#include <Keypad.h>
#include <Joystick.h>
#include <ClickEncoder.h>

#define NUMBUTTONS 25
#define NUMROWS 3
#define NUMCOLS 6

//define the symbols on the buttons of the keypads
byte buttons[NUMROWS][NUMCOLS] = {
  {1,2,3,4,5,6},
  {7,8,9,10,11,12},
  {13,14,15,16,17,18},
};

byte rowPins[NUMROWS] = {6,7,8}; //connect to the row pinouts of the keypad
byte colPins[NUMCOLS] = {9,10,16,14,15,18}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad buttbx = Keypad( makeKeymap(buttons), rowPins, colPins, NUMROWS, NUMCOLS); 

//initialize an Joystick with 34 buttons;
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, 
  JOYSTICK_TYPE_JOYSTICK, 25, 0,
  false, false, false, false, false, false,
  false, false, false, false, false);

//ClickEncoder *encoder; 
int16_t last, value;

//void timerIsr() {
//  encoder->service();
//}

void setup() {
  Joystick.begin();
//  encoder = new ClickEncoder(D2, D3, D4);
  last = -1;
}

void loop() {
  CheckAllButtons();
  CheckAllPots();
//  CheckEncoder();
}

void CheckAllButtons(void) {
  if (buttbx.getKeys())
  {
     for (int i=0; i<LIST_MAX; i++)   // Scan the whole key list.
      {
         if ( buttbx.key[i].stateChanged )   // Only find keys that have changed state.
          {
          switch (buttbx.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
                  case PRESSED:
                  case HOLD:
                            Joystick.setButton(buttbx.key[i].kchar, 1);
                            break;
                  case RELEASED:
                  case IDLE:
                            Joystick.setButton(buttbx.key[i].kchar, 0);
                            break;
          }
         }   
       }
   }
}

void CheckAllPots(void) {
  Joystick.setXAxis(analogRead(A3));
  Joystick.setYAxis(analogRead(A2));
  Joystick.setZAxis(analogRead(A1));
}

//
//void CheckEncoder(void) {
//  value += encoder->getValue();
//  
//  if (value != last) {
//    last = value;
//
//}
