bits 32 

global start        

extern exit,scanf,printf,fopen,fclose,fprintf,fread               
import exit msvcrt.dll  
import printf msvcrt.dll
import scanf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
import fread msvcrt.dll
  
                          
segment data use32 class=data
    file_name1 db "ana.txt",0
    file_name2 db "result.txt",0
    
    access_mode1 db "r",0
    file_descriptor dd -1
    file_descriptor2 dd -1
    
    formatcar db "%s",0
    format_charater db "%c",0
    formatcif db "%d",0
    
    access_mode2 db "w",0
    text resb 2000
    
    aux db 0
    
    
segment code use32 class=code
    start:
        
        push dword access_mode1
        push dword file_name1
        call [fopen]
        add ESP,4*2
        
        mov [file_descriptor],EAX
        
        cmp EAX,0
        je finala
        
        push dword access_mode2
        push dword file_name2
        call [fopen]
        add ESP, 4*2
        
        mov [file_descriptor2],EAX
        cmp EAX,0
        je finala
        
        my_loop:
            mov DL, 0x00; this is null element 
        
            push dword [file_descriptor]
            push dword 100
            push dword 1
            push dword text
            call [fread]
            add ESP, 4*4
            
            cmp EAX, 0 
            je cleanup 
            
            mov [text+EAX+1],DL
            
            ;pushad
            ;push dword text
            ;push dword formatcar
            ;call [printf]
            ;add esp, 4*2
            ;popad
            
            mov ESI, text
            cld
            mov ECX,EAX
            repeta:
                lodsb
                
                cmp AL, "A"
                jb not_capital
                cmp AL, "Z"
                ja not_capital
                
                mov [aux],AL
                
                pushad
                push dword [aux]
                push dword format_charater
                push dword [file_descriptor2]
                call [fprintf]
                add ESP,4*3
                popad
                
                not_capital:
                    
                    
                    cmp AL, "a"
                    jb capital
                    cmp AL, "z"
                    ja capital
                    
                    mov [aux],AL
                
                    pushad
                    push dword [aux]
                    push dword formatcif
                    push dword [file_descriptor2]
                    call [fprintf]
                    add ESP,4*3
                    popad
                
                capital:
            loop repeta
            
            
        jmp my_loop
        cleanup:
        
        push dword [file_descriptor]
        call [fclose]
        add esp,4
        
        push dword [file_descriptor2]
        call [fclose]
        add esp,4
        
        finala:
        push    dword 0      
        call    [exit]       
