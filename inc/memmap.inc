;
; memmap.inc
;
; Describes the memory layout.
;
; The first memory bank is always (by the hardware) mapped to ROM page 0; this
; houses the most common/crucial system calls. Memory bank A is constantly
; swapped by functions which need to use arbitrary flash locations (i.e.
; filesystem functions) and for system calls not on ROM page 0 to be mapped to
; during execution. Bank B is mapped to the page with the current process's code
; and bank C to the page with its data.
;
; Statically-allocated kernel memory is stored at the start of RAM page 1, so
; that it can be easily mapped and unmapped to bank B without saving the initial
; page on the bank by the use of port $28. To play nice with the allocator, this
; memory is prefixed with an allocation node header so that the allocator does
; not have to do anything special with it.
;

#ifndef MEMMAP_INC_
#define MEMMAP_INC_

#include "keys.inc"
#include "display.inc"
#include "fildes.inc"
#include "flash.inc"
#include "malloc.inc"
#include "process.inc"
#include "terminal.inc"
#include "text.inc"
#include "utils.inc"

RAM_PAGE_START .equ $80
RAM_PAGE_END .equ $87
RAM_PAGE_SIZE .equ $4000

KERNEL_RAM_PAGE .equ $81

; TODO Change these to fit what is necessary
KERNEL_TMP_SIZE .equ $80
FLASH_CODE_SIZE .equ $40

; Grow static memory from the beginning of page $80, mapped to memory bank C.

#macro init_group_(org)
#define __next eval(org)
#endmacro

#macro def_group_(name, size)
#define __str_name concat("\"", name, "\"")
clr()
wr(__str_name, " .equ ", __next)
run()
#define __next eval(__next + size)
#undefine __str_name
#endmacro

; Leave some space for the allocation node to start the allocator and protect
; the kernel ram
init_group_(MEM_BANK_B_ADDR + sizeof_galloc_node)

def_group_(kernel_ram_start, 0)

; Statically allocated RAM for various kernel functions to use. Functions that
; make use of this disable interrupts when doing so to lock the memory region.
def_group_(kernel_tmp, KERNEL_TMP_SIZE)
def_group_(kernel_tmp_end, 0)
; RAM reserved for procedures which write/clear flash
def_group_(flash_code, FLASH_CODE_SIZE)
; Store offsets for the filesystem (normal 3-byte format) so they don't have to
; be looked up in flash every time (only at boot).
def_group_(fs_inode_file, 3)
def_group_(fs_head, 3)
def_group_(fs_tail, 3)
; Store the locations of the current anchor pointers
def_group_(fs_head_anchor, 3)
def_group_(fs_inode_anchor, 3)

; TODO These might be moved
; Input buffer from the keyboard
; This contains 1 extra character so that it can be determined when the buffer
; is full: when end = start - 1 (mod MAX_INPUT+1)
def_group_(term_input_buf, MAX_INPUT+1)
def_group_(term_input_start, 1)
def_group_(term_input_end, 1)
def_group_(term_input_nlines, 1)
def_group_(term_cc, NCSS)
def_group_(term_lflag, 1)
def_group_(term_cflag, 1)
def_group_(term_oflag, 1)
def_group_(term_iflag, 1)
def_group_(term_state, 1)
def_group_(term_esc_buf, 2) ; TODO Rename
def_group_(term_esc_idx, 1)

def_group_(text_flags, 1)
DEFINE_OR_MASK(TEXT_FONT, 0)
TEXT_FONT5X7 .equ 0
TEXT_FONT3X5 .equ 1

def_group_(text_col, 1)
def_group_(text_row, 1)
; LCD driver RAM offset (used for scrolling).
def_group_(text_z_off, 1)

; Stores the position of the cursor. These follow text_row and text_col, but are
; stored separately so that the text position can be changed without turning off
; the cursor each time.
def_group_(text_cursor_col, 1)
def_group_(text_cursor_row, 1)
def_group_(text_cursor_shadow, 7)
; Make the text shadow big enough for the small font
def_group_(text_shadow, TEXT_ROW_COUNT_3X5 * TEXT_COL_COUNT_3X5)
def_group_(text_screen_buf, LCD_HEIGHT * LCD_WIDTH / 8)

def_group_(file_table, SYS_OPEN_MAX * sizeof_filtab_ent)

def_group_(flock_table, FLOCK_MAX * sizeof_flock_ent)

def_group_(cur_pid, 1) ; PID of the current process
def_group_(cur_process, 2) ; Address of the process entry for cur_pid
def_group_(proc_table, PROC_MAX * sizeof_proc_ent)

; Store the last known status of keys so that they are only registered once when
; pressed and held down.
; TODO Repeating would be nice, if possible. I think that if one of the timers
; is set to e.g. 0.5 sec, then it can compare the state of keys and the status
; here. 0.5 sec is probably too long to accurately check the keys, so a faster
; interrupt would have to check when the keys are pressed.
def_group_(key_states_map, KEY_GROUP_COUNT)
; Stores the state of ALPHA and 2ND
def_group_(key_states_special, 1)
DEFINE_OR_MASK(KEY_STATE_SPECIAL_ALPHA, 0)
DEFINE_OR_MASK(KEY_STATE_SPECIAL_ALPHA_LOCK, 1)
DEFINE_OR_MASK(KEY_STATE_SPECIAL_2ND, 2)
DEFINE_OR_MASK(KEY_STATE_SPECIAL_2ND_LOCK, 3)

def_group_(lcd_contrast, 1)

def_group_(kernel_ram_end, 0)

KERNEL_RAM_SIZE .equ kernel_ram_end - kernel_ram_start

KERNEL_RAM_MAP_CMD .equ $FF ;(KERNEL_RAM_SIZE + (KERNEL_RAM_SIZE % 64)) / 64

#macro KERNEL_RAM_MAP()
    ld a, KERNEL_RAM_MAP_CMD
    out (PORT_RAM_01_MAP), a
#endmacro

#macro KERNEL_RAM_UNMAP()
    ld a, 0 ; xor a modifies flags
    out (PORT_RAM_01_MAP), a
#endmacro

#endif

