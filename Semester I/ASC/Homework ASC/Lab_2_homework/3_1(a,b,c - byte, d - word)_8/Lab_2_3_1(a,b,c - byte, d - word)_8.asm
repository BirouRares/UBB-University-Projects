bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; a,b,c - byte, d - word
    a db 5
    b db 2
    c db 10
    d dw 20

; our code starts here
segment code use32 class=code
    start:
        ; (100*a+d+5-75*b)/(c-5)
        
        ;100*a=500
        mov AL, [a]  ;AL=5
        mov AH, 100 ;AH=100
        mul AH  ;AH*Al=AX
    
        ;100*a+d =520
        add AX, [d] ;AX=520
        
        ;100*a+d+5=525
        add AX, 5 ;AX=525
        
        ;75*b=150
        mov BX, AX ;BX=AX=525, we store the result until now in BX
        
        mov AL, [b] ; AL=2
        mov AH, 75; AH=75
        mul AH  ;AH*Al=AX  AX=150
        
        ;100*a+d+5-75*b=375
        sub BX,AX ;BX=525-150=375
        
        ;c-5=5
        mov CL, [c]  ; CL=10
        sub CL, 5 ;  CL=10-5=5
        
        ; (100*a+d+5-75*b)/(c-5)=75
        mov AX, BX  
        div CL      ;AL=(100*a+d+5-75*b)/(c-5)=75      AH=(100*a+d+5-75*b)%(c-5) =0
        
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
