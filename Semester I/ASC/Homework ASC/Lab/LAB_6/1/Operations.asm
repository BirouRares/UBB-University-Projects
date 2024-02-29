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
    
    sum db 0
    
segment code use32 class=code
    start:
        ;sum of numbers (bytes) in s1
        
        mov BL, 0
        mov ECX, lens1  ; number of repetition of the loop
        mov ESI,0 ; ESI- index
        jecxz endloop  ; if ECX=0
        repeta:
            mov AL,[s1+ESI]  ; AL=s1[ESI]
            add BL, AL  ; sum
            inc ESI  ;ESI++
            
        loop repeta   ; decrement ECX  ; Jump (jnz) to repete
        endloop:
        
        mov [sum], BL
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
