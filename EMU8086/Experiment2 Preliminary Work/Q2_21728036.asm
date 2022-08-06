Org 100h

MOV AH,09h
MOV DX,OFFSET Somewords       ;To show my InData.
INT 21h 

MOV AH,09h
MOV DX,OFFSET NextRow         ;To pass the next row.
INT 21H

LEA BX,Somewords              ;I stored ýnput memory location in the BX Register.
SUB [BX],32d                  ;First turning operation.
INC BX                        ;To the next word.

TRY: 
MOV AL,[BX]                   ;The word is in the AL Register.
CMP AL,36d                    ;Compare the word as a $ sign?
JE FINISH                     ;If word is $ sign,ZF will be 1 and the code will jump to the FINISH.  
CMP AL,32d                    ;Compare the word as a space button?
JE Upper                      ;If word is SPACE,ZF will be 1 and the code will jump to the Upper.
INC BX                        ;Otherwise, Increase the BX and Turn the TRY.
JMP TRY
 
Upper:
SUB [BX+1],32d                ;If the word is space,the next word will be Uppercase.
INC BX                        ;Increase the BX and Turn the TRY.
JMP TRY

FINISH:      
MOV AH,09h
MOV DX,OFFSET Somewords       ;To show OutData.
INT 21H

Ret
Somewords DB 'btjs are current controlled devices.','$'
NextRow DB 0Ah,0DH,'$'
End


