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



//TODO: handle the polling, decoding, and debouncing of the keypad--Even then, there still may be hardware needed to be debounced

int main() {
  lcd = fopen(COL, "w");
  initColumns();
  logIn();
  menu();
  fclose(lcd);
  return 0;
}

void initColumns() { /////////////////////
  return;
}

int getKey() {
  int keyValue = scanf(lcd);
  return keyValue;
}

void logIn() (
  int i = 1;
  while (i) {
    /// if wrong password
    {
      logInError();
    }
  }

  return;
)

void logInError() {
  printf("Incorrect");
  pause(1000); ////////////////////
  return;
}

void menu() {
  fprintf("Press: 1 temp 2 light 3 logout");
  int menuKeyValue = getKey();  ////////////////////// TODO: might need some kind of loop for waiting for user input
  if (menuKeyValue == 1) {
    tempMenu();
  }
  if (menuKeyValue == 2) {
    lightMenu();
  }
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
