;
; text.inc
;
; Defines for printing text.
;

#ifndef TEXT_INC_
#define TEXT_INC_

; Dimensions for fonts
TEXT_COL_COUNT_5X7 .equ 16
TEXT_ROW_COUNT_5X7 .equ 8
TEXT_COL_COUNT_3X5 .equ 24
TEXT_ROW_COUNT_3X5 .equ 10

; Character code equates
; Values such as EOL, STOP, etc. are the same (defaults) as those used by Linux.
; Others such as DOWN, GPOS, etc. are used as cursor/text manipulation
; functions.
CHAR_NUL    .equ $00
CHAR_EOL    .equ CHAR_NUL
CHAR_INTR   .equ $03 ; ETX
CHAR_EOF    .equ $04 ; EOT
CHAR_BEL    .equ $07
CHAR_BS     .equ $08
CHAR_ERASE  .equ CHAR_BS
CHAR_HT     .equ $09
CHAR_LF     .equ $0A
CHAR_NL     .equ CHAR_LF
CHAR_VT     .equ $0B
CHAR_FF     .equ $0C
CHAR_CR     .equ $0D
CHAR_START  .equ $11 ; DC1
CHAR_GPOS   .equ $12 ; DC2
CHAR_STOP   .equ $13 ; DC3
CHAR_SPOS   .equ $14 ; DC4
CHAR_KILL   .equ $15 ; NAK
CHAR_UP     .equ $16 ; SYN
CHAR_DOWN   .equ $17 ; ETB
CHAR_RIGHT  .equ $18 ; CAN
CHAR_LEFT   .equ $19 ; EM
CHAR_SUSP   .equ $1A ; SUB
CHAR_ESC    .equ $1B
CHAR_QUIT   .equ $1C ; FS
CHAR_DEL    .equ $7F

CHAR_NOPRINT .equ CHAR_DEL

#endif

