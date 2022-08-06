.Model Small
.Stack 64
.Data
.Code  
Proc Main
   Mov AX,Data
   Mov DS,AX
   
   Mov AX,0B217h        ; I put the value in AX Register
   Call Funct           ; Call the procedure
Endp Main
Proc Funct         
                
   Ror AH,4d             ; Rotates the AH
   Ror AX,4d             ; Rotates the AX
   Ror AL,4d             ; Rotates the AL
    
Endp Funct
End