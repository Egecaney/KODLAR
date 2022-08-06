;Karesinin Almak
org 100h

LEA BX,Number
LEA BP,kare
MOV SI,0
MOV DI,0
MOV CX,2  

TRY:
MOV AL,[BX+SI]
IMUL AL
MOV [BP+DI],AL
INC SI
ADD DI,2
LOOP TRY:

ret  
Number DB 12d,16d
Kare DW 2 dup(?)





