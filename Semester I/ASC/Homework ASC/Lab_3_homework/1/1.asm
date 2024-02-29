bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ;a - byte, b - word, c - double word, d - qword - Unsigned representation
    a db 20
    b dw 300
    c dd 4
    d dq 100

    
segment code use32 class=code
    start:
        ;(a+b-d)+(a-b-d)
    
        ;a+b
        mov AL, [a]
        cbw ;AL-> AX
        add AX, [b] 
        
        ;a+b-d
        cwd
        cdq
        sub EAX, [d]
        mov EBX, EAX
        
        ;a-b-d
        mov AL, [a]
        cbw
        sub AX, [b]
        cwd
        cdq 
        sub EAX, [d]
        
        ;(a+b-d)+(a-b-d)
        add EBX, EAX
        
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
