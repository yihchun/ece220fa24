.ORIG x3000

LEA R4, GLOBAL
LEA R6, STACK_START
JSR FIB
HALT

FIB
	; callee setup
	ADD R6, R6, #-4 ; local variables + bookkeeping(3)
	STR R5, R6, #1  ; 1 is the number of local variables
	STR R7, R6, #2  ; 1 (space for R5) + local variables
	ADD R5, R6, #0  ; Local variables - 1, so R5 points to bottom of LVs

	; ct++
	LDR R0, R4, #0
	ADD R0, R0, #1
	STR R0, R4, #0

	; if (n <= 1) return n
	; for convenience, assume n is less than 2^15
	LDR R0, R5, #4	   ; n
	ADD R1, R0, #-1	   ; n-1
	BRnz RETURN_R0

	; tmp = fib(n-1)
	; push n-1
	ADD R6, R6, #-1
	STR R1, R6, #0		; kinda optimized
	JSR FIB
	LDR R0, R6, #0		; get the return value
	ADD R6, R6, #2		; restore stack to look like it did before the call
	STR R0, R5, #0		; tmp = return value

	; return tmp + fib(n-2)
	; evaluate fib(n-2)
	LDR R0, R5, #4
	ADD R0, R0, #-2		; calculate n-2
	ADD R6, R6, #-1
	STR R0, R6, #0		; push n-2
	JSR FIB
	LDR R0, R6, #0		; get the return value
	ADD R6, R6, #2		; restore stack to look like it did before the call
	; add tmp
	LDR R1, R5, #0
	ADD R0, R0, R1		; R0 <- tmp+fib(n-2)

RETURN_R0
	STR R0, R5, #3		; store R0 at the return value location

	; callee teardown
	LDR R7, R5, #2
	LDR R5, R5, #1
	ADD R6, R6, #3
	RET

; Symbol Table
; scope	 name	baseptr	offset
; fib	 ct	R4	0
; fib	 n	R5	4
; fib	 tmp	R5	0


GLOBAL .FILL #0 ; fib:ct
.BLKW #128   	; runtime stack
STACK_START .FILL #8


.END
	