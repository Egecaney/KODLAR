Org 100h

MOV AH,09h
MOV DX,OFFSET Somewords       ;To show my InData.
INT 21h 

LEA BX,Somewords
MOV DI,01h                     ;DI is my counter.

TRY: 
MOV AL,[BX]                   ;The word is in the AL Register.
CMP AL,46d                    ;Compare the word as a $ sign?
JE FINISH1                    ;If word is dot,ZF will be 1 and the code will jump to the FINISH.  
CMP AL,32d                    ;Compare the word as a space button?
JE Space                      ;If word is SPACE,ZF will be 1 and the code will jump to the Upper.
INC BX                        ;Otherwise, Increase the BX and Turn the TRY.
JMP TRY
 
Space:                        ;If the word is space,our counter isincreased.
INC DI
INC BX                        ;Increase the BX and Turn the TRY.
JMP TRY

FINISH1:                      ;Sentence finished, now we will press the screen. 

MOV AH,09h
MOV DX,OFFSET NextRow         ;To pass the next row.
INT 21H

MOV CX,DI                     
ADD CX,48d                    ;In ASCII Table, numbers range from 48 to 57. 
MOV DX,CX 

SUB DX,58d                    ;This is It checks if it is greater than 10
JNC FINISH2                   ;10 has two character, we can not describe in ASCII
                              
MOV DX,CX                     
MOV AH,2                      ;If my counter is in 0-9
INT 21H
JMP FINISH3 

FINISH2:                      ;If my counter is above 10, ý print 10 on the screen
MOV DX,49d
MOV AH,2                      ;To show 1
INT 21h

MOV DX,48d
MOV AH,2                      ;To show 0
INT 21h
FINISH3: 
     
Ret
Somewords DB 'Technically, anything with a microprocessor can be considered a robot.'
NextRow DB 0Ah,0DH,'$'
End




