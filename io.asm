.ORIG x3000

WAIT_KEY_READY
; do work

; take a character input, put it in R0
; check the ready bit of KBSR
LD R0, KBSR     ; PC+offset
LDR R0, R0, #0  ; BaseR+offset
; shorthand for last two instructions: LDI R0, KBSR ; PC+offset, go to memory 2x
; character not ready yet
BRzp WAIT_KEY_READY

LDI R0, KBDR
LD R1, KEYMASK
AND R0, R0, R1

; take R0 and write it to the display
; check the DSR
LD R1, DSR     ; PC+offset
LDR R1, R1, #0  ; BaseR+offset
BRzp #-3

; display is now ready
STI R0, DDR
BRnzp WAIT_KEY_READY
HALT

KBSR .FILL xFE00
KBDR .FILL xFE02
DSR .FILL xFE04
DDR .FILL xFE06
KEYMASK .FILL x00FF
.END