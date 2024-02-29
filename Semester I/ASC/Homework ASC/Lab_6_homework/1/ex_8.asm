;A list of doublewords is given. Obtain the list made out of the low bytes of the high words of each doubleword from the given list with the property that these bytes are palindromes in base 10

bits 32

global start        

extern exit              
import exit msvcrt.dll    

segment data use32 class=data
    s dd 12345678h, 1A2C3C4Dh, 98FCDC76h
    len equ ($-s)/4
    d times len db 0
    aux db 0
    uc dd 0

segment code use32 class=code
    start:
        mov ECX, len  ; ECX=the lenght of the string
        mov ESI, s 
        mov EDI, d
        cld  ;parse the string from left to right(DF=0).
        jecxz endloop  ; if ECX=0
        myloop:
            lodsd ;EAX=the current doubleword from the string
            shr EAX, 16  ; we move the word from AX -> AH:AL
            mov AH, 0 ;we are interested in the low byte 
            mov [aux], AL
            mov EBX, 0
            mov [uc], ECX ; we store the value of ECX, as we need this register
            mov BX,10
            mov CX,0
            reverting:
                xchg AX,CX
                mul BX;  AX = "10*B"  DX = overflow (typically 0)
                
                xchg AX,CX; Change AX and BX back: BX="10*B"
                mov DX,0 ; Prepare DX for "div"
                div BX ;  AX = "A/10"     DX = "A MOD 10" = "digit"
                
                add CX,DX  ; "B = 10*B+digit"
                cmp AX,0  ;if we still have digits in AX
                ja reverting  ; Here CL will contain the "reverted" number, as from the beginning the value was a byte
                
            mov AL, [aux]
            cmp AL,CL
            mov ECX, [uc]
            jne notadd
            stosb;store AL into the byte from the address <ES:EDI> 
            notadd: 
        loop myloop
        endloop:
        push    dword 0      
        call    [exit]       
