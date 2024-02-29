bits 32 

global start        


extern exit               
import exit msvcrt.dll    

segment data use32 class=data
    sir  dq  123110110abcb0h,1116adcb5a051ad2h,4120ca11d730cbb0h
    ;b0 bc 0a 11 10 31 12 00
	len equ ($-sir)/8;the length of the string (in quadwords)
	opt db 8;variabile used for testing divisibility to 8
	zece dd 10;variabile used for determining the digits in base 10 of a number by successive divisions to 10
	suma dd  0;variabile used for holding the sum of the digits 


segment code use32 class=code
    start:
        mov esi,sir
        mov BL, 0
        mov ECX, len
        myloop:
            lodsd  ;EAX= first dw from sir  and increment ESI with 4
            lodsw  ; AX= word and esi+2
            lodsw  ; AX=high word
               ;AL
            mov AH,0
            div byte [opt]
               ;check remainder AH
            cmp AH,0  ;if remainder is 0
            jne dontinc
                inc BL
            dontinc:
        loop myloop
        
        ;This is another solution
        push    dword 0     
        call    [exit]      
