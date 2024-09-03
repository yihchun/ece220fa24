.ORIG x3000

; set R6 one step below the bottom of stack memory
; (initialize the stack to be empty)
LEA R6, BOT_OF_STACK_MEMORY
ADD R6, R6, #1

; R1 -- pointer to the current location in the input stream
; R2 -- pointer to the current location in the output stream
LEA R1, INSTREAM
LEA R2, OUTSTREAM

TOPLOOP
	; push next character of instream
	LDR R0, R1, #0
	BRz NOMOREINPUT ; we don't have anything more to push, and the popping stopped last time for some reason, probably failed
	JSR PUSH

TOPINLOOP
	; do all the pops we need to do
	LDR R0, R6, #0	; peek at the top of the stack
	NOT R0, R0
	ADD R0, R0, #1
	LDR R3, R2, #0
	BRz NOMOREINPUT ; (no more output)
	ADD R0, R0, R3	; compares the peek with the next output element
	BRnp EXITINLOOP
	JSR POP		; same so we pop
	; the other way to handle running off the end of the stack,
	; rather than the R6 <= BOT_OF_STACK_MEMORY check, is to check
	; for failure here (R5 == 1) and immediately leave the inner loop
	; without OUT or incrementing R2. The slightly worse thing about
	; this approach is that it reads R6 when R6 points below stack memory
	; (which is safe in assembly)
	OUT
	ADD R2, R2, #1
	; continue iterating this loop if R6 <= BOT_OF_STACK_MEMORY
	LEA R5, BOT_OF_STACK_MEMORY
	NOT R5, R5
	ADD R5, R5, #1			; -BOT_OF_STACK_MEMORY in R5
	ADD R5, R5, R6			; R6-BOT_OF_STACK_MEMORY
	BRnz TOPINLOOP			; stack not empty

EXITINLOOP
	ADD R1, R1, #1
	BRnzp TOPLOOP

NOMOREINPUT
	HALT

INSTREAM .STRINGZ "ZYXWVUTSR"
OUTSTREAM .STRINGZ "YXVUWZSRT"

; if the stack is empty, set R5 to 1
; otherwise, set R5 to 0 and pop the top of the stack into R0
POP
LEA R5, BOT_OF_STACK_MEMORY
NOT R5, R5
ADD R5, R5, #1			; -BOT_OF_STACK_MEMORY in R5
ADD R5, R5, R6			; R6-BOT_OF_STACK_MEMORY
BRp POP_FAILED
AND R5, R5, #0			; R5 <- 0
LDR R0, R6, #0			; pop
ADD R6, R6, #1
POP_FAILED			; R5 is already 1, do nothing
RET

; if the stack is full, set R5 to 1
; otherwise, set R5 to 0 and push R0 onto the stack
PUSH
LEA R5, TOP_OF_STACK_MEMORY
NOT R5, R5
ADD R5, R5, #1			; -TOP_OF_STACK_MEMORY in R5
ADD R5, R5, R6			; R6-TOP_OF_STACK_MEMORY
BRz PUSH_FAILED
AND R5, R5, #0			; R5 <- 0
ADD R6, R6, #-1			; push
STR R0, R6, #0
RET
PUSH_FAILED
;AND R5, R5, #0			; R5 is already 0
ADD R5, R5, #1
RET

; stack memory is these 32 addresses
TOP_OF_STACK_MEMORY .BLKW #31
BOT_OF_STACK_MEMORY .FILL #0

.END