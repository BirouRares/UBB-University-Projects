bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dd 125
    b db 150
    c dw 15
    d db 20
    e dq 80

; our code starts here
segment code use32 class=code
    start:
        
        ;a+b/c-d*2-e
        ;b/c byte/word
        mov AL, [b]
        mov AH, 0
        mov DX, 0 ; AL-> DX:AX=b
        
        div word [c] ; AX=DX:AX/c=10   DX=DX:AX%c-d*2-ends
        
        ;d*2
        
        mov AL, 2
        mul byte [d] ; AX=d*AL=4
        
        ; b/c-d*e BX-AX
        sub BX,AX ; BX=b/c-d*2=6
        
        ;a+BX
        mov EAX, 0
        mov AX, BX ; EAX=b/c-d*e
        
        mov EBX, [a]
        add EBX, EAX ; EBX=a+b/c-d*2
        
        ;EBX- e(quad)
        ;EBX ->EDX:EBX
        mov EDX, 0
        
        ;EDX:EBX
        ;[e+4]:[e]
        
        sub EBX, [e]
        sub EDX, [e+4]  ; EDX:EBX=a+b/c-d*2-e
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
