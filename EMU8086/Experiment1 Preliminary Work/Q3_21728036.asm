
org 100h 

Mov AX,0b                 ;AX Register is the counter of '0'.
Mov DX,01101010b
Mov CX,8                  ;This is the counter of JCXZ
 
TRY:
Jcxz Fýnýsh               ;JCXZ is repeated until CX=0.Since CX=0,it jump to Fýnýsh label.
Shr DX,1                  ;Shift all bits right, the bit that goes off is set to CF.
Jnc Fýnd                  ;IF CF=0,then jump
Dec CX                    ;Decrease the counter of JCXZ
Jmp TRY                   ;We go back to the beginning.
    
Fýnd:
Inc AX                    ;IF CF=0, increase the AX Register 
Dec CX                    ;Decrease the counter of JCXZ
JMP TRY                   ;We go back to the beginning.

Fýnýsh:  
  
Ret
End                       ;Egemen Can AYDUÐAN - 21728036

