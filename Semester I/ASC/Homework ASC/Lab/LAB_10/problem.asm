bits 32 

global start        

extern exit, fopen, fread, fclose, printf
import exit msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll   
                          
segment data use32 class=data
    file_name db "file.txt", 0   ; filename to be read
    access_mode db "r", 0 
    file_descriptor dd -1
    len equ 100 
    text times (len+1) db 0 
    formatcif db "%d ", 0
    
    
segment code use32 class=code
    start:
    
        push dword access_mode     
        push dword file_name
        call [fopen]
        add esp, 4*2       ; clean-up the stack
        mov [file_descriptor], eax  ; store the file descriptor returned by fopen
        
        cmp eax, 0
        je final
        
        push dword [file_descriptor]
        push dword len
        push dword 1
        push dword text        
        call [fread]
        add esp, 4*4
        
        
        
        
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        
        final:
        push    dword 0      
        call    [exit]       
