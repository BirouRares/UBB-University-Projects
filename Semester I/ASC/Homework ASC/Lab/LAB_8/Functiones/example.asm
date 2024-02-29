bits 32

global start        

extern exit              
import exit msvcrt.dll
    
                         
segment code use32 class=code
    start:
        
        
        push    dword 0    
        call    [exit]       