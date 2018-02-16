;
; flash.inc
;
; Defines for dealing with flash ROM.
;

#ifndef FLASH_INC_
#define FLASH_INC_

FLASH_PAGE_SIZE .equ $4000

MEM_BANK_A_ADDR .equ $4000
MEM_BANK_B_ADDR .equ $8000
MEM_BANK_C_ADDR .equ $C000

;; Verifies that the code is not too large to fit ont a page.
#macro FLASH_PAGE_END(start, page)
    #define _page_hex concat("\"", page / 16, page % 16, "\"")
    #if $ - start > $4000
        .error "Page ", _page_hex, " is ", $ - start - $4000, " bytes too long."
    #else
        .echo "Page ", _page_hex, ": ", $ - start, " bytes."
    #endif
    #undefine _page_hex

    .end
#endmacro

#endif

