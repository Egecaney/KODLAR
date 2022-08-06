Name "ELE338_PROJECT_EgemenCan_Ayduðan_21728036"

PUTC    MACRO   Char
        PUSH    AX
        MOV     AL, Char
        MOV     AH, 0Eh
        INT     10h     
        POP     AX
ENDM

Org 100h
Jmp Code

String1 DB "Welcome to the PCB Trace Width Calculator",0Dh,0Ah,'$'  
String2 DB 0Dh,0Ah, "Here is our options: ",'$'
StringA DB 0Ah,0Dh,"A/a: Maximum current calculation from trace width in internal layer","$"
StringB DB 0Ah,0Dh,"B/b: Maximum current calculation from trace width in external layer","$"
StringC DB 0Ah,0Dh,"C/c: Minimum trace width calculation from current in internal layer ","$"
StringD DB 0Ah,0Dh,"D/d: Minimum trace width calculation from current in external layer","$"
PressEsc DB 0Ah,0Dh,"ESC: Any time to exit program",0Ah,0Dh,"$"
Choice DB 0Dh,0Ah,"Select the choice you want to do:  ",'$' 
NotValid DB 0Ah,0Dh,"You entered invalid value. All done is canceled. Please, try again!",0Ah,0Dh,'$'
NextLine DB 0Ah,0Dh,"$"

MaxCurInt DB 0Dh,0Ah, "Maximum Current will be calculated in Internal Layer",'$'
CalculateMaxCurInt DB 0Dh,0Ah, "Enter Trace Width value (in mils) for internal layer: ",'$'
MaxCurExt DB 0Dh,0Ah, "Maximum Current will be calculated in External Layer",'$'
CalculateMaxCurExt DB 0Dh,0Ah, "Enter Trace Width value (in mils) for external layer: ",'$'
MinTWInt DB 0Dh,0Ah, "Minimum Trace Width will be calculated in Internal Layer",'$'
CalculateMinTWInt DB 0Dh,0Ah, "Enter Current value (in A) for internal layer: ",'$'
MinTWExt DB 0Dh,0Ah, "Minimum Trace Width will be calculated in External Layer",'$'
CalculateMinTWExt DB 0Dh,0Ah, "Enter Current value (in A) for external layer: ",'$' 

Inp1 DW dup(0)
Inp2 DW dup(0)
Ten  DW 10
Precision = 30

WtoC1 DB "W=",'$'
WtoC2 DB "(mils) I=",'$'
WtoC3 DB "(A)",'$'

CtoW1 DB "I=",'$'
CtoW2 DB "(A) W=",'$'
CtoW3 DB "(mils)",'$'
 
Code:
Start:    

Mov AH,9h
Mov DX,OFFSET String1    ; To printf 'Welcome' 
Int 21h
Mov AH,9h
Mov DX,OFFSET String2    ; To show options

Mov AH,9h
Mov DX,OFFSET StringA    ; To printf option A
Int 21h
Mov AH,9h
Mov DX,OFFSET StringB    ; To printf option B
Int 21h
Mov AH,9h
Mov DX,OFFSET StringC    ; To printf option C
Int 21h
Mov AH,9h
Mov DX,OFFSET StringD    ; To printf option D
Int 21h 
Mov AH,9h
Mov DX,OFFSET PressEsc   ; To printf option ESC
Int 21h 

Mov AH,9h
Mov DX,OFFSET Choice     
Int 21h
Mov AH,01h               
Int 21h                  ; To get the selection

Cmp AL,27d               ; IF Select Data is ESC
Je Finish

Cmp AL,'A'                           ; IF Select Data is A/a
Je CALL Max_Current_Int              ; Jump to Max_Current_Int 
Cmp AL,'a'             
Je CALL Max_Current_Int

Cmp AL,'B'                           ; IF Select Data is B/b
Je CALL Max_Current_Ext              ; Jump to Max_Current_Ext
Cmp AL,'b'             
Je CALL Max_Current_Ext
 
Cmp AL,'C'                           ; IF Select Data is C/c
Je CALL Min_Width_Int                ; Jump to Min_Width_Int 
Cmp AL,'c'             
Je CALL Min_Width_Int
 
Cmp AL,'D'                           ; IF Select Data is D/d
Je CALL Min_Width_Ext                ; Jump to Min_Width_Ext
Cmp AL,'d'             
Je CALL Min_Width_Ext  
 
 
Invalid: 
Mov AH,9h
Mov DX,OFFSET NotValid         ; When the select is not A/B/C/D or a/b/c/d.  
Int 21h                        ; To print screen "It is not valid input". 
Mov AH,9h
Mov DX,OFFSET NextLine
Int 21h 
Jmp Start

Finish:
Ret                
Endp Main

;----------------------------------------------------------
Proc Max_Current_Int 
    
Mov AH,9h
Mov DX,OFFSET NextLine
Int 21h    
Mov AH,9h
Mov DX,OFFSET MaxCurInt    
Int 21h                  
Mov AH,9h
Mov DX,OFFSET CalculateMaxCurInt
Int 21h
 
Call Scan_Num                                  
Mov Inp1,CX
Mov Inp2,CX
            
         ; Area = (Current/(k*Temp_Rise^b))^(1/c)
         ; Width = Area/(Thickness*1.378)
         
         ; IN INTERNAL LAYERS:
         ; Temp_Rise = 10 C  , Thickness = 1 oz 
         ; b = 0.44  ,  c = 0.725 , k = 0.024  
            
         ; Current = Area^c (k*10^b)  
         ; Current = (Width^0.725)/12
         ; Current = (1+0.725(Width-1))/12     (From Taylor Series)
         ; Current = (10+7(Width-1))/120    
         
         ; Finally
         ; Current = (3+7*Width)/120 
         
Mov AX,0000h
MOV DL,7d
Cross1:         
Add AX,CX               ; 7*Width
Dec DL
Cmp DL,00h
Jne Cross1 

Add AX,3d               ; 7*Width+3
Mov Inp1,AX

Pusha
Mov AX,03d              ; 80x25 Emulator Screen
Int 10h
Popa

Mov DL,00d              ; DH = Row, DL = Column
Mov DH,00d              ; Title Coordinat
Mov AH,02h              
Int 10h
Mov AH,9h
Mov DX,OFFSET MaxCurInt      ; Title of Emulator Screen
Int 21h
 
Call Draw_Internal           ; To draw internal layer

Mov DL,30d                   ; Starting coordinate of values
Mov DH,05d
Mov AH,02h
Int 10h

Mov AH,9h
Mov DX,OFFSET WtoC1    
Int 21h

Mov AX,Inp2
Call Print_Num

Mov AH,9h
Mov DX,OFFSET WtoC2    
Int 21h

Mov     AX, Inp1
Xor     DX,DX
Mov     BX,120d   
Idiv    BX         
Call    Print_Float

Mov AH,9h
Mov DX,OFFSET WtoC3   
Int 21h
            
Endp Max_Current_Int
Ret

;----------------------------------------------------------
Proc Max_Current_Ext 
    
Mov AH,9h
Mov DX,OFFSET NextLine
Int 21h    
Mov AH,9h
Mov DX,OFFSET MaxCurExt    
Int 21h                  
Mov AH,9h
Mov DX,OFFSET CalculateMaxCurExt
Int 21h
 
Call Scan_Num                                  
Mov Inp1,CX
Mov Inp2,CX

         ; Area = (Current/(k*Temp_Rise^b))^(1/c)
         ; Width = Area/(Thickness*1.378)
         
         ; IN EXTERNAL LAYERS:
         ; Temp_Rise = 10 C  , Thickness = 1 oz 
         ; b = 0.44  ,  c = 0.7 , k = 0.048  
            
         ; Current = Area^c (k*10^b)  
         ; Current = (Width^0.7)/6
         ; Current = (1+0.7(Width-1))/6     (From Taylor Series)
         ; Current = (10+7(Width-1))/60    
         
         ; Finally
         ; Current = (3+7*Width)/60 
         
Mov AX,0000h
MOV DL,7d
Cross2:         
Add AX,CX
Dec DL                  ; 7*Width
Cmp DL,00h
Jne Cross2 

Add AX,3d               ; 7*Width+3
Mov Inp1,AX

Pusha
Mov AX,03d              ; 80x25 Emulator Screen
Int 10h
Popa

Mov DL,00d
Mov DH,00d              ; Title Coordinat
Mov AH,02h
Int 10h
Mov AH,9h
Mov DX,OFFSET MaxCurExt    
Int 21h
 
Call Draw_External      ; To draw external layer

Mov DL,30d
Mov DH,05d              ; Starting coordinate of values
Mov AH,02h
Int 10h

Mov AH,9h
Mov DX,OFFSET WtoC1    
Int 21h

Mov AX,Inp2
Call Print_Num

Mov AH,9h
Mov DX,OFFSET WtoC2    
Int 21h

Mov     AX, Inp1
Xor     DX,DX
Mov     BX,60d   
Idiv    BX         
Call    Print_Float

Mov AH,9h
Mov DX,OFFSET WtoC3    
Int 21h
 
Endp Max_Current_Ext
Ret

;----------------------------------------------------------
Proc Min_Width_Int 
    
Mov AH,9h
Mov DX,OFFSET NextLine
Int 21h        
Mov AH,9h
Mov DX,OFFSET  MinTWInt   
Int 21h                  
Mov AH,9h
Mov DX,OFFSET CalculateMinTWInt
Int 21h
 
Call Scan_Num                                  
Mov Inp1,CX
Mov Inp2,CX 

         ; Area = (Current/(k*Temp_Rise^b))^(1/c)
         ; Width = Area/(Thickness*1.378)
         
         ; IN INTERNAL LAYERS:
         ; Temp_Rise = 10 C  , Thickness = 1 oz 
         ; b = 0.44  ,  c = 0.725 , k = 0.024  
            
         ; Width = (Current^(1/c))/(k^(1/c)*10^(0.44/c)*1.378)    
         ; Width = 31*(Current^(1.38))
         ; Width = 31*(1+1.38(Current-1))
         ; Width = 31+43(Current-1)
         
         ; Finally
         ; Width = 43*Current-12 
         
Mov AX,0000h
MOV DL,43d
Cross3:         
Add AX,CX
Dec DL                  ; 43*Width
Cmp DL,00h
Jne Cross3 

Sub AX,12d              ; 43*Width-12
Mov Inp1,AX

Pusha
Mov AX,03d              ; 80x25 Emulator Screen
Int 10h
Popa

Mov DL,00d              ; Title Coordinat
Mov DH,00d
Mov AH,02h
Int 10h
Mov AH,9h
Mov DX,OFFSET MinTWInt    
Int 21h
 
Call Draw_Internal      ; To draw internal layer

Mov DL,30d
Mov DH,05d              ; Starting coordinate of values
Mov AH,02h
Int 10h

Mov AH,9h
Mov DX,OFFSET CtoW1    
Int 21h

Mov AX,Inp2
Call Print_Num

Mov AH,9h
Mov DX,OFFSET CtoW2    
Int 21h

Mov AX,Inp1
Call Print_Num

Mov AH,9h
Mov DX,OFFSET CtoW3    
Int 21h
  
Endp Min_Width_Int
Ret

;----------------------------------------------------------
Proc Min_Width_Ext
    
Mov AH,9h
Mov DX,OFFSET NextLine
Int 21h    
Mov AH,9h
Mov DX,OFFSET MinTWExt    
Int 21h                  
Mov AH,9h
Mov DX,OFFSET CalculateMinTWExt
Int 21h
 
Call Scan_Num                                  
Mov Inp1,CX
Mov Inp2,CX
         
         ; Area = (Current/(k*Temp_Rise^b))^(1/c)
         ; Width = Area/(Thickness*1.378)
         
         ; IN EXTERNAL LAYERS:
         ; Temp_Rise = 10 C  , Thickness = 1 oz 
         ; b = 0.44  ,  c = 0.7 , k = 0.048  
            
         ; Width = (Current^(1/c))/(k^(1/c)*10^(0.44/c)*1.378)    
         ; Width = 13*(Current^(1.43))
         ; Width = 13*(1+1.43(Current-1))      (From Taylor Series)
         ; Width = 13+19(Current-1)
         
         ; Finally
         ; Width = 19*Current-6 

Mov AX,0000H
MOV DL,19d
Cross4:         
Add AX,CX
Dec DL                 ; 19*Width
Cmp DL,00h
Jne Cross4 

Sub AX,06d             ; 19*Width-6
Mov Inp1,AX 

Pusha
Mov AX,03d             ; 80x25 Emulator Screen
Int 10h
Popa

Mov DL,00d             ; Title Coordinat
Mov DH,00d
Mov AH,02h
Int 10h
Mov AH,9h
Mov DX,OFFSET MinTWInt    
Int 21h
 
Call Draw_External      ; To draw external layer

Mov DL,30d              ; Starting coordinate of values
Mov DH,05d
Mov AH,02h
Int 10h

Mov AH,9h
Mov DX,OFFSET CtoW1    
Int 21h

Mov AX,Inp2
Call Print_Num

Mov AH,9h
Mov DX,OFFSET CtoW2    
Int 21h

Mov AX,Inp1
Call Print_Num

Mov AH,9h
Mov DX,OFFSET CtoW3    
Int 21h
  
Endp Min_Width_Ext
Ret 

;----------------------------------------------------------
Proc Draw_Internal
               
Mov DH,7d              ; Starting position of drawing
Mov DL,15d              
Top_Int_Yellow:        ; Top Part (Yellow)
  Mov AH,02h
  Int 10h
  
  Mov AL,32d           ; AL = Charachter
  Mov BH,0             ; BH = Page Number
  Mov BL,0E0h          ; BL = Color   (0E0h= Yellow)
  Mov CX,1             ; CX = Number of times to print character
  Mov AH,09h
  Int 10h
  
  Inc DL
  Cmp DL,60d           ; To print 45 pixels in one line
Jne Top_Int_Yellow


Mov DI,02d             ; To press the middle section twice
Mov DH,8d
Mov DL,15d 
Jmp Top_Int_Green
Top_Int_Green_Again:   ; Middle Part (Green)
  Inc DH
  Mov DL,15d 
Top_Int_Green:
  Mov AH,02h
  Int 10h
  
  Mov AL,32d           
  Mov BH,0             
  Mov BL,0A0h          ; BL = Color   (0A0h= Green)
  Mov CX,1             
  Mov AH,09h
  Int 10h
  
  Inc DL
  Cmp DL,60d          
Jne Top_Int_Green
  DEC DI
  Cmp DI,00d          
Jne Top_Int_Green_Again

Mov DH,10d
Mov DL,15d  
Left_Int:              ; Left Middle Part (Green)
  Mov AH,02h
  Int 10h
  
  Mov AL,32d           
  Mov BH,0             
  Mov BL,0A0h          ; BL = Color   (0A0h= Green)
  Mov CX,1             
  Mov AH,09h
  Int 10h
  
  Inc DL
  Cmp DL,35d          
Jne Left_Int
Middle_Int:            ; Internal part of drawing
  Mov AH,02h
  Int 10h
  
  Mov AL,32d           
  Mov BH,0             
  Mov BL,0E0h          ; BL = Color   (0E0h= Yellow)
  Mov CX,1             
  Mov AH,09h
  Int 10h
  
  Inc DL
  Cmp DL,40d          
Jne Middle_Int
Right_Int:             ; Right Middle Part (Green)
  Mov AH,02h
  Int 10h
  
  Mov AL,32d           
  Mov BH,0             
  Mov BL,0A0h          ; BL = Color   (0A0h= Green)
  Mov CX,1             
  Mov AH,09h
  Int 10h
  
  Inc DL
  Cmp DL,60d          
Jne Right_Int  

Mov DI,02d
Mov DH,11d
Mov DL,15d 
Jmp Bot_Int_Green
Bot_Int_Green_Again:   ; Middle Part (Green)
  Inc DH
  Mov DL,15d
Bot_Int_Green:
  Mov AH,02h
  Int 10h
  
  Mov AL,32d           
  Mov BH,0             
  Mov BL,0A0h          ; BL = Color   (0A0h= Yellow)
  Mov CX,1             
  Mov AH,09h
  Int 10h
  
  Inc DL
  Cmp DL,60d          
Jne Bot_Int_Green
  DEC DI
  Cmp DI,00d          
Jne Bot_Int_Green_Again

Mov DH,13d
Mov DL,15d  
Bot_Int_Yellow:        ; Bottom Part
  Mov AH,02h
  Int 10h
  
  Mov AL,32d           
  Mov BH,0             
  Mov BL,0E0h          ; BL = Color   (0E0h= Yellow)
  Mov CX,1             
  Mov AH,09h
  Int 10h
  
  Inc DL
  Cmp DL,60d          
Jne Bot_Int_Yellow   
    
Ret
Endp Draw_Internal
;----------------------------------------------------------

Proc Draw_External
               
Mov DH,7d
Mov DL,35d              
Top_Ext_Yellow:
  Mov AH,02h
  Int 10h
  
  Mov AL,32d           ; AL = Charachter
  Mov BH,0             ; BH = Page Number
  Mov BL,0E0h          ; BL = Color   (0E0h= Yellow)
  Mov CX,1             ; CX = Number of times to print character
  Mov AH,09h
  Int 10h
  
  Inc DL
  Cmp DL,40d          
Jne Top_Ext_Yellow


Mov DI,04d
Mov DH,8d
Mov DL,15d 
Jmp Top_Ext_Green
Top_Ext_Green_Again:  
  Inc DH
  Mov DL,15d 
Top_Ext_Green:
  Mov AH,02h
  Int 10h
  
  Mov AL,32d           ; AL = Charachter
  Mov BH,0             ; BH = Page Number
  Mov BL,0A0h          ; BL = Color   (0E0h= Yellow)
  Mov CX,1             ; CX = Number of times to print character
  Mov AH,09h
  Int 10h
  
  Inc DL
  Cmp DL,60d          
Jne Top_Ext_Green
  DEC DI
  Cmp DI,00d          
Jne Top_Ext_Green_Again

  Mov DH,12d
  Mov DL,15d
Bot_Ext_Yellow:
  Mov AH,02h
  Int 10h
  
  Mov AL,32d           ; AL = Charachter
  Mov BH,0             ; BH = Page Number
  Mov BL,0E0h          ; BL = Color   (0E0h= Yellow)
  Mov CX,1             ; CX = Number of times to print character
  Mov AH,09h
  Int 10h
  
  Inc DL
  Cmp DL,60d          
Jne Bot_Ext_Yellow   
    
Ret
Endp Draw_External
;----------------------------------------------------------

SCAN_NUM  PROC    NEAR                                        
        PUSH    DX
        PUSH    AX
        PUSH    SI
        
        MOV     CX, 0
        ; Reset Flag:
        MOV     CS:make_minus, 0

Next_Digit:

        ; Get char from keyboard
        ; Into AL:
        MOV     AH, 00h
        INT     16h
        ; And print it:
        MOV     AH, 0Eh
        INT     10h

        ; Check for MINUS:
        CMP     AL, '-'
        JE      Set_Minus

        ; Check for ENTER key:
        CMP     AL, 0Dh     ; Carriage return?
        JNE     Not_Cr
        JMP     Stop_Input
Not_Cr:


        CMP     AL, 8                   ; 'BACKSPACE' pressed?
        JNE     Backspace_Checked
        MOV     DX, 0                   ; Remove last digit by
        MOV     AX, CX                  ; Division:
        DIV     CS:Ten                  ; AX = DX:AX / 10 (DX-rem).
        MOV     CX, AX
        PUTC    ' '                     ; Clear position.
        PUTC    8                       ; Backspace again.
        JMP     Next_Digit
Backspace_Checked:


        ; Allow only digits:
        CMP     AL, '0'
        JAE     Ok_AE_0
        JMP     Remove_Not_Digit
Ok_AE_0:        
        CMP     AL, '9'
        JBE     Ok_Digit
Remove_Not_Digit:       
        PUTC    8           ; Backspace.
        PUTC    ' '         ; Clear last entered not digit.
        PUTC    8           ; Backspace again.        
        JMP     Next_Digit  ; Wait for next input.       
Ok_Digit:


        ; Multiply CX by 10 (first time the result is zero)
        PUSH    AX
        MOV     AX, CX
        MUL     CS:Ten                  ; DX:AX = AX*10
        MOV     CX, AX
        POP     AX

        ; Check if the number is too big
        ; (Result should be 16 bits)
        CMP     DX, 0
        JNE     Too_Big

        ; Convert from ASCII code:
        SUB     AL, 30h

        ; Add AL to CX:
        MOV     AH, 0
        MOV     DX, CX      ; Backup, in case the result will be too big.
        ADD     CX, AX
        JC      Too_Big2    ; Jump if the number is too big.

        JMP     Next_Digit

set_minus:
        MOV     CS:Make_Minus, 1
        JMP     Next_Digit

Too_Big2:
        MOV     CX, DX      ; Restore the backuped value before add.
        MOV     DX, 0       ; DX was zero before backup!
Too_Big:
        MOV     AX, CX
        DIV     CS:Ten      ; Reverse last DX:AX = AX*10, make AX = DX:AX / 10
        MOV     CX, AX
        PUTC    8           ; Backspace.
        PUTC    ' '         ; Clear last entered digit.
        PUTC    8           ; Backspace again.        
        JMP     Next_Digit  ; Wait for Enter/Backspace.
        
        
Stop_Input:
        ; check flag:
        CMP     CS:Make_Minus, 0
        JE      Not_Minus
        NEG     CX
Not_Minus:

        POP     SI
        POP     AX
        POP     DX
        RET
Make_Minus      DB      ?       ; Used as a flag.
SCAN_NUM        ENDP 
Ret 
;----------------------------------------------------------

PRINT_NUM  PROC    NEAR
        PUSH    DX
        PUSH    AX

        CMP     AX, 0
        JNZ     Not_zero

        PUTC    '0'
        JMP     Printed

Not_zero:
        ; The check SIGN of AX,
        ; Make absolute if it's negative:
        CMP     AX, 0
        JNS     Positive
        NEG     AX

        PUTC    '-'

Positive:
        CALL    PRINT_NUM_UNS
Printed:
        POP     AX
        POP     DX
        RET
PRINT_NUM  ENDP 
Ret

;----------------------------------------------------------

PRINT_NUM_UNS   PROC    NEAR
        PUSH    AX
        PUSH    BX
        PUSH    CX
        PUSH    DX

        ; Flag to prevent printing zeros before number:
        MOV     CX, 1

        ; (Result of "/ 10000" is always less or equal to 9).
        MOV     BX, 10000       ; 2710h - divider.

        ; AX is zero?
        CMP     AX, 0
        JZ      Print_zero

Begin_print:

        ; Check divider (if zero go to end_print):
        CMP     BX,0
        JZ      End_print

        ; Avoid printing zeros before number:
        CMP     CX, 0
        JE      Calc
        ; If AX<BX then result of DIV will be zero:
        CMP     AX, BX
        JB      Skip
Calc:
        MOV     CX, 0   ; set flag.

        MOV     DX, 0
        DIV     BX      ; AX = DX:AX / BX   (DX=remainder).

        ; Print last digit
        ; AH is always ZERO, so it's ignored
        ADD     AL, 30h    ; convert to ASCII code.
        PUTC    AL


        MOV     AX, DX  ; get remainder from last div.

Skip:
        ; Calculate BX=BX/10
        PUSH    AX
        MOV     DX, 0
        MOV     AX, BX
        DIV     CS:Ten  ; AX = DX:AX / 10   (DX=Remainder).
        MOV     BX, AX
        POP     AX

        JMP     Begin_print
        
Print_zero:
        PUTC    '0'
        
End_print:

        POP     DX
        POP     CX
        POP     BX
        POP     AX
        RET
PRINT_NUM_UNS   ENDP

;----------------------------------------------------------
Print_float Proc  Near
 Push    CX
 Push    DX
        ; because the remainder takes the sign of divident
        ; its sign should be inverted when divider is negative
        ; (-) / (-) = (+)
        ; (+) / (-) = (-)
 Cmp     BX,0
 Jns     Div_Not_Signed
 Neg     DX              ; make remainder positive.
Div_Not_Signed:
 
 ; print_num procedure does not print the '-'
 ; when the whole part is '0' (even if the remainder is
 ; negative) this code fixes it:
 Cmp     AX, 0
 Jne     Checked         ; ax<>0
 Cmp     DX, 0
 Jns     Checked         ; ax=0 and dx>=0
 Push    DX
 Mov     DL, '-'
 Call    Write_Char      ; print '-'
 Pop     DX
Checked:
 ; print whole part:
 Call    Print_Num
 ; if remainder=0, then no need to print it:
 Cmp     DX,0
 Je      Done
 Push    DX
 ; print dot after the number:
 Mov     DL, '.'
 Call    Write_Char
 Pop     DX
 ; print digits after the dot:
 Mov     CX,Precision
 Call    Print_Fraction
Done:
 Pop     DX
 Pop     CX
 Ret
Print_Float Endp

;----------------------------------------------------------
; prints dx as fraction of division by bx.
; dx - remainder.
; bx - divider.
; cx - maximum number of digits after the dot.
Print_Fraction  Proc    Near
 Push    AX
 Push    DX
 Mov DI,3d
Next_Fraction:
 ; check if all digits are already printed:
 Cmp     CX,0
 Jz      End_Rem
 CMP DI,00d
 Je End_Rem
 Dec     CX             ; decrease digit counter.
 ; when remainder is '0' no need to continue:
 Cmp     DX,0
 Je      End_Rem

 Mov     AX,DX
 Xor     DX,DX
 Cmp     AX,0
 Jns     Not_Sig1
 Not     DX
Not_Sig1:
 Imul    Ten             ; dx:ax = ax * 10
 Idiv    BX              ; ax = dx:ax / bx   (dx - remainder)

 Push    DX              ; store remainder.
 Mov     DX,AX
 Cmp     DX,0
 Jns     Not_Sig2
 Neg     DX
Not_Sig2:
 Add     DL,30h         ; convert to ascii code.
 Call    Write_Char      ; print dl.
 Pop     DX
 Dec     DI
 Jmp     Next_Fraction
End_Rem:
 Pop     DX
 Pop     AX
 Ret
Print_Fraction  Endp
;----------------------------------------------------------

Write_Char  Proc    Near
 Push AX
 Mov  AH, 02h
 Int  21h
 Pop  AX
 Ret
Write_Char      Endp
Ret 
Ends