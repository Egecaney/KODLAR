;LEA = Load Effective Address

org 100h

LEA BX,NUMBER1+2  ;BX Number1 dizisinin ikinci 
                  ;sayisinin baslangic adresini gosterir. 
                  ;+2 eklememizin nedeni DW kullanmamizdir.

MOV AX,[BX]       ;AX 9155 sayisini gosterir.

ret 

Number1 DW 7149h,9155h,8151h
   

end      ; LEA komutu REG,MEMORY olarak calisir
         ; Baslangic adres tutucu BX ya da BP 
         ; Indeksi SI ya da DI olmalidir.

         ;MOV operand1,offset operand2 ile ayni gorevdedir.

