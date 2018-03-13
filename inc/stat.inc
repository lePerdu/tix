;
; stat.inc
;
; Define constants from stat.h
;

#ifndef STAT_INC_
#define STAT_INC_

#include "fcntl.inc"

; Mask for file types
S_IFMT   .equ %1111000000000000
; File type values
S_IFBLK  .equ %1001000000000000
S_IFCHR  .equ %1010000000000000
S_IFIFO  .equ %1011000000000000
S_IFREG  .equ %1100000000000000
S_IFDIR  .equ %1101000000000000
S_IFLNK  .equ %1110000000000000
; Extra ones for the filesystem
; Inode file
S_INDFIL .equ %1111000000000000
; Deleted (a mask to reset the first bit)
S_IDEL   .equ %0111000000000000

; File permission bits
S_IXUSR .equ O_EXEC << 6
S_IRUSR .equ O_RDONLY << 6
S_IWUSR .equ O_WRONLY << 6
S_IRWXU .equ S_IRUSR | S_IWUSR | S_IXUSR
S_IXGRP .equ O_EXEC << 3
S_IRGRP .equ O_RDONLY << 3
S_IWGRP .equ O_WRONLY << 3
S_IRWXG .equ S_IRGRP | S_IWGRP | S_IXGRP
S_IXOTH .equ O_EXEC
S_IROTH .equ O_RDONLY
S_IWOTH .equ O_WRONLY
S_IRWXO .equ S_IROTH | S_IWOTH | S_IXOTH
S_ISUID .equ %0000100000000000
S_ISGID .equ %0000010000000000
S_ISVTX .equ %0000001000000000


;; Structure for returning data from *stat()
;   dev - ID of the device containing the file. (This is always 0 for now)
;   inode - Inode of the file
;   mode - File mode (type and permissions)
;   size - File size (only counting data, not the header)
;   uid - UID of the file owner
;   gid - GID of the file owner
;   nlink - Number of hard links to the file
;   ; atime,mtime,ctime - Access, modification, and status change times of the
;       file
;   rdev - Device ID (for character and block special files)
;   blksize - Filesystem block size (always 1 for now)
;   block - Number of blocks the file uses (the physical size of the file)
;
stat_dev    .equ 0
stat_inode  .equ 2
stat_mode   .equ 4
stat_size   .equ 6
stat_uid    .equ 8
stat_gid    .equ 9
stat_nlink  .equ 10
stat_rdev   .equ 11
stat_blksize    .equ 13
stat_blocks .equ 15

sizeof_stat .equ 17

#endif ; STAT_INC_

