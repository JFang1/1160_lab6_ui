#include <stdio.h>
#include <unistd.h>
#include "sys/alt_irq.h"
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "alt_types.h"
// Cursor movement on the LCD:
// Start escape sequence
#define ESC 27
// Clear screen and position cursor at row 1, column 1 of LCD.
#define ESC_CLEAR "[2J"
#define COL IORD_ALTERA_AVALON_PIO_DATA(PIO_IN_BASE)
#define PASS 1234

#include "hello_world.h"
FILE* lcd;
// LCD
volatile int edge_capture;
// Edge capture value
volatile int key = -1;
// Key pressed
volatile int state = 1;
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



//TODO: Handle the polling, decoding, and debouncing of the keypad--Even then, there still may be hardware needed to be debounced

int main() {
  lcd = fopen(COL, "w");  ///////////////TODO: I have no idea if this is right or not
  initColumns();
  logIn();
  fprintf(lcd, "Goodbye!");
  sleep(2);
  fclose(lcd);
  return 0;
}

void initColumns() { /////////////////////TODO
  return;
}

int getKey() {
  int keyValue = fscanf(lcd);
  return keyValue;
}

void logIn() (
  int i = 1;
  int logInKeyValue;
  fprintf(lcd, "Enter Password:");
  while (i) {
    logInKeyValue = getKey();
    if (logInKeyValue == ESC) {
      return;
    }
    else if (logInKeyValue != PASS)
    {
      logInError();
    }
    else { // then the password was entered correctly--exit while loop
      i = 0;
      menu(); // This is called here because it should be accessible only to those who enter the password correctly;
    }
  }
  return;
)

void logInError() {
  fprintf(lcd, "Incorrect");
  sleep(2); // waits for 2 seconds
  return;
}

void menu() {
  fprintf(lcd, "Press: 1 temp 2 light 3 logout");
  int menuKeyValue = getKey();  ////////////////////// TODO: might need some kind of loop for waiting for user input
  if (menuKeyValue == 1) {
    tempMenu();
  }
  else if (menuKeyValue == 2) {
    lightMenu();
  }
  else if (menuKeyValue == 3 || menuKeyValue == ESC)
  return;
}

void tempMenu() {

  return;
}

void lightMenu() {

  return;
}

static void tempCurrent(int temp) {
  return;
}

// The temperature setting should range from 0 to 200, and the light settings will be Off (1), Low (2), Medium (3), and (4)
static int tempChange (void) {
  int temp;
  return temp;
}

static void lightCurrent(int light) {
  return;
}

int lightChange() (
  int value;
  return value;
)
