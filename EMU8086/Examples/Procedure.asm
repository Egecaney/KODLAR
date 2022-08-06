Data Segment
     HWSpace DB 0d
Ends
Extra Segment
    String1 DB "Emu8086 Assembly Programming"
    String2 DB "Egemen Can Aydugan 21728036"
Ends

Stack Segment
    DW   128  dup(0)
Ends

Code Segment
Start:

MOV AX,Data
MOV DS,AX
MOV AX,Extra
MOV ES,AX
 
MOV CX,28d
LEA DI,String1
MOV AL,32d   ;Space 

CALL FýndSpace

MOV AX,4C00h  ;Exit to Operating System.
INT 21h

FýndSpace proc
   TRY:
     JCXZ FINISH
     SCASB   ;DI+1 yapýyor , ES:[DI]
     JE Space
     DEC CX
     JMP TRY

    Space:
     INC [HWSpace]
     DEC CX
     JMP TRY  
    FINISH:
     Ret
FýndSpace endp
 
Ends
End start