bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ;a,b,c,d - byte
    a db 10
    b db 20
    d db 15

; our code starts here
segment code use32 class=code
    start:
        ;(a+b-d)+(a-b-d)
        
        ;a+b
        mov AL, [a]
        add AL, [b]
        
        ;(a+b-d)
        sub AL, [d]
        
        ;a-b
        mov AH, [a]
        sub AH, [b]
        
        ;(a-b-d)
        sub AH, [d]
        
        ;(a+b-d)+(a-b-d)
        add Ah, Al
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
