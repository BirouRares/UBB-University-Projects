;A natural number a (a: dword, defined in the data segment) is given. Read a natural number b from the keyboard and calculate: a + a/b. Display the result of this operation. The values will be displayed in decimal format (base 10) with sign.

bits 32 

global start        

extern exit, printf, scanf               
import exit msvcrt.dll  
import printf msvcrt.dll
import scanf msvcrt.dll  
                          
segment data use32 class=data
    a dd -40
    b dw 0
    d dd 0
    messager  db "For a+a/b, b=", 0
    messagep  db "a+a/b=%d", 0
    format  db "%d", 0
    
segment code use32 class=code
    start:
        ;reading the natural number b
        push messager 
        call [printf]
        add ESP, 4
        push dword b
        push dword format
        call [scanf]
        add ESP, 4*2
        ;a/b
        mov AX, word [a]
        mov DX, word [a+2]
        mov BX, [b]
        idiv BX
        ;AX=a/b
        cwde
        ;EAX=AX=a/b
        add EAX, [a]
        ;EAX=a+a/b
        mov [d],EAX
        ;d=a+a/b
        
        ;printing the result
        push dword [d]
        push dword messagep
        call [printf]
        add ESP, 4*2
        
        push    dword 0      
        call    [exit]       
