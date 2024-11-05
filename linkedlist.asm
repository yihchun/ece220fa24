.ORIG x3000

LEA R6, STACK_BOT
JSR LLINSERT_HEAD
HALT

LLLENGTH_R
	; callee setup
	ADD R6, R6, #-3 ; rv, r7, r5
	STR R5, R6, #0
	STR R7, R6, #1
	ADD R5, R6, #-1

	; if (!head) return 0;
	LDR R0, R5, #4
	BRz LEN_RETURN_R0

	LDR R0, R0, #1		; R0 <- head->next
	; caller setup
	ADD R6, R6, #-1
	STR R0, R6, #0		; push R0
	JSR LLLENGTH_R	    ; llength(head->next)
	; caller teardown
	LDR R0, R6, #0		; R0 <- ret val
	ADD R0, R0, #1		; 1+llength_r(...)
	ADD R6, R6, #2		; pop rv, head->n

LEN_RETURN_R0
	STR R0, R5, #3
	; callee teardown
	LDR R7, R5, #2
	LDR R5, R5, #1
	ADD R6, R6, #2
	RET

; === stack frame
; 		<- R5
; link		<- R6
; saved ra
; return value
; head
; === symbol table
; head R5 +4

LLINSERT_HEAD
	; callee setup
	ADD R6, R6, #-4
	STR R5, R6, #1
	ADD R5, R6, #0
	STR R7, R5, #2

	; tmp = malloc(sizeof(llnode))
	; bad implementation
	LEA R0, ALLOC_ELT
	STR R0, R5, #0

	; tmp->val = val
	LDR R1, R5, #5		; val
	STR R1, R0, #0		; tmp->val = val

	; tmp->next = *head
	LDR R2, R5, #4		; head
	LDR R2, R2, #0		; *head
	STR R2, R0, #1		; tmp->n = *head

	; *head = tmp
	LDR R2, R5, #4		; head
	STR R0, R2, #0		; *head = tmp

	; callee teardown
	LDR R7, R5, #2
	LDR R5, R5, #1
	ADD R6, R6, #3
	RET


; === stack frame
; tmp 	    <- R6, R5	R5+0
; link
; ra
; rv
; head			R5+4
; val			R5+5

HEADPTR    .FILL HEAD
HEAD       .FILL #5
           .FILL SECOND_ELT
SECOND_ELT .FILL #8
	   .FILL #0
ALLOC_ELT  .BLKW #2

STACK .BLKW #128
STACK_BOT .FILL HEADPTR
.FILL #3

.END