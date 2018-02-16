;
; process.inc
;
; Constants for process allocation and use.
;

#ifndef PROCESS_INC_
#define PROCESS_INC_

#include "fildes.inc"

;; The number of bytes allocated to each process.
; This allows for 23 processes on calculators with 48 KiB of RAM and 63 on those
; with 128 KiB of RAM (the OS takes up the last frame on page $80).
PROC_FRAME_SIZE .equ 2048

;; Maximum number of child processes a process can have.
; This is the minimum specified by POSIX, though could possibly be larger.
;
CHILD_MAX .equ 6

;; Maximum number of active processes on the system.
; This can include terminated processes which have not been acknowledged to have
; finished by their parent process via a call to wait().
;
PROC_MAX .equ 16

;; Structure of process table entries.
; TODO If threads are implemented as separate from processes, some of these
; (i.e. errno) must be moved the thread header data.
;
;   flags - Flags describing the state of the process (i.e. sleeping).
;   uid, euid, suid - Real, effective, and saved UIDs of the process.
;   gid, egid, sgid - Real, effective, and saved GIDs of the process.
;   status - The exit status, if the process is exited (see flags above).
;   cwd - Inode of the current working directory.
;   text_page, text_addr - Page of the program text section.
;   data_page, data_addr - Page and address of the program data section. This
;       includes os data, program static data, the heap, and the stack.
;   prog_data_addr - Start of program data in the data section.
;   heap_addr - Address of the head node of the allocation list for the
;       process.
;   sp - Stores the stack pointer when the context is saved.
;   fildes[OPEN_MAX] - The file descriptors for the process.
;   children[CHILD_MAX] - PIDs of the children of this process.
;
; TODO Order these based on order/frequency of access.
;
proc_ent_flags      .equ 0
proc_ent_uid        .equ 1
proc_ent_euid       .equ 2
proc_ent_suid       .equ 3
proc_ent_gid        .equ 4
proc_ent_egid       .equ 5
proc_ent_sgid       .equ 6
proc_ent_parent     .equ 7
proc_ent_status     .equ 8
proc_ent_cwd        .equ 10
proc_ent_text_page  .equ 12
proc_ent_text_addr  .equ 13
proc_ent_data_page  .equ 15
proc_ent_data_addr  .equ 16
proc_ent_prog_data_addr  .equ 18
proc_ent_heap_addr  .equ 20
proc_ent_ctx            .equ 22
proc_ent_ctx_page_a .equ 22
proc_ent_ctx_page_c .equ 23
proc_ent_ctx_iy     .equ 24
proc_ent_ctx_ix     .equ 26
proc_ent_ctx_hl     .equ 28
proc_ent_ctx_de     .equ 30
proc_ent_ctx_bc     .equ 32
proc_ent_ctx_af     .equ 34
proc_ent_ctx_end        .equ 36
proc_ent_ctx_sp     .equ 36
proc_ent_ctx_ret    .equ 38
proc_ent_fildes     .equ 40
proc_ent_children   .equ 40 + OPEN_MAX

sizeof_proc_ent .equ 40 + OPEN_MAX + CHILD_MAX

;; Process flags
DEFINE_OR_MASK(PROC_USED,       0)
DEFINE_OR_MASK(PROC_WAITING,    1)
DEFINE_OR_MASK(PROC_SLEEPING,   2)
DEFINE_OR_MASK(PROC_VFORKED,    3)
DEFINE_OR_MASK(PROC_VFORK_PARENT,4)
DEFINE_OR_MASK(PROC_RELOCATE,   6)
DEFINE_OR_MASK(PROC_TERMINATED, 7)


;; Structure for process data stored in a process's data section.
; These are generally accessed relative to the prog_data_addr with negative
; offsets.
;   errno - Errno value for the process.
;   environ - Pointer to the environment.
;
proc_os_data_environ    .equ 0
proc_os_data_errno      .equ 2

sizeof_proc_os_data .equ 4

;; Structure for executable file format (TIXE) header
;   32  tixeh_magic - Magic string "TIXE".
;   16  tixeh_heap_size - Requested heap size.
;   16  tixeh_stack_size - Requested stack size.
;   16  tixeh_text_off - Offset of text section.
;   16  tixeh_text_size - Size of text section.
;   16  tixeh_data_off - Offset of data section.
;   16  tixeh_data_size - Size of data section.
;
tixeh_magic         .equ 0
tixeh_heap_size     .equ 4
tixeh_stack_size    .equ 6
tixeh_text_off      .equ 8
tixeh_text_size     .equ 10
tixeh_data_off      .equ 12
tixeh_data_size     .equ 14

sizeof_tixeh        .equ 16

#endif

