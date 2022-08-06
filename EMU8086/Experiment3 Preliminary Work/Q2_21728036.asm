.Model Small
.Stack 64
.Data
   String1 DB "It is not satisfy the condition.","$"
.Code  
Proc Main
   Mov AX,Data
   Mov DS,AX
   
   Mov AX,0A00BH        ; I put the value in AX Register
   Call Funct           ; Call the procedure
Endp Main
Proc Funct         
   Push AX              ; To saves it to use later

   Rol AX,4             ; To checks the middle nibbles are zero
   Cmp AH,00h
   Je Exists            ; If the middles are zero, it jumps to Exists 
   Jne NotExists        ; If the middles are not zero, it jumps to NotExists 
     
   Exists:
   Pop AX               ; Pop the first value AX
   Xchg AH,AL           ; Exchanges the AL and the AH
   Ror AL,4             ; Rotates the AL
   Rol AH,4             ; Rotates the AH
   Jmp Finish           ; The reason for rotating 4 times is that the hex value is 4 bits.
   
   NotExists:
   Mov AH,09h
   Mov DX,OFFSET String1   ; If the middles are not zero 
   Int 21h                 ; To print the screen "It is not satisfy the condition.".
   Finish:
Endp Funct
End




