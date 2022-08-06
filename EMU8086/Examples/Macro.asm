Data Segment
    Number1 DB 19d,23d,7d,211d
    String1 DB "Egemen Can Aydugan"
    
Ends

Extra Segment 
    Number2 DB 4 Dup(?)
    String2 DB 4 Dup(?)
Ends
    
Stack Segment
    DW   128  dup(0)
Ends

Code Segment
   
   MCR MACRO HMTURN
    MOV CX,HMTURN
   LOCAL TRY   ; Ýkinci döngüde sorun yaþamamak için
   TRY:
    MOV AL,DS:[SI]
    MOV ES:[DI],AL
    INC DI
    INC SI 
   LOOP TRY
   
   MCR ENDM
   
Start: 
    MOV AX,Data
    MOV DS,AX
    MOV AX,Extra
    MOV ES,AX
    
    
    LEA SI,Number1
    LEA DI,Number2
    MCR 4d; MACRO    ;Döngü Sayýsý 4
    
    
    LEA SI,String1
    LEA DI,String2
    MCR 18d; MACRO   ;Döngü Sayýsý 18

MOV AX, 4c00h
INT 21h 

Ends
End Start
