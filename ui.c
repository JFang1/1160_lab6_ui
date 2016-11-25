#include <stdio.h>
#include <unistd.h>
#include "sys/alt_irq.h"
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "alt_types.h"
#include "hello_world.h"

// Cursor movement on the LCD:
// Start escape sequence
#define ESC 27
// Clear screen and position cursor at row 1, column 1 of LCD.
#define ESC_CLEAR "[2J"
#define COL IORD_ALTERA_AVALON_PIO_DATA(PIO_IN_BASE)
#define PASS 1234///

FILE* lcd;
// LCD
volatile int edge_capture;      // TODO: WTF is this?????
// Edge capture value
volatile int key = -1;          // TODO: Use this
// Key pressed
volatile int state = 1;         // TODO: Us this too
// State
static void initColumns();
static int getKey();
static void logIn(void);
static void logInError(void);
static void invalidInput(void);
static void menu(void);
static void tempMenu(void);
static void lightMenu(void);
static void tempCurrent(int temp);
static int tempChange (void);
static void lightCurrent(int light);
static int lightChange(void);

enum lightSettings = {Off, Low, Medium, High};
int currentTemp = 0;
int currentLight = Off;



//TODO: Handle the polling, decoding, and debouncing of the keypad--Even then, there still may be hardware needed to be debounced
// Note: the hardware can handle the polling, decoding, and debouncing of the keypad instead.

int main() {
  lcd = fopen(COL, "w");  ///////////////TODO: I have no idea if opening COL is right or not
  initColumns();
  logIn();
  fprintf(lcd, ESC_CLEAR); //clears the screen
  fprintf(lcd, "Goodbye!");
  sleep(2); // I'm assuming that this will keep the "Goodbye!" message on the screen for 2 seconds
  fprintf(lcd, ESC_CLEAR); //clears the screen
  fclose(lcd);
  return 0;
}

void initColumns() { /////////////////////TODO What do I do here?????????
  return;
}

int getKey() {
  int keyValue = fscanf(lcd); ////////////////////// TODO: might need some kind of loop or timer for waiting for user input, and/or getting ALL of the user input
  return keyValue;
}

void logIn() (
  int loop = 1;
  int logInKeyValue;
  fprintf(lcd, ESC_CLEAR);
  fprintf(lcd, "Enter Password:");
  while (loop) {
    logInKeyValue = getKey();
    if (logInKeyValue == ESC) {
      return;
    }
    else if (logInKeyValue != PASS)
    {
      logInError();
    }
    else { // then the password was entered correctly--exit while loop
      loop = 0;
      menu(); // This is called here because it should be accessible only to those who enter the password correctly;
    }
  }
  return;
)

void logInError() {
  fprintf(lcd, ESC_CLEAR);
  fprintf(lcd, "Incorrect");
  sleep(2); // waits for 2 seconds--I'm assuming this keeps the "Incorrect" message on the screen for two seconds in addition to waiting before returning
  return;
}

void invalidInput() {
  fprintf(lcd, ESC_CLEAR);
  fprintf(lcd, "invalidInput");
  sleep(2); // waits for 2 seconds--I'm assuming this keeps the "Incorrect" message on the screen for two seconds in addition to waiting before returning
  return;
}

void menu() {
  fprintf(lcd, ESC_CLEAR);
  fprintf(lcd, "Press: 1 temp 2 light 3 logout");
  int menuKeyValue;
  while (1 ) {
    menuKeyValue = getKey();
    if (menuKeyValue == 1) {
      tempMenu();
    }
    else if (menuKeyValue == 2) {
      lightMenu();
    }
    else if (menuKeyValue == 3 || menuKeyValue == ESC) {
      return;
    }
    else {
      invalidInput();
      fprintf(lcd, ESC_CLEAR);
      fprintf(lcd, "Press: 1 temp 2 light 3 logout");
    }
  }
}

void tempMenu() { //According to the flow diagram given in the example, you don't return to this menu
  fprintf(lcd, ESC_CLEAR);
  fprintf(lcd, "Press: 1 view current 2 change");
  int tempMenuKeyValue;
  while(1) {
    tempMenuKeyValue = getKey();
    if (tempMenuKeyValue == 1) {
      tempCurrent();
      return;
    }
    else if (tempMenuKeyValue == 2) {
      tempChange();
      return;
    }
    else if (tempMenuKeyValue == ESC) {
      return;
    }
    else {
      invalidInput();
      fprintf(lcd, ESC_CLEAR);
      fprintf(lcd, "Press: 1 view current 2 change");
    }
  }
}

void lightMenu() { // According to the flow diagram given in the example, you don't return to this menu
  fprintf(lcd, ESC_CLEAR);
  fprintf(lcd, "Press: 1 view current 2 change");
  int lightMenuKeyValue;
  while(1) {
    lightMenuKeyValue = getKey();
    if (lightMenuKeyValue == 1) {
      lightCurrent();
      return;
    }
    else if (lightMenuKeyValue == 2) {
      lightChange();
      return;
    }
    else if (lightMenuKeyValued == ESC) {
      return;
    }
    else {
      invalidInput();
      fprintf(lcd, ESC_CLEAR);
      fprintf(lcd, "Press: 1 view current 2 change");
    }
  }

}

static void tempCurrent(int temp) {
  fprintf(lcd, ESC_CLEAR);
  fprintf("Current temp: %d", currentTemp);
  return;
}

// The temperature setting should range from 0 to 200, and the light settings will be Off (1), Low (2), Medium (3), and (4)
static int tempChange (void) {
  fprintf(lcd, ESC_CLEAR);
  fprintf(lcd, "Enter temp deg F: 0 Min 200 MAX");
  int newTemp;
  while(1) {
    newTemp = getKey();
    if (newTemp =< 200) {
      break;
    }
    else {
      invalidInput();
      fprintf(lcd, ESC_CLEAR);
      fprintf(lcd, "Enter a temp 0 to 200 deg F:");
    }
  }
  currentTemp = newTemp;
  return newTemp;
}

static void lightCurrent(int light) {
  fprintf(lcd, ESC_CLEAR);
  switch (currentLight) {
    case 1:
      fprintf(lcd, "Current light: Off");
      break;
    case 2:
      fprintf(lcd, "Current light: Low");
      break;
    case 3:
      fprintf(lcd, "Current light: Medium");
      break;
    case 4:
      fprintf(lcd, "Current light: High");
      break;
    default:
      fprintf(lcd, "Massive Error");
  }
  return;
}

static int lightChange() (
  fprintf(lcd, ESC_CLEAR);
  fprintf(lcd, "Enter light level: 1 off 2 low 3 medium 4 high");
  int newLValue;
  while(1) {
    newLValue = getKey();
    if (newLValue >=1 && newLValue <=4) {
      break;
    }
    else {
      invalidInput();
      fprintf(lcd, ESC_CLEAR);
      fprintf(lcd, "Enter light level: 1 off 2 low 3 medium 4 high");
    }
  }
  currentLight = newLValue;
  return newLValue;
)
