;   Given the words A and B, compute the byte C as follows:
;the bits 0-5 are the same as the bits 5-10 of A
;the bits 6-7 are the same as the bits 1-2 of B.
;   Compute the doubleword D as follows:
;the bits 8-15 are the same as the bits of C
;the bits 0-7 are the same as the bits 8-15 of B
;the bits 24-31 are the same as the bits 0-7 of A
;the bits 16-23 are the same as the bits 8-15 of A

bits 32

global start        

extern exit               
import exit msvcrt.dll    

segment data use32 class=data
    a dw 0101010101010101b
    b dw 0010101010101010b
    c db 0
    d dd 0

segment code use32 class=code
    start:
        
        ;Given the words A and B, compute the byte C as follows:
        ;the bits 0-5 are the same as the bits 5-10 of A
        
        mov BX, 0; store the result in BX
        mov AX, word [a] ;AX= 0101010101010101b         we isolate bits 5-10 of A
        and AX, 0000011111100000b   ; AX=0000010101000000b=1344
        mov CL,5
        ror AX, CL ; rotate right 5 bits => AX=00000000000101010b=42
        or BX,AX  ; BX=AX=00000000000101010b=42
        mov BH, 0 ; BL=00101010=42
        
        ;the bits 6-7 are the same as the bits 1-2 of B.
        
        mov AX, word [b] ;AX=0010101010101010b=10922     we isolate bits 1-2 of B
        and AX, 0000000000000110b ;AX=0000000000000010b=2
        mov CL, 5
        rol AX,CL  ; rotate left 5 bits => AX=0000000001000000b=64
        or BX, AX  ; BX=0000000001101010b=106
        mov BH, 0 ; BL=01101010b=106 
        mov byte [c], BL ; c=01101010b = 106 => final result
        mov BX,0 ;reset BX
        
        ;Compute the doubleword D as follows:
        ;the bits 8-15 are the same as the bits of C
        
        mov EBX,0  ;store the result in EBX
        mov EAX,0  ;reset EAX
        mov AH, byte [c] ; AX=01101010 00000000b=27136
        or EBX, EAX; EBX=00000000 00000000 01101010 00000000b=27136
        mov EAX,0  ;reset EAX
        
        ;the bits 0-7 are the same as the bits 8-15 of B
        
        mov AX, word [b] ;AX=00101010 10101010b=10922    we isolate bits 8-15 of B
        and AX, 1111111100000000b  ; AX=00101010 00000000b= 10752
        mov CL, 8
        ror EAX, CL ; rotate right 8 bits => EAX=00000000 00000000 00000000 00101010b=42
        or EBX, EAX ; EBX=00000000 00000000 01101010 00101010b = 27178
        mov EAX,0  ;reset EAX
        
        ;the bits 24-31 are the same as the bits 0-7 of A
        
        mov AX, word [a] ; AX=01010101 01010101b=21845  we isolate bits 0-7 of A
        and AX, 0000000011111111b  ; AX=00000000 01010101b=85
        mov CL, 8
        ror EAX, CL  ; rotate right 8 bits => EAX=01010101 00000000 00000000 00000000b=1426063360
        or EBX, EAX  ; EBX=01010101 00000000 01101010 00101010b = 1426090538
        mov EAX,0  ;reset EAX
        
        ;the bits 16-23 are the same as the bits 8-15 of A
        
        mov AX, word [a] ; AX=01010101 01010101b=21845  we isolate bits 8-15 of A
        and AX, 1111111100000000b  ; AX=01010101 00000000b=21760
        mov CL, 8
        rol EAX, CL  ; rotate right 8 bits => EAX=00000000 01010101 00000000 00000000b=5570560
        or EBX, EAX ; EBX=01010101 01010101 01101010 00101010b = 1431661098 => final result
        mov EAX,0  ;reset EAX
        
        mov dword [d], EBX
        mov EBX,0  ;reset EBX
        mov ECX,0  ;;reset ECX
        
        mov CL, byte [c] ;verification: CL=01101010b = 106
        
        mov EDX, dword [d] ;verification EDX=01010101 01010101 01101010 00101010b = 1431661098
        
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
