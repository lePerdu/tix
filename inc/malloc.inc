;
; malloc.inc
;
; Defines for the allocator.
;

#ifndef MALLOC_INC_
#define MALLOC_INC_

;; Structure for location allocation nodes.
;   16  size - Size of the allocation, including the node header. The MSB of
;       this is set if the node is empty (so the size is effectively 15 bits).
;       Set to 0 if at the tail.
;   16  psize - Copy of the size field from the previous node. This includes the
;       empty flag for it. Set to 0 if at the head.
;
lalloc_node_size    .equ 0
lalloc_node_psize   .equ 2

sizeof_lalloc_node  .equ 4

;; Structure for global allocation nodes.
;   32  lalloc_node - size and psize fields from lalloc_node.
;   8   refs - Number of references to the node.
;
galloc_node_size    .equ 0
galloc_node_psize   .equ 2
galloc_node_refs    .equ 4

sizeof_galloc_node  .equ 5

DEFINE_OR_MASK(ALLOC_NODE_EMPTY, 7)

#endif

