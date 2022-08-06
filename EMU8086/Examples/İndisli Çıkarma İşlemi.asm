data segment
     Numbers DB 2,5,4,8 
     Fark DB 4 dup(?)
ends

stack segment
    DW   128  dup(0)
ends

code segment
start:
      MOV AX,Data
      MOV DS,AX
      
      LEA BX,Numbers
      LEA SI,Fark
      MOV CX,4h
      MOV DI,0h
      MOV AL,0h
       
      TRY:
      MOV AH,[BX+DI]
      SUB AH,AL   
      MOV [SI],AH 
      INC AL
      INC SI
      INC DI
      LOOP TRY
    

ends

end start
