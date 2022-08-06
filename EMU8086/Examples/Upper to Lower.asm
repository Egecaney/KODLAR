Org 100h

MOV AH,09h
LEA DX,InputStrýng
INT 21H

LEA BX,InputData
LEA BP,OutputData

TRY: 
MOV AH,01h
INT 21h

MOV [BX],AL
MOV CX,[BX]
CMP AL,0Dh
JE FINISH

SUB CX,91
JB UppertoLower
JNC LowertoUpper 

UppertoLower:
ADD [BX],32
MOV DI,[BX]
MOV [BP],DI
MOV DI,0
INC BP
JMP TRY

LowertoUpper:
SUB [BX],32
MOV DI,[BX]
MOV [BP],DI
MOV DI,0 
INC BP
JMP TRY

FINISH:

MOV AL,'$'
MOV [BP],AL
         
MOV AH,09h            
LEA DX,OutputStrýng                     
INT 21H  
         
MOV AH,09h
MOV DX,OFFSET OutputData
INT 21H

Ret
InputStrýng DB 'Input :','$'
OutputStrýng DB 'Output:','$' 
InputData DB 10 dup(?)
OutputData DB 10 dup(?)
ret




