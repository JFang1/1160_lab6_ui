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
#define COL
IORD_ALTERA_AVALON_PIO_DATA(PIO_IN_BASE)
#define PASS 1234
