;
; terminal.inc
;
; Defines for the terminal interface.
;

#ifndef TERMINAL_INC_
#define TERMINAL_INC_

#include "utils.inc"

; The maximum number of bytes which can be stored in the input queue.
; TODO This is lower than what POSIX wants so that MAX_INPUT+2 can be stored in
; a single byte. The algorithms dealing with the buffer will probably have to
; use addresses instead of offsets in order to store offsets large enough to fix
; this.
MAX_INPUT .equ 253
MAX_CANON .equ MAX_INPUT

DEFINE_OR_MASK(TERM_STATE_CURSOR_ENABLED, 0) ; Cursor is blinking
DEFINE_OR_MASK(TERM_STATE_CURSOR_ON, 1) ; Cursor is visible

DEFINE_OR_MASK(OPOST, 0)

DEFINE_OR_MASK(ICRNL,   0)
DEFINE_OR_MASK(IGNCR,   1)
DEFINE_OR_MASK(INLCR,   2)

DEFINE_OR_MASK(ICANON,  0)
DEFINE_OR_MASK(ECHO,    1)
DEFINE_OR_MASK(ECHOE,   2)
DEFINE_OR_MASK(ECHOK,   3)
DEFINE_OR_MASK(ECHONL,  4)
DEFINE_OR_MASK(IEXTEN,  5)

VEOF    .equ 0
VEOL    .equ 1
VERASE  .equ 2
VINTR   .equ 3
VKILL   .equ 4
VMIN    .equ VEOF
VTIME   .equ VEOL
VQUIT   .equ 5
VSTART  .equ 6
VSTOP   .equ 7
VSUSP   .equ 8

NCSS    .equ 9

#endif

