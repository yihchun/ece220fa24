.ORIG x3000

; Register allocation
; R0- current character
; R1- pointer to the current character in the input string

; set up a stack
LEA R6, BOT_OF_STACK_MEMORY
ADD R6, R6, #1

; iterate across each character in the string
LEA R1, INPUT_STRING
LOOPTOP
LDR R0, R1, #0
BRz LOOPBOT

; if the character is open, push a representation
LEA R2, OPEN_CHARACTERS
AND R3, R3, #0
OPENLOOP
; load the next open character into R4
LDR R4, R2, #0
BRz NOTOPEN
ADD R4, R4, R0
BRz DOPUSH
ADD R2, R2, #1
ADD R3, R3, #1
BRnzp OPENLOOP

DOPUSH
; right now, R0 is an open
; transform it into the matching close
LEA R2, CLOSE_CHARACTERS
ADD R2, R2, R3
LDR R0, R2, #0
JSR PUSH
; R0 has been overwritten, but not to anything that will affect the later code

NOTOPEN
LEA R2, CLOSE_CHARACTERS
; check to see if this character is a close character
CLOSELOOP
LDR R4, R2, #0
BRz NOTCLOSE
ADD R4, R4, R0
BRz ISCLOSE
ADD R2, R2, #1
BRnzp CLOSELOOP

; it's a close character so it must match the top of the stack
; (which also needs to be nonempty)
ISCLOSE
JSR POP
ADD R5, R5, #0
BRp FAIL ; empty stack
; at this point, our representation (negative close) is in R0
; the close parenthesis that it is supposed to match is at M[R1]
LDR R2, R1, #0
ADD R2, R0, R2
; if it doesn't match, FAIL
BRnp FAIL

; else continue the loop

NOTCLOSE
ADD R1, R1, #1
BRnzp LOOPTOP

LOOPBOT

; outside the loop
; if the stack is empty, succeed
JSR POP
ADD R5, R5, #0
BRz FAIL
LEA R0, SUCCMSG
PUTS
HALT

; else fail
FAIL
LEA R0, FAILMSG
PUTS
HALT

SUCCMSG .STRINGZ "Your string seems fine to me."
FAILMSG .STRINGZ "Your string has unmatched parentheses. You fail."

OPEN_CHARACTERS
.FILL #-40  ; (
.FILL #-91  ; [
.FILL #-123 ; {
.FILL #0
CLOSE_CHARACTERS
.FILL #-41  ; )
.FILL #-93  ; ]
.FILL #-125 ; }
.FILL #0

INPUT_STRING .STRINGZ ")([{}( ) ])"

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