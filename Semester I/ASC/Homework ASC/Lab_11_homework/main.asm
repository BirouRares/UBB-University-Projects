;Show for each number from 32 to 126 the value of the number (in base 8) and the character with that ASCII code.
bits 32 
global start        

extern exit, printf, scanf               
import exit msvcrt.dll    
import printf msvcrt.dll
import scanf msvcrt.dll

extern operations
                          
segment data use32 class=data
    a dd 0
    formatcar db "The character with this ASCII code is --> %c",10,13,10,13,0
    formatoct db "The number in base 8 is --> %o",10,13,0
    formatdec db "The number in base 10 is --> %d",10,13,0
segment code use32 public code
    start:
        mov EAX, 32
        
        myloop:
            mov [a], EAX
            
            pushad;print the number in base 8
            push dword [a]
            push dword formatoct
            call [printf]
            add ESP, 4*2
            popad
            
            pushad; print the character with the ascii code
            push dword [a]
            push dword formatcar
            call [printf]
            add ESP, 4*2
            popad
            
            push dword EAX  ;EAX is a int value and it is the parameter for the function operations(int n)
            call operations  ; call my function
            
            jnae myloop; loop while eax<127
        
        
        push    dword 0      
        call    [exit]       
