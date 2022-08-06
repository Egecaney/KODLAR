Org 100h

MOV AH,09h
MOV DX,OFFSET InputStrýng        ;To show what ý have to do
INT 21H

LEA BX,InData                    ;To put value to the empty register
LEA BP,OutData                   ;InData and OutData hold values

TRY: 
MOV AH,01h                       ;To give input to the screen.  
INT 21h
                                 ;Values are stored in AL
MOV [BX],AL                      ;I put the values on [BX] 
MOV CX,[BX]                      ;To do the substraction
CMP AL,0Dh                       ;If value is enter button,ZF = 1
JE FINISH                        ;If ZF=1,Je command jump to FINISH.

SUB CX,91                        ;To find out what the value is 
JB UppertoLower                  ;If value is big word,CF=1
JNC LowertoUpper                 ;If value is small word,CF=0

UppertoLower:                    ;The reason for this section is to spin the word.
ADD [BX],32                      ;In ASCII Table,the difference between lowercase and uppercase is 32d. 
MOV DI,[BX]                      ;IF I add 32d in the uppercase, it turns to lowercase.
MOV [BP],DI                      ;I stored the value in [BP]
MOV DI,0                         ;After the turning,DI must be 0 again.
INC BP                           ;To pass next word.
JMP TRY

LowertoUpper:
SUB [BX],32                      ;IF I sub 32d in the lowercase, it turns to uppercase.
MOV DI,[BX]                      
MOV [BP],DI                      ;I stored the value in [BP]
MOV DI,0                         ;After the turning,DI must be 0 again.
INC BP                           ;To pass next word.
JMP TRY

FINISH:
MOV AH,09h
MOV DX,OFFSET NextRow                ;To pass the next row
INT 21H

MOV AL,'$'
MOV [BP],AL

MOV AH,09h            
MOV DX,OFFSET OutputStrýng                    
INT 21H  
         
MOV AH,09h
MOV DX,OFFSET OutData                ;To show my OutData
INT 21H

Ret
InputStrýng DB 'Please,enter your name and hometown:','$'        
OutputStrýng DB 'Your name and hometown:','$' 
InData DB 15 dup(?)                  ;My Input Data
OutData DB 15 dup(?)                 ;My Output Data
NextRow DB 0Ah,0DH,'$'               ;To pass the next row
End



