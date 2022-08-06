
org 100h 

Mov AX,0b               ;AX Register is my counter.
Lea BX,Number
Mov BX,[BX]
            
 
TRY:
Shr BX,1                ;Shift all bits right, the bit that goes off is set to CF.
Jnc Fýnd                ;If CF=0 then jump.               
Inc AX                  ;We increment AX to find the 0 bit position. 
Jmp TRY                 ;Since CF = 1, we go back to the beginning.

Fýnd:                   ;If CF=0,We increase the AX once more and find the result.
Inc AX

Ret
Number DW 11111011b     ;I wrote the number in the memory. 
End

                         ;Egemen Can AYDUÐAN - 21728036

