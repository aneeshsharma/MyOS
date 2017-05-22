; The Starting of the Kernel Code
; Author - Anish Sharma

[bits 32]
[extern main]

global _start
_start:
    call main

jmp $