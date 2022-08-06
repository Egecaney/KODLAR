org 100h

LEA BX,Number1            ;I took the addresses of numbers with LEA.
LEA BP,Number2                       
                                     
MOV AX,[BP]               ;I stored the value of Number2 in the AX Register.                  
ADD AX,[BX]               ;And sum the numbers in the AX Register.                   
                            
Ret                                  
Number1 DW 8916h          ;I wrote the number1 and number2 in the memory.
Number2 DW 76EAh       
End

                          ;Egemen Can AYDUÐAN - 21728036