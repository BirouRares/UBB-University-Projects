bits 32 ; assembling for the 32 bits architecture


global start        


extern exit               
import exit msvcrt.dll    
                         


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
        ;signed
        
        ;1/a
        mov AX, 1  ;AX=1
        cwd ; AX=DX:AX=1
        idiv word[a]  ; AX=1/a=0    DX=1%a=1
        mov DX, 0  ; DX=0
        mov BX,AX ;BX=AX=0
        
        ;200*b
        mov DX,200 ;DX=200
        mov AX, [b] ;AX=b=10
        imul DX ;AX=2000  
        
        ;1/a + 200*b
        adc BX,AX ;BX=2000
        
        ;c / (d+1)
        mov AL, [c] ;AL=10
        cbw ; AX=10
        mov CL, [d] ; CL=4
        adc CL, 1; CL=5
        idiv CL ;AL=c/(d+1) =2  AH=c % (d+1)=0
        
        ;1/a + 200*b -c / (d+1)
        cbw ;AX=2
        sbb BX, AX ;BX=1998
        
        ;x / a
        mov AX, [a] ;AX=2
        cwde ;DX:AX=2
        push DX
        push AX
        pop ECX ;ECX=2
        
        mov EAX, dword [x] 
        mov EDX, dword [x+4]; EDX:EAX=x=310
        
        idiv ECX ; EAX=EDX:EAX/ECX=155  EDX=EDX:EAX%ECX=0
        
        ;1/a + 200*b -c / (d+1) + x / a
        ;Corection here
        mov ECX,EAX  ;ECX=EAX=155
        mov AX, BX ;AX=BX=1998
        cwde ;EAX=1998
        add EAX,ECX  ; EAX=EAX+ECX=1998+155=2153
        
        ;1/a + 200*b -c / (d+1) + x / a - e
        sub EAX, [e] ;EAX=2153-150=2003
        
        push    dword 0     
        call    [exit]     
