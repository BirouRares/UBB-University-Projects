;A character string S is given. Obtain the string D that contains all capital letters of the string S
bits 32 

global start        

extern exit, printf               
import exit msvcrt.dll    
import printf msvcrt.dll
                          

segment data use32 class=data
    s db 'a', 'A', 'b', 'B', '2', '%', 'x', 'M'
    l equ $-s
    d times l db 0
    
segment code use32 class=code
    start:
        ;A character string S is given. Obtain the string D that contains all capital letters of the string S
        mov ECX, l
        mov ESI,-1
        mov EDI,0
        jecxz endloop  ; if ECX=0
        repeta:
            inc ESI  ;ESI++
            mov AL, [s+ESI]  ; AL=s[ESI]
            cmp AL, "A"  ; compare character and "A"
            JB notcapitala  ;jump to notcapitala if input<A
            cmp AL, "Z"   ; compare character and "Z"
            JA notcapitalz  ; jump to notcapitalz if input>Z
            mov [d+EDI],AL  ; if AL is a capital letter we add it to d
            inc EDI  ; EDI++

            notcapitala:
            notcapitalz:
            ;inc ESI
        loop repeta
        endloop: ; the loop ends and we have the capital letters stored in d
        mov AX, 01Ah
        push    dword 0      
        call    [exit]       
