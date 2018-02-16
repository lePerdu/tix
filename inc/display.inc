;
; display.inc
;
; Defines for the LCD.
;

#ifndef DISPLAY_INC_
#define DISPLAY_INC_

LCD_HEIGHT .equ 64
LCD_WIDTH  .equ 96

; Restart address for a routine that waits until the LCD driver is free to
; accept a command/data.
rLCD_DELAY .equ $30

#endif

