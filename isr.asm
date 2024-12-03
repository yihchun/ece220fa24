.ORIG x3000

; write a program that echos everything that the user inputs
; at the keyboard to the display.
; also, the body of the program should be BRnzp #-1

; Load the ISR into KB_INTV
LEA R0, KB_ISR
STI R0, KB_INTV

; Load INTERRUPT_ENABLE into KBSR
LD R0, KBSR
LD R1, INTERRUPT_ENABLE
STR R1, R0, #0

BRnzp #-1

KB_ISR
   ; R6 points to the supervisor stack
   ADD R6, R6, #-1
   STR R0, R6, #0
   ADD R6, R6, #-1
   STR R1, R6, #0

   LDI R0, KBDR
   LDI R1, DSR
   BRzp #-2
   STI R0, DDR
   
   LDR R1, R6, #0
   ADD R6, R6, #1
   LDR R0, R6, #0
   ADD R6, R6, #1
   RTI

KBSR .FILL xFE00
KBDR .FILL xFE02
DSR .FILL xFE04
DDR .FILL xFE06
INTERRUPT_ENABLE .FILL x4000
KB_INTV .FILL x0180

.END