
.ORIG x3000

LD R6, STACK_BOTTOM

LD R0, PARAM1
ADD R6, R6, #-1
STR R0, R6, #0
JSR FACT
HALT

PARAM1 .FILL #5
PARAM2 .FILL #3

FACT
	ADD R6, R6, #-4 ; -(3+LV)
	STR R5, R6, #1  ; (LV)
	ADD R5, R6, #0  ; LV-1
	STR R7, R5, #2

	; total = 1
	AND R0, R0, #0
	ADD R0, R0, #1
	STR R0, R5, #0

	; while n > 0
FACT_LOOP_TOP
	LDR R0, R5, #4
	BRz FACT_LOOP_EXIT

	; total = multiply(n, total)
	;;; caller setup
	ADD R6, R6, #-2 ; -(params)
	STR R0, R6, #0
	LDR R0, R5, #0
	STR R0, R6, #1
	JSR MULTIPLY
	;;; caller teardown
	LDR R0, R6, #0
	ADD R6, R6, #3	; params+1

	STR R0, R5, #0 ;  total = multiply(n, total)

	; n--
	LDR R0, R5, #4
	ADD R0, R0, #-1
	STR R0, R5, #4
	
	BRnzp FACT_LOOP_TOP
	
FACT_LOOP_EXIT
	; return total
	LDR R0, R5, #0
	STR R0, R5, #3

	LDR R7, R5, #2
	LDR R5, R5, #1
	ADD R6, R6, #3 ; LV+2
	RET

MULTIPLY
	ADD R6, R6, #-5 ; -(3+LV)
	STR R5, R6, #2  ; (LV)
	ADD R5, R6, #1  ; LV-1
	STR R7, R5, #2
	
	; accum = 0
	AND R0, R0, #0
	STR R0, R5, #-1

	; i = 1
	AND R1, R1, #0
	ADD R1, R1, #1
	STR R1, R5, #0

MULTIPLY_LOOP_TOP
	; check if i is nonzero
	LDR R1, R5, #0
	BRz MULTIPLY_LOOP_EXIT

	; if (a & i)
	LDR R0, R5, #5
	AND R0, R1, R0
	BRz DONT_ADD
	
	; accum += b
	LDR R0, R5, #-1
	LDR R1, R5, #4
	ADD R0, R0, R1
	STR R0, R5, #-1

DONT_ADD
	; b <<= 1
	LDR R0, R5, #4
	ADD R0, R0, R0
	STR R0, R5, #4

	; i <<= 1
	LDR R0, R5, #0
	ADD R0, R0, R0
	STR R0, R5, #0

	BRnzp MULTIPLY_LOOP_TOP

MULTIPLY_LOOP_EXIT
	; return accum
	LDR R0, R5, #-1
	STR R0, R5, #3

	LDR R7, R5, #2
	LDR R5, R5, #1
	ADD R6, R6, #4 ; LV+2
	RET

STACK_BOTTOM .FILL x4000

.END
