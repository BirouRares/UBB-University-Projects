bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ;a,b,c,d - word
    a dw 5
    b dw 10
    c dw 15
    d dw 20

; our code starts here
segment code use32 class=code
    start:
        ;(b+c+d)-(a+a)
        
        ;b+c
        mov AX, [b]
        add AX, [c]
        
        ;(b+c+d)
        add AX, [d]
        
        ; a+a
        mov BX, [a]
        add BX, [a]
        
        ;(b+c+d)-(a+a)
        sub AX, BX
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
