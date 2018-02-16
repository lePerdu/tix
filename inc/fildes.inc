;
; fildes.inc
;
; Functions for dealing with file descriptors at the lowest level.
;

#ifndef FILDES_INC_
#define FILDES_INC_

;; filtab_ent structure describing an entry in the system-wide file table.
;   16  inode | dev - The inode or device identifier, depending on the type of
;                     file
;   16  flags - The flags and type of the file. The MSB is the type (S_IF*) and
;              the LSB is the open() flags (O_*).
;   16  offset | device - The offset into the file, if appllicable.
;   8   refs - The number of references to this entry.
; When an entry is unused, the inode/dev field will be set to $FF (and, as such,
; that value should be invalid in either case).
;
filtab_ent_inode    .equ 0
filtab_ent_dev      .equ 0
filtab_ent_flags    .equ 2
filtab_ent_offset   .equ 4
filtab_ent_refs     .equ 6

; Round up to make the math easier. There will probably be more data added
; eveentually anyway.
sizeof_filtab_ent   .equ 8

;; Information stored by a file descriptor.
;   u7  tab_idx - The index in the system file table.
;   bit cloexec - FD_CLOEXEC bit.
; This is set to $FF when the file descriptor is not open.
;
fildes_tab_idx .equ 0

sizeof_fildes .equ 1

;; Structure used to store file locks (not to be confused with the flock
;; structure, which is used for passing information to/from fcntl()).
flock_ent_type  .equ 0
flock_ent_inode .equ 1
flock_ent_start .equ 3
flock_ent_len   .equ 5
flock_ent_pid   .equ 7

sizeof_flock_ent .equ 8

;; The maximum number of file descriptors a process can have open at any time.
OPEN_MAX .equ 16

;; The maximum number of open file descriptions the system can have open at any
;; time.
SYS_OPEN_MAX .equ OPEN_MAX * 2

;; The maximum number of file locks that system can maintain at any time.
FLOCK_MAX .equ SYS_OPEN_MAX

#endif

