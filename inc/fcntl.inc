;
; fcntl.inc
;
; Defines constants for file control functions.
;

#ifndef FCNTL_INC_
#define FCNTL_INC_

#include "memmap.inc"
#include "utils.inc"

NAME_MAX .equ 14
PATH_MAX .equ 255

; Commands for fcntl()
F_DUPFD .equ 1
F_DUPFD_CLOEXEC .equ 2
F_GETFD .equ 3
F_SETFD .equ 4
F_GETFL .equ 5
F_SETFL .equ 6
F_GETLK .equ 7
F_SETLK .equ 8
F_SETLKW .equ 9
F_GETOWN .equ 10
F_SETOWN .equ 11

;; Flag in file descriptor for closing upon callling exec*() functions.
; Put in the MSB so that it can co-exist in the same byte as a file table index
; in a file descriptor. This is really bad practice, but I am pretty sure that
; there will never be more than 127 file table entries available on the system,
; and using an extra byte in file descriptors for a single flag is really
; wasteful.
DEFINE_OR_MASK(FD_CLOEXEC, 7)

; Special file descriptor value for *at() functions.
AT_FDCWD    .equ $7FFF ; TODO Should this be single-byte?

; Flags for some *at() functions.
DEFINE_OR_MASK(AT_SYMLINK_FOLLOW, 0)
DEFINE_OR_MASK(AT_SYMLINK_NOFOLLOW, 1)
DEFINE_OR_MASK(AT_REMOVEDIR, 2)

; Possible values for the type field in flock
F_UNLCK .equ 0
F_RDLCK .equ 1
F_WRLCK .equ 2

;; Structure for passing data in and out of fcntl().
flock_type      .equ 0
flock_whence    .equ 2
flock_start     .equ 4
flock_len       .equ 6
flock_pid       .equ 8

sizeof_flock    .equ 9

; Bitmask for the access mode.
; The access mode is in the first byte; other flags are in the second.
O_ACCMODE   .equ %111
; Access mode flags. These need not be bit-wise distinct, but are so that they
; can mirror the permission flags for files.
O_EXEC      .equ %001
O_RDONLY    .equ %100
O_WRONLY    .equ %010
O_SEARCH    .equ O_EXEC
O_RDWR      .equ O_RDONLY | O_WRONLY

; Flags for open which are stored in file descriptors. These, with the access
; mode flags, fit into a single byte
DEFINE_OR_MASK(O_APPEND,    3)
DEFINE_OR_MASK(O_NONBLOCK,  4)
DEFINE_OR_MASK(O_SYNC,      5)
; This is not a status flag, but is needed when creating a file description to
; be stored in the file descriptor in the FD_CLOEXEC bit. This is NOT updated
; to reflect changes in that bit or looked at after initialization.
DEFINE_OR_MASK(O_CLOEXEC,   6)

; Remaining flags for open(). There are in the second byte and are not stored in
; file descriptors (TODO Make sure this is okay.)
DEFINE_OR_MASK(O_CREAT,     8)
DEFINE_OR_MASK(O_DIRECTORY, 9)
DEFINE_OR_MASK(O_EXCL,      10)
DEFINE_OR_MASK(O_NOCTTY,    11)
DEFINE_OR_MASK(O_NOFOLLOW,  12)
DEFINE_OR_MASK(O_TRUNC,     13)
; This set as zero means it is an unavoidable default.
O_TTY_INIT .equ 0

#endif

