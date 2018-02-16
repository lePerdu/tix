;
; tix.inc
;
; Equates for system calls.
;

#ifndef TIX_INC_
#define TIX_INC_

;; Addresses for the text and data sections.
; TODO Make macros for starting/ending each section
tixe_text_org .equ $4000
tixe_data_org .equ $C000

;; Macros for starting and ending sections.
; The string "text" or "data" should be passed as parameters.
#macro tixe_sec_start(sec) ; {{{
#ifdef _sec_orig
    .error "Cannot nest sections."
#else
    #define _sec_orig eval($)
    clr()
    wr("#define _sec_start eval(tixe_",sec,"_org)")
    run()
    #undefine _sec_addr_name
    .org _sec_start
#endif
#endmacro
; }}}

#macro tixe_sec_end() ; {{{
#ifndef _sec_start
    .error "No section started."
#else
    .org $ - _sec_start + _sec_orig
    #undefine _sec_start
    #undefine _sec_orig
#endif
#endmacro
; }}}

;; System call macros
; TODO Make the system call identifier 2-byte if necessary in the future.
; rst $08
rsyscall .equ $08
rprivcacll .equ $08

; {{{

.addinstr syscall &       CF 2
; For conditions, simply do call cond, $0008. This is faster than jumping over
; the instructions on the opposite condition whatever the condition is.
.addinstr syscall nz,&    C40008 4
.addinstr syscall z,&     CC0008 4
.addinstr syscall nc,&    D40008 4
.addinstr syscall c,&     DC0008 4
.addinstr syscall po,&    E40008 4
.addinstr syscall pe,&    EC0008 4
.addinstr syscall p,&     F40008 4
.addinstr syscall m,&     FC0008 4

; Privilaged system call is the same as a normal one for now
; rst $08
.addinstr privcall &       CF 2
; For conditions, simply do call cond, $0008. This is faster than jumping over
; the instructions on the opposite condition whatever the condition is.
.addinstr privcall nz,&    C40008 4
.addinstr privcall z,&     CC0008 4
.addinstr privcall nc,&    D40008 4
.addinstr privcall c,&     DC0008 4
.addinstr privcall po,&    E40008 4
.addinstr privcall pe,&    EC0008 4
.addinstr privcall p,&     F40008 4
.addinstr privcall m,&     FC0008 4

; }}}


;; Local calls/jumps/loads
; Instead resolving symmbols when loading programs, they should use these macros
; when loading/jumping using objects/addresses in the program. The loader
; detremines which section the value is in based on its address range
; ($4000-7FFF for text and $C000-FFFF for data).

rlld .equ $10

; {{{

; Call
.addinstr lcall *       CDD7 4
.addinstr lcall nz,*    C4D7 4
.addinstr lcall z,*     CCD7 4
.addinstr lcall nc,*    D4D7 4
.addinstr lcall c,*     DCD7 4
.addinstr lcall po,*    E4D7 4
.addinstr lcall pe,*    ECD7 4
.addinstr lcall p,*     F4D7 4
.addinstr lcall m,*     FCD7 4

; Jump
.addinstr ljp *         C3D7 4
.addinstr ljp nz,*      C2D7 4
.addinstr ljp z,*       CAD7 4
.addinstr ljp nc,*      D2D7 4
.addinstr ljp c,*       DAD7 4
.addinstr ljp po,*      E2D7 4
.addinstr ljp pe,*      EAD7 4
.addinstr ljp p,*       F2D7 4
.addinstr ljp m,*       FAD7 4

; Load
.addinstr lld a,(*)     3AD7 4
.addinstr lld (*),a     32D7 4
.addinstr lld bc,*      01D7 4
.addinstr lld de,*      11D7 4
.addinstr lld hl,*      21D7 4
.addinstr lld sp,*      31D7 4
.addinstr lld ix,*      21DDD7 5
.addinstr lld iy,*      21FDD7 5
.addinstr lld bc,(*)    4BEDD7 5
.addinstr lld de,(*)    5BEDD7 5
.addinstr lld hl,(*)    2AD7 4
.addinstr lld ix,(*)    2ADDD7 5
.addinstr lld iy,(*)    2AFDD7 5
.addinstr lld (*),bc    43EDD7 5
.addinstr lld (*),de    53EDD7 5
.addinstr lld (*),hl    22D7 4
.addinstr lld (*),sp    FD73ED 5
.addinstr lld (*),ix    22DDD7 5
.addinstr lld (*),iy    22FDD7 5

; }}}


;; System call numbers
; TODO Don't suffix everything with '_' to stop it from conflicting with the
; names of the actuall functions these reference.
; {{{
open_       .equ 0
close_      .equ 1
read_       .equ 2
write_      .equ 3
ftruncate_  .equ 4
lseek_      .equ 5

create_     .equ 6
mkdir_      .equ 7
mknod_      .equ 8
link_       .equ 9
unlink_     .equ 10
rmdir_      .equ 11
remove_     .equ 12
rename_     .equ 13

dup_        .equ 14
dup2_       .equ 15
fcntl_      .equ 16

opendir_    .equ 17
closedir_   .equ 18
readdir_    .equ 19
rewinddir_  .equ 20
telldir_    .equ 21
seekdir_    .equ 22

malloc_     .equ 23
calloc_     .equ 24
realloc_    .equ 25
free_       .equ 26

execve_     .equ 27
execv_      .equ 28
fork_       .equ 29
vfork_      .equ 30
wait_       .equ 31
exit_       .equ 32
_exit_      .equ 33
_Exit_      .equ 34

getpid_     .equ 35
getuid_     .equ 36
getgid_     .equ 37
geteuid_    .equ 38
getegid_    .equ 39
setuid_     .equ 40
setgid_     .equ 41
setreuid_   .equ 42
setregid_   .equ 43
chdir_      .equ 44
fchdir_     .equ 45
getenv_     .equ 46
putenv_     .equ 47
getcwd_     .equ 48
getwd_      .equ 49

; TODO Make these local to the kernel
lock_flash_  .equ 50
unlock_flash_   .equ 51

; TODO Write a script to parse the symbol table generated by the assembler on
; the syscall.z80 file instead of defining the numbers here

; }}}


;; OS static data.
; These should be accessed via dld instructions, as they are negative offsets
; from the program's data section.
errno   .equ -4
environ .equ -2

#endif ; TIX_INC_
