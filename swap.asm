.ORIG x3000

LD R6, STACK_START
ADD R6, R6, #-1
LEA R0, VAR_A
STR R0, R6, #0
ADD R6, R6, #-1
LEA R0, VAR_B
STR R0, R6, #0
JSR SWAP
HALT

VAR_A .FILL #1
VAR_B .FILL #2
STACK_START .FILL x4000

SWAP
  ADD R6, R6, #-4
  STR R5, R6, #1
  ADD R5, R6, #0
  STR R7, R5, #2

  LDR R0, R5, #4  ; tmp = *a
  LDR R0, R0, #0  ; *a
  STR R0, R5, #0

  LDR R0, R5, #5  ; *a = *b
  LDR R0, R0, #0  ; *b
  LDR R1, R5, #4
  STR R0, R1, #0  ; *a = *b

  LDR R0, R5, #0  ; *b = tmp
  LDR R1, R5, #5
  STR R0, R1, #0

  LDR R7, R5, #2
  LDR R5, R5, #1
  ADD R6, R6, #3
  RET


.END