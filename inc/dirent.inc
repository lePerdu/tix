;
; dirent.inc
;
; Directory stream defines
;

#ifndef DIRENT_INC_
#define DIRENT_INC_

#include "fcntl.inc"

;; Structure for storing a directory entry.
; inode - Inode of the entry.
; name - Name of the entry. This is NAME_MAX+1 bytes in length, unlike
; tix_dir_entry, because it needs a null byte.
;
dirent_inode    .equ 0
dirent_name     .equ 2

sizeof_dirent   .equ 17


;; Structure for storing a directory stream.
; TODO Do this? :
; The inode of the last returned entry is used to determine the offset in the
; directory instead of a raw offset so that entries added or removed between
; calls to readdir() will not mess up the offset and result in missing or
; repeating an entry. If the current entry is removed before the next call to
; readdir(), it will return with error ENOENT, as the offset is invalid.
;
; inode - Inode of the directory.
; offset - Index into the directory.
; dirent - Space to read directory entries into and return to return pointers
;   to.
;
DIR_inode   .equ 0
DIR_offset  .equ 2
DIR_dirent  .equ 4

sizeof_DIR  .equ 4 + sizeof_dirent

#endif ; DIRENT_INC_

