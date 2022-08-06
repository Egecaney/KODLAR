.Model Small
.Stack 64
.Data
      String1 DB 'The Offset is: ','$'
      NextRow DB 0Ah,0DH,'$'                       ; To the next row
      Numbers DW 1230h,1F05h,045Ah,0B0ACh,4708h    ; My Values
.Code
    
Proc Main
    
  Mov AX,Data
  Mov DS,AX
  
  LEA SI,Numbers          ; I take the value in DATA Segement.
  MOV AX,[SI]             ; And put the value in AX Register.
  Mov BL,00h              ; This is my counter.(Highest-->Lowest) 
  Mov BH,05h              ; Loop counter for retrieving numbers from memory
  
 Týmes:
  Call Foffset            ; I call the Foffset.
  
  ADD SI,2                ; I add 2 to SI because to move to the next number.
  MOV AX,[SI]             ; The reason I add 2 is because its number is word type. 
                          ; And put the new value in AX Register.
  DEC BH                  ; Loop Counter
  CMP BH,00h              ; To finish the code when the loop is over.
  JE  Over                   
  JMP Týmes               ; Return to get a new number      .
                          
  Mov AH,004Ch            ; To stop program.
  Int 21h
   
Endp  Main

Proc Foffset
    
 RETURN:                  ; To examine the next bit
  Inc BL                  ; I ýncrease my counter to find offset.
  MOV DI,0h               ; To reset 4 býts
  MOV CX,4h               ; To control 4 bits each time because of 4 BINARY = 1 HEX
  
 TRY:                  
  SHL AX,1d               ; And ý shift the number 1 bit to the left.
  JC HERE                 ; IF CF=1,it jumps to HERE
  JCXZ COMP               ; If CX =0,ýt jumps to COMP 
  DEC CX                  ; 4 Bit Counter
  CMP CX,00h              ; If the counter finish, CF=1
  JNE TRY                 ; If CX does not 0,it jumps to TRY
  
 COMP:
  CMP DI,00h              ; This is number controller. 
                          ; If the number is 0, the offset has been found.
  JNE RETURN              ; If number is not zero, it jumps to RETURN and starts to examine the next issue   
  JE FINISH               ; If the number is 0, it jumps to Fýnýsh.
  
 HERE:                    ; The part that checks the 1 bit. 
  INC DI                  ; IF DI increases, this number is not 0.
  DEC CX
  CMP CX,00h              ; If the counter finish, CF=1 
  JE COMP                 ; IF CF=1, it jumps to COMP to control number finally.
  JMP TRY                 
  
                          
 FINISH:            
  Mov AH,09h
  Mov DX,OFFSET String1   ; To show string on the screen
  Int 21h
  
  Add BL,48d              ; I add 48 to the counter to show the number on the screen.
  Mov DL,BL               
  
  Mov AH,02h              ; Print the offset
  Int 21h 
  
  Mov AH,09h
  Mov DX,OFFSET NextRow   ; To pass the next row.
  Int 21H
  
  Mov BL,0h
  Mov DL,0h               ; I have to make Registers 0 for the next number.
  Mov AX,0h
  Ret 
Endp Foffset
Over:
Ends
