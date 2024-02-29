bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    s1 db 1,2,3,4,5,6,7
    lens1 equ $-s1
    s2 times lens1 dw 0  ; add digit 7 at each number in s1
    two db 2
    sum db 0
    ten db 10
    
segment code use32 class=code
    start:
        ;construct s2 by adding digit 7 at the end of each element in s1
        mov ECX, lens1
        mov ESI, 0
        mov EDI, 0
        jecxz ends2l
        s2loop:
            mov AL, [s1+ESI]
            mul byte [ten] ; AX=AL*10
            add AX,7 ; AX=AL*10+7
            mov [s2+EDI], AX
            inc ESI
            inc EDI
            inc EDI  ; as s2 in a dword
        loop s2loop
        ends2l:
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
