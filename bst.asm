.ORIG x3000

LEA R6, STACK_END
ADD R6, R6, #-2
LEA R0, ROOT
STR R0, R6, #0
LEA R1, STUFF
LDR R1, R1, #0
STR R1, R6, #1
JSR TREE_INSERT

ADD R6, R6, #1
LEA R1, STUFF
LDR R1, R1, #1
STR R1, R6, #1
JSR TREE_INSERT

ADD R6, R6, #1
LEA R1, STUFF
LDR R1, R1, #2
STR R1, R6, #1
JSR TREE_INSERT

ADD R6, R6, #1
LEA R1, STUFF
LDR R1, R1, #3
STR R1, R6, #1
JSR TREE_INSERT

HALT

TREE_INSERT
	; callee setup
	ADD R6, R6, #-3
	STR R5, R6, #0
	STR R7, R6, #1
	ADD R5, R6, #-1

	; if (*root == NULL)
	LDR R0, R5, #4        ; R0 <- root
	LDR R1, R0, #0        ; R1 <- *root
	BRnp INSERT_ROOT_NOT_NULL

	; *root = malloc(sizeof(treeNode))
	ADD R6, R6, #-1		; caller setup for malloc: push 3
	ADD R1, R1, #3
	STR R1, R6, #0
	
	JSR MALLOC

	; caller teardown for malloc
	LDR R1, R6, #0	      ; R1 <- malloc(3)
	ADD R6, R6, #2	      ; stack is back to pre-call
	STR R1, R0, #0

	; (*root)->val = v
	LDR R2, R5, #5
	STR R2, R1, #0

	; (*root)->left = NULL
	AND R2, R2, #0
	STR R2, R1, #1
	STR R2, R1, #2        ; (*root)->right = NULL

	BRnzp INSERT_RETURN

INSERT_ROOT_NOT_NULL
	; r1 is *root entering this code
	; if ((*root)->val == v) return
	LDR R2, R1, #0
	LDR R3, R5, #5  ; v
	NOT R0, R3
	ADD R0, R0, #1
	ADD R2, R2, R0  ; (*root)->val - v
	BRz INSERT_RETURN
	
	BRp #1
	ADD R1, R1, #1
	ADD R1, R1, #1
	; caller setup for TREE_INSERT
	ADD R6, R6, #-2
	STR R3, R6, #1
	STR R1, R6, #0
	JSR TREE_INSERT
	ADD R6, R6, #3 ; caller teardown for TREE_INSERT

INSERT_RETURN
	; callee teardown
	LDR R7, R5, #2
	LDR R5, R5, #1
	ADD R6, R6, #2
	RET

;         <- R5
; R5-save <- R6  (R5+1)
; R7-save        (R5+2)
; ret val        (R5+3)
; root           (R5+4)
; v              (R5+5)


MALLOC
	ADD R6, R6, #-2 ; save R0, R1
	STR R0, R6, #0
	STR R1, R6, #1
	; load the old free pointer, which we will return
	LD R0, MALLOC_FREEPTR
	; calculate the new freepointer, and store it
	LDR R1, R6, #2
	ADD R1, R1, R0
	ST R1, MALLOC_FREEPTR
	; we're done with r1, restore it
	LDR R1, R6, #1
	; the spot that r1-save is the spot for the return value
	STR R0, R6, #1
	; restore R0
	LDR R0, R6, #0
	; pop 1 spot off the stack (because we pushed 2)
	ADD R6, R6, #1
	RET

ROOT .FILL #0
STUFF .FILL #5
      .FILL #3
      .FILL #7
      .FILL #4

STACK .BLKW #50
STACK_END .FILL #0
MALLOC_FREEPTR   .FILL MALLOC_ALLOCATES
MALLOC_ALLOCATES .FILL #0
.END