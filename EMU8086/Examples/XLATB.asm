;XLATB     
     
org 100h

;BX Taban adres
;AL Istenilen Elemanin sirasi
;xtalb 
   
LEA BX,number ;Number'in adresi BX'e yazildi.
MOV AL,1      ;Numberdan alacagimiz sayinin sirasi yazildi.
XLATB         ;Operasyon olmadan AL'ye deger yazildi.
              ;AL = 49h yazildi
   

ret
Number DB 48h,49h,4Ah,4Bh,4Ch

end

