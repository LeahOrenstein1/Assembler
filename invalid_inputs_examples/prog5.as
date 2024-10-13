;Editor- Lior Dvora
;Details- Errors during first and second passes.
;Output file- am

macr printNum
prn #48
prn #49
prn #50
endmacr

MAIN: mov r3, LENGTH
LOOP: jmp L1
printNum
macr m1
sub r1, r4
bne END
endmacr
m1
L1: inc K
dec r7
bne LOOP
;Error: undefined label
mov r5, nonexistentLabel  
;Error: immediate value out of range
cmp r2, #1111111
.entry MAIN
.extern EXIT
;Error: invalid instruction (should be 'stop')
END: stp  
;Error: integer out of range
LENGTH: .data 6,-9,15,30013837
;Error:
    .data 6,-9,15.6,300
;Error: invalid data (non-numeric)
K: .data abc
;Error: missing quoted string
    .string
;Error: missing "
STR: .string "
;Error: missing "
STR: .string "abc
;Error: missing "
STR: .string abc"
STR: .string "" 
;Error: out of range
.data 100, 200, , 111111111111111
