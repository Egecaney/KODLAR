; ISLEM SONUNDA NUMBERS2 DEGERLERI 5,2,3,4 OLDU.
org 100h

LEA BX,Numbers1    
LEA BP,Numbers2
           
MOV SI,0 
MOV DI,1
MOV CX,3         
XX:         
MOV AL,[BX+SI]
MOV [BP+DI],AL
INC SI
INC DI         
LOOP XX 

MOV AL,[BX+3]
MOV [BP],AL

ret
Numbers1 DB 2,3,4,5
Numbers2 DB 4 dup(?)
 
end




