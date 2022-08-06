;INC AND DEC = Increment and Decrement 

org 100h

MOV AL,20h   ;AL=20h
MOV AH,19h   ;AH=19h
DEC AL       ;AL 1 azaldi.(AL=1Fh)
INC AH       ;AH 1 artti. (AH=1Ah)

LEA BX,Number[1]   ;Number[1]'in adresini BX'e yazdi.
INC BX             ;BX'i 1 artirdi.
                            
DEC Number[1]      ;Number[1]=24h
INC Number[0]      ;Number[0]=17h

ret
Number DB 16h,25h


                  ;INC ve DEC komutlari REG ve Memory'e yazilir.
                  ;Carry Flag bu komuttan etkilenmez.
