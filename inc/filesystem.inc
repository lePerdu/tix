;
; filesystem.inc
;

#ifndef FILESYSTEM_INC_
#define FILESYSTEM_INC_

;; The starting and ending pages reserved for the filesystem.
; The filesystem takes up all but the first erase block and the last 2 (reserved
; for system calls, certificates, and boot code).
FS_PAGE_START   .equ $04
; TODO This should be version-dependant.
FS_PAGE_END     .equ $6B

;; The total size of the filesystem.
FS_SIZE         .equ (FS_PAGE_END - FS_PAGE_START) * FLASH_PAGE_SIZE

;; Offsets for the inode type.
;   16  mode/type (the MSB is reset if the inode should be deleted; the second
;                  MSB is set for the inode file)
;   16  size (TODO Put this first as it is the most commonly accessed. Have to
;             be really careful to change all uses)
;   [
;   32  ctime
;   32  mtime
;   32  atime
;   ]
;   8   uid
;   8   gid
;   8   nlinks
;   *   data
;
inode_mode   .equ 0
inode_size   .equ 2
inode_uid    .equ 4
inode_gid    .equ 5
inode_nlinks .equ 6
inode_data   .equ 7

;; The size of an inode (not including file data).
sizeof_inode .equ 7

;; Offsets for entries in the inode file.
;   16  ident (the inode identifier number)
;   8   page
;   16  offset
;
inode_entry_ident   .equ 0
inode_entry_page    .equ inode_entry_ident + 2
inode_entry_offset  .equ inode_entry_page  + 1

sizeof_inode_entry  .equ 5

;; Offsets for direntory entries.
;   16  inode
;   8   name[14]
;
fs_direntry_inode .equ 0
fs_direntry_name  .equ 2

sizeof_fs_direntry .equ 16

;; Inode of the root directory.
FS_ROOT .equ 1

#endif

