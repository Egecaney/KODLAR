
Org 100h 

 LEA BP,Somewords            ;To put the Input Data
 MOV DI,0h

 HMTURN:               ;HMTURN shows how many caharacter in input data
 MOV AL,[BP+DI]        
 INC DI                ;MY Counter
 CMP AL,36d            ;If the word is $ sign,the counter ends.
 JNE HMTURN
 MOV AL,0h             ;Reset the AL Register
 DEC DI                ;Decreament reason is the $ sign. 
 MOV CX,DI             ;My second counter to show the output data 

 READ:      
 MOV AL,[BP]           ;Word is stored in AL Register.
 PUSH AX               ;The word is being held.
 INC BP                ;To pass other word.
 MOV AH,0Eh
 INT 10h               ;To show input data in my screen.
 MOV AH,0h             ;AH is reset because we show the word at AX.
 DEC CX                ;If CX=0, The loop ends.
 JNZ READ 

 MOV AH,09h
 MOV DX,OFFSET NextRow   ;To pass next row.
 INT 21h    

 WRITE:                  ;My output LOOP
 MOV AH,0h               
 POP AX                  ;To print the held values.
 MOV [BP+DI],AL
 MOV AH,0Eh              ;To show output data in my screen.
 INT 10h 
 DEC DI                  ;If DI=0, The loop ends.
 JNZ WRITE 

 RET
 Somewords DB 'FETs are voltage controlled devices.','$'
 NextRow DB 0Ah,0Dh,'$'
End




