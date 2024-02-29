bits 32 
segment code use32 public code
global operations  
;define the function      
;the function will return the result in eax which is an integer
operations: ;int operations(int n)
    mov EAX,[ESP+4] ;move to EAX my parameter
    inc EAX 
    cmp EAX, 127 
    ret 4 ; in this case, 4 represents the number of bytes that need to be cleared from the stack (the parameter of the function)  
