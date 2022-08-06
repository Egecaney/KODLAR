org 100h

MOV BX,9     ; I put the value in DX Register
MOV CX,BX
SUB CX,0002h   ;This is my counter of loop
MOV DI,0001h   ; this is my divider value

TRY: 
INC DI            ; I increment the value of DI for evert loop
MOV AX,BX         
MOV DX,0          ;Before divider, ý did DX=0 
DIV DI            ;This is my prime number controller
CMP DX,0          ;If ý can divide the value, ZF will be 1
JE F1             ;If zf=1, it jump to F1 Position
LOOP TRY
 
MOV DX,BX         ;If this is a prime number, DX will equal to begining value.
JMP FINISH        
    
    
F1:  
MOV DX,0FFFFh     ;If this is not prime number, DX will equal to 0FFFFh.

FINISH:    
ret
end                ;Egemen Can Ayduðan - 21728036


