;XCHG = Exchange Value of Two Operators

org 100h  

MOV AL,99h               ;AL =99h oldu.
      
XCHG AL,Number[2]        ;AL=11h , Number[2]=99h oldu.
 
MOV BH,Number[2]         ;BH=99h oldu.

ret       

Number DB 08h,45h,11h    ; En sonunda Number DB 08h,45h,99h oldu.
     
end


                 ;REG and Memory
                 ;Memory and REG
                 ;REG AND REG   
             
