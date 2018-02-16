;
; priv.inc
;
; Aliases for functions on the privilaged page.
;

#ifndef PRIV_INC_
#define PRIV_INC_

#include "flash.inc"

; TODO Make this dependent on the version
priv_page         .equ $6C

priv_unlock_flash   .equ MEM_BANK_A_ADDR
priv_lock_flash     .equ priv_unlock_flash + 3

#endif

