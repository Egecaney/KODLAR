;TERSTEN DIZI KOPYALAMA

Org 100h

LEA BX,Name1
LEA BP,BackName
          
MOV CX,10
MOV DI,0
MOV SI,9

Start:          
MOV AX,[BX+SI]
MOV [BP+DI],AX
INC DI
DEC SI
Loop start          
          
          
      
Ret
Name1 DB 'Egemen Can'
BackName DB 10 dup(?) 
End



