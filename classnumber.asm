.ORIG x3000

LEA R6, STACK_BOT
; we need to call p->classno()
LD R0, P       ; this is the pointer to the Base on which we call classno()
LDR R1, R0, #0 ; VFT for Base or derived class
LDR R2, R1, #0 ; classno() function we want to call
ADD R6, R6, #-1 ; push p onto the stack
STR R0, R6, #0 
JSRR R2
HALT

BASE_CLASSNO
	ADD R6, R6, #-1
	AND R0, R0, #0
	STR R0, R6, #0
	RET

A_CLASSNO
	ADD R6, R6, #-1
	AND R0, R0, #0
	ADD R0, R0, #1
	STR R0, R6, #0
	RET

BASE_VFT .FILL x3008 ; BASE_CLASSNO
A_VFT    .FILL x300C ; A_CLASSNO

X .FILL x3012 ; A_VFT
P .FILL x3013 ; X

.BLKW #10
STACK_BOT .FILL #0


.END