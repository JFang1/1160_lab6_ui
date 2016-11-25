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
static void menu(void);
static void tempMenu(void);
static void lightMenu(void);
static void tempCurrent(int temp);
static int tempChange (void);
static void lightCurrent(int light);
static int lightChange(void);

int currentTemp;
int currentLight;



//TODO: Handle the polling, decoding, and debouncing of the keypad--Even then, there still may be hardware needed to be debounced

int main() {
  lcd = fopen(COL, "w");  ///////////////TODO: I have no idea if this is right or not
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
  int keyValue = fscanf(lcd); ////////////////////// TODO: might need some kind of loop for waiting for user input, and/or getting ALL of the user input
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
  }

}

static void tempCurrent(int temp) {
  fprintf(lcd, ESC_CLEAR);
  fprintf("Current temp: %d", currentTemp);
  return;
}

// The temperature setting should range from 0 to 200, and the light settings will be Off (1), Low (2), Medium (3), and (4)
static int tempChange (void) {
  int newTemp = getKey();
  currentTemp = newTemp;
  return newTemp;

}

static void lightCurrent(int light) {
  fprintf(lcd, ESC_CLEAR);
  return;
}

static int lightChange() (
  int newLValue = getKey();
  currentLight = newLValue;
  return newLValue;
)
