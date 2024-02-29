bits 32 

global _increment ; indicate to the assembler that the function show should be available to other compile units 

segment data public data use32; the linker may use the public data segment for external data

; the code written in assembly language resides in a public segment, that may be shared with external code
segment code public code use32                          
_increment:
    ; crate a stack frame
    push EBP
    mov EBP, ESP
    
    ; retreive the function's arguments from the stack
    ; [ebp+4] contains the return value 
    ; [ebp] contains the ebp value for the caller
    
    mov EAX, [EBP+8]; EAX  <- i
    
    inc EAX  ;i=i+1
    
    ; restore the stack frame
    mov ESP, EBP
    pop EBP
    
    ret
    ; cdecl call convention - the caller will remove the parameters from the stack