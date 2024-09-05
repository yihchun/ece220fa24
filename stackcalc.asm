.ORIG x3000

; set up a stack
LEA R6, BOT_OF_STACK_MEMORY
ADD R6, R6, #1

LOOPTOP
GETC
LD R1, ZERO
ADD R0, R0, R1
BRzp HANDLE_DIGIT
JSR STACK_ADD
BRnzp LOOPTOP

HANDLE_DIGIT
JSR PUSH
BRnzp LOOPTOP

HALT

STACK_ADD
ST R7, SAVE_R7
JSR POP
ADD R1, R0, #0
JSR POP
ADD R0, R0, R1
JSR PUSH
LD R7, SAVE_R7
RET

SAVE_R7 .FILL #0
ZERO .FILL #-48

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