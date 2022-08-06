Org 100h

MOV AH,09h
MOV DX,OFFSET InputStrýng
INT 21H

LEA BX,InputData
LEA BP,OutputData

TRY: 
MOV AH,01h
INT 21h

MOV [BX],AL
CMP AL,0Dh
JE FINISH 
         
XOR AL,00100000b
MOV [BP],AL
INC BP

JMP TRY 

FINISH:

MOV AL,'$'
MOV [BP],AL
         
MOV AH,09h            
MOV DX,OFFSET OutputStrýng                     
INT 21H  
         
MOV AH,09h
MOV DX,OFFSET OutputData
INT 21H

Ret
InputStrýng DB 'INPUT :','$'
OutputStrýng DB 'OUTPUT:','$' 
InputData DB 10 dup(?)
OutputData DB 10 dup(?)

