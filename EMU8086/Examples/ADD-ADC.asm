;ADD ve ADC Komutlarý
org 100h

LEA BX,Number1
LEA BP,Number2                       ;Reg,Memory
                                     ;Memory,Reg
MOV AX,[BP]                          ;Reg,Reg
ADD AX,[BX]                          ;Memory,Immediate
ADC AX,0                             ;Reg,Immediate
Ret                                  
Number1 DW 99AFh
Number2 DW 77A1h
End
                   ;ADC KOMUTU EKSTRA OLARAK CF DE EKLER.

                   ;ADD = OP1+OP2
                   ;ADC = OP1+OP2+CF

