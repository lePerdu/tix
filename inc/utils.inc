;
; utils.inc
;
; Various macros used in other headers.
;

#ifndef UTILS_INC_
#define UTILS_INC_

#macro DEFINE_OR_MASK(name, bit_idx)
#define __str_name concat("\"", name, "\"")
    clr()
    wr("BIT_", __str_name, " .equ ", bit_idx)
    wr(__str_name, " .equ 1 << ", bit_idx)
    run()
#undefine __str_name
#endmacro

#macro DEFINE_AND_MASK(name, bit_idx)
#define __str_name concat("\"", name, "\"")
    clr()
    wr("BIT_", __str_name, " .equ ", bit_idx)
    wr(__str_name, " .equ ~(1 << ", bit_idx, ") & $FF")
    run()
#undefine __str_name
#endmacro

#macro ROUND_POW2(val)
#if val > 128
    .error "Cannot round ", val, " to nearest 8-bit power of 2."
#elif val > 64
    128
#elif val > 32
    64
#elif val > 16
    32
#elif val > 8
    16
#elif val > 4
    8
#elif val > 2
    4
#else
    val
#endif
#endmacro

#macro relocate(new_location)
#ifdef _relocate_orig
    .error "Cannot nest relocate blocks."
#else
#define _relocate_orig eval($)
#define _relocate_new eval(new_location)
    .org new_location
#endif
    ; clr()
    ; wr("#ifdef relocate_orig_loc_",id," \\")
    ;     wr(".error \"Cannot nest relocate blocks with the same id.\" \\")
    ; wr("#else \\")
    ;     wr("#define relocate_orig_loc_",id," eval($) \\")
    ;     wr(".org new_location\\")
    ;     wr("#define relocate_new_loc_",id," eval(new_location) \\")
    ; wr("#endif")
    ; run()
#endmacro

#macro endrelocate()
#ifndef _relocate_new
    .error "Cannot find relocate start."
#else
    .org $ - _relocate_new + _relocate_orig
#undefine _relocate_orig
#undefine _relocate_new
#endif
    ; clr()
    ; wr("#ifndef relocate_new_loc_",id," \\")
    ;     wr(".error \"Cannot find relocate start\" \\")
    ; wr("#else \\")
    ;     wr(".org $ - relocate_new_loc_",id," + relocate_orig_loc_",id," \\")
    ;     wr("#undefine relocate_orig_loc_",id," \\")
    ;     wr("#undefine relocate_new_loc_",id," \\")
    ; wr("#endif")
    ; run()
#endmacro

#endif

