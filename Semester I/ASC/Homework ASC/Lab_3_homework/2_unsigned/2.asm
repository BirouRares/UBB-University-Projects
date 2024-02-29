bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ;a,b-word; c,d-byte; e-doubleword; x-qword
    a dw 2
    b dw 10
    c db 10
    d db 4
    e dd 150
    x dq 310

segment code use32 class=code
    start:
        ;1/a + 200*b -c / (d+1) + x / a - e
        ;unsigned
        
        
        ;1/a
        mov DX, 0 ;DX=0
        mov AX, 1 ;AX=1
        div word[a] ;AX=1/a    DX=1%a
        mov BX,AX ;BX=AX=0
        
        ;200*b
        mov DX,200 ;DX=200
        mov AX, [b] ;AX=b=10
        mul DX ;DX:AX=2000
        
        ;1/a + 200*b
        add BX,AX ;BX=2000
        
        ;c / (d+1)
        mov AH, 0
        mov AL, [c] ;AL=10  , AX=10
        mov CL, [d] ;CL=4
        add CL, 1 ;CL=5
        div CL  ; AL=c/(d+1)=2   AH=c % (d+1)=0
        
        ;1/a + 200*b -c / (d+1)
        mov AH,0 ;AH=0
        sub BX, AX ;BX=1998
        
        ;x / a
        mov AX, [a] ;AX=a=2
        mov DX, 0 ;DX:AX=a=2
        push DX
        push AX
        pop ECX ;ECX=2
        
        mov EAX, dword [x] 
        mov EDX, dword [x+4]; EDX:EAX=x=310
        
        div ECX ; EAX=EDX:EAX/ECX=155  EDX=EDX:EAX%ECX=0
        
        ;1/a + 200*b -c / (d+1) + x / a
        mov CX, BX ;CX=BX=1988
        mov BX, 0
        push BX
        push CX
        pop ECX
        add EAX,ECX  ; EAX=EAX+ECX=1998+155=2153
        
        ;1/a + 200*b -c / (d+1) + x / a - e
        sub EAX, [e] ;EAX=2153-150=2003
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
