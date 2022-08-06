.Model Small
.Stack 64
.Data
String1 DB "You Clicked Box 1","$" 
String2 DB "You Clicked Box 2","$"
.Code

PROC Main
Mov AX,Data
Mov DS,AX

Mov AX,0012H             ; To set 640*480 pixels
Int 10H
Int 10H 
                      
Square:
CALL DrawBoxWhite
CALL DrawBoxRed
        
CALL DetectionBox                    
ENDP Main

PROC DrawBoxWhite        ; TO DRAW BOX WHITE     
Mov CX,100d
Mov DX,100d
  
Mov BX,20d               ; To keep height
RightS:                  ; THE RIGHT EDGE OF THE SQUARE
    Mov AH,0CH
    Mov AL,0FH
    Int 10H
    
    Inc DX               ; CX=100
    Dec BL
    Cmp BL,00h           ; DX increase until it reaches its height.
    Jne RightS 
    
Mov BX,25d               ; To keep height
BottomS:                 ; THE BOTTOM OF THE SQUARE
    Mov AH,0CH
    Mov AL,0FH
    Int 10H
    
    Dec CX               ; DX=120
    Dec BL
    Cmp BL,00h           ; CX decrease until it reaches its height.
    Jne BottomS
    
Mov BX,20d               ; To keep height
LeftS:                   ; THE LEFT EDGE OF THE SQUARE
    Mov AH,0CH
    Mov AL,0FH
    Int 10H
    
    Dec DX               ;CX=75
    Dec BL
    Cmp BL,00h           ; DX decrease until it reaches its height.
    Jne LeftS
    
Mov BX,25d               ; To keep height
TopS:                    ; THE RIGHT SIDE OF THE SQUARE
    Mov AH,0CH
    Mov AL,0FH
    Int 10H
    
    Inc CX                ;DX=100
    Dec BL
    Cmp BL,00h           ; CX increase until it reaches its height.
    Jne TopS
Ret
ENDP DrawBoxWhite

PROC DrawBoxRed        ; TO DRAW BOX WHITE     
Mov CX,300d
Mov DX,300d
  
Mov BX,20d               ; To keep height
RightR:                  ; THE RIGHT EDGE OF THE SQUARE
    Mov AH,0CH
    Mov AL,0FH
    Int 10H
                         ;CX = 300
    Inc DX     
    Dec BL
    Cmp BL,00h           ; DX increase until it reaches its height.
    Jne RightR 
    
Mov BX,25d               ; To keep height
BottomR:                 ; THE BOTTOM OF THE SQUARE
    Mov AH,0CH
    Mov AL,0FH
    Int 10H
                         ; DX=320
    Dec CX     
    Dec BL
    Cmp BL,00h           ; CX decrease until it reaches its height.
    Jne BottomR
    
Mov BX,20d               ; To keep height
LeftR:                   ; THE LEFT EDGE OF THE SQUARE
    Mov AH,0CH
    Mov AL,0FH
    Int 10H
                         ;CX = 275
    Dec DX     
    Dec BL
    Cmp BL,00h           ; DX decrease until it reaches its height.
    Jne LeftR
    
Mov BX,25d               ; To keep height
TopR:                    ; THE RIGHT SIDE OF THE SQUARE
    Mov AH,0CH
    Mov AL,0FH
    Int 10H
                         ;DX=300
    Inc CX     
    Dec BL
    Cmp BL,00h           ; CX increase until it reaches its height.
    Jne TopR
Ret
ENDP DrawBoxRed
              
Proc DetectionBox 
GETXY:

MOV AX,03
INT 33H
SHR CX,1
CMP BX,1
JE BXC
JMP GETXY

BXC:
CMP CX,100
JNC Other
CMP CX,70
JC Other
CMP DX,120
JNC Other
CMP DX,100
JC Other

MOV AX,03
INT 33H
CMP BX,0
JNE GETXY

Mov AH,9h
Mov DX,OFFSET String1    ; To printf String1
Int 21h
HLT

Other:
CMP CX,300
JNC GETXY
CMP CX,275
JC GETXY
CMP DX,320
JNC GETXY
CMP DX,300
JC GETXY

MOV AX,03
INT 33H
CMP BX,0
JNZ GETXY

Mov AH,9h
Mov DX,OFFSET String2    ; To printf String2
Int 21h

HLT
DetectionBox ENDP
Ends




