
org 100h

 LEA BX,Metin
 LEA BP,Metin2
 MOV SI,0
 MOV CX,6
       
 TRY:
 MOV AX,[BX+SI]
 MOV [BP+SI],AX
 AND [BP+SI],11011111b
 INC SI
 LOOP TRY

ret
 Metin DB 'egemen'
 Metin2 DB 6 dup(?)


