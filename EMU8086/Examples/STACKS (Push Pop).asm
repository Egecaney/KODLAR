;STACK
;PUSH POP KOMUTU

data segment
    yuksek DB 2 dup(?)
    dusuk DB 2 dup(?)
ends

stack segment
    dw   128  dup(0)
ends

code segment
start:
Mov AX,data
Mov DS,AX
       
Push 2244h
Push 3366h       
  

MOV SI,0 
Mov CX,4 

Back:       
Pop AX
Mov dusuk[SI],AL       
Mov yuksek[SI],AH       
DEC CX
INC SI      
Loop Back       
       
       
Mov Ax, 4c00h
int 21h  

ends

end start
              
              ;PUSHA VE POPA TEKRAR YAZDIRIR
              ;AMACI TEKRAR KULLANMAYI KOLAYLASTIRMAK
              
              ;PUSHF VE POPF DEGERLERI GECICI OLARAK YAZAR
              ;ISLEM SONUNDA ESKI HALÝNE DONERLER
              ;16 BIT KULLANIRLAR
              ;STACKLAR 16 BITTIR
            
          